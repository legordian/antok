#include<plotter.h>

#include<yaml-cpp/yaml.h>

#include<TH1.h>

#include<cutter.h>
#include<object_manager.h>
#include<plot.hpp>
#include<yaml_utils.hpp>

antok::Plotter* antok::Plotter::_plotter = 0;

antok::Plotter* antok::Plotter::instance() {
	if(_plotter == 0) {
		_plotter = new antok::Plotter();
	}
	return _plotter;
}

void antok::Plotter::fill(const long& cutPattern) {

	for(unsigned int i = 0; i < _plots.size(); ++i) {
		_plots[i]->fill(cutPattern);
	}
	for(unsigned int i = 0; i < _waterfallHistograms.size(); ++i) {
		TH1* hist = _waterfallHistograms[i].histogram;
		for(unsigned int j = 0; j < _waterfallHistograms[i].cuts.size(); ++j) {
			const bool* result = _waterfallHistograms[i].cuts[j].second;
			if(*result) {
				hist->Fill(_waterfallHistograms[i].cuts[j].first, 1);
			} else {
				break;
			}
		}
	}

}

namespace {

	std::string __getCutnamesOffNode(const YAML::Node& withCut, const std::string& cutTrainName) {

		std::string cutName = antok::YAMLUtils::getString(withCut["ShortName"]);
		if(cutName == "") {
			std::cerr<<"Warning: One of the \"WithCuts\" or \"WithoutCuts\" appears to have a missing or invalid ";
			std::cout<<"\"ShortName\" for \"CutTrain\" \""<<cutTrainName<<"\", skipping entry."<<std::endl;
			return "";
		}
		antok::Cutter& cutter = antok::ObjectManager::instance()->getCutter();
		if(cutter.cutInCutTrain(cutName, cutTrainName)) {
			return cutName;
		} else {
			std::cerr<<"Warning: \"WithCuts\" or \"WithoutCuts\" entry \""<<cutName;
			std::cout<<"\" is not in \"CutTrain\" \""<<cutTrainName<<"\", skipping entry."<<std::endl;
			return "";
		}

	}

	long __handleCutList(const YAML::Node& cutNode, const std::string& cutTrainName, bool invertSelection) {

		std::vector<std::string> cutNames;
		if(cutNode.IsMap()) {
			std::string cutName = __getCutnamesOffNode(cutNode, cutTrainName);
			if(cutName == "") {
				return -1;
			}
			cutNames.push_back(cutName);
		} else if (cutNode.IsSequence()) {
			for(YAML::const_iterator innerCuts_it = cutNode.begin(); innerCuts_it != cutNode.end(); ++innerCuts_it) {
				std::string cutName = __getCutnamesOffNode(*innerCuts_it, cutTrainName);
				if(cutName == "") {
					cutNames.clear();
					break;
				}
				cutNames.push_back(cutName);
			}
			if(cutNames.empty()) {
				return -1;
			}
		} else {
			std::cerr<<"Warning: One of the \"WithCuts\" or \"WithoutCuts\" appears to have invalid format for \"CutTrain\" \""<<cutTrainName<<"\", skipping entry."<<std::endl;
			return -1;
		}
		antok::Cutter& cutter = antok::ObjectManager::instance()->getCutter();
		long cutmask = cutter.getCutmaskForNames(cutNames);
		if(invertSelection) {
			long allCuts = cutter.getAllCutsCutmaskForCutTrain(cutTrainName);
			cutmask = (~cutmask)&allCuts;
		}
		return cutmask;
	}

}

bool antok::Plotter::handleAdditionalCuts(const YAML::Node& trainList, std::map<std::string, std::vector<long> >& map) {

	using antok::YAMLUtils::hasNodeKey;

	bool error = false;
	for(YAML::const_iterator trainList_it = trainList.begin(); trainList_it != trainList.end(); ++trainList_it) {
		const YAML::Node& entry = *trainList_it;
		if((not (hasNodeKey(entry, "CutTrain"))) or (not hasNodeKey(entry["CutTrain"], "Name"))) {
			std::cerr<<"Warning: \"CutTrain\" missing or invalid for an entry, skipping it."<<std::endl;
			continue;
		}
		std::string cutTrainName = antok::YAMLUtils::getString(entry["CutTrain"]["Name"]);
		if(cutTrainName == "") {
			std::cerr<<"Warning: Could not convert \"CutTrain\" to std::string for an entry, skipping it."<<std::endl;
			continue;
		}
		if(not (hasNodeKey(entry, "WithCuts") and hasNodeKey(entry, "WithoutCuts"))) {
			std::cerr<<"Warning: Either \"WithCuts\" or \"WithoutCuts\" missing for \"CutTrain\" \""<<cutTrainName<<"\", skipping entry."<<std::endl;
			continue;
		}
		if(not (entry["WithCuts"].IsSequence() and entry["WithoutCuts"].IsSequence())) {
			std::cerr<<"Warning: Either \"WithCuts\" or \"WithoutCuts\" is not a sequence for \"CutTrain\" \""<<cutTrainName<<"\", skipping entry."<<std::endl;
			continue;
		}
		bool innerError = false;
		std::vector<long> cutMasks;
		for(YAML::const_iterator withCuts_it = entry["WithCuts"].begin(); withCuts_it != entry["WithCuts"].end(); ++withCuts_it) {
			const YAML::Node& withCut = *withCuts_it;
			long cutmask = __handleCutList(withCut, cutTrainName, false);
			if(cutmask < 0) {
				innerError = true;
				error = true;
				break;
			}
			cutMasks.push_back(cutmask);
		}
		if(innerError) {
			continue;
		}
		for(YAML::const_iterator withoutCuts_it = entry["WithoutCuts"].begin(); withoutCuts_it != entry["WithoutCuts"].end(); ++withoutCuts_it) {
			const YAML::Node& withoutCut = *withoutCuts_it;
			long cutmask = __handleCutList(withoutCut, cutTrainName, true);
			if(cutmask < 0) {
				innerError = true;
				error = true;
				break;
			}
			cutMasks.push_back(cutmask);
		}
		if(innerError) {
			continue;
		}
		map[cutTrainName] = cutMasks;
	}
	return (not error);

}

antok::plotUtils::GlobalPlotOptions::GlobalPlotOptions(const YAML::Node& optionNode) {

	using antok::YAMLUtils::hasNodeKey;

	plotsForSequentialCuts = false;
	plotsWithSingleCutsOn = false;
	plotsWithSingleCutsOff = false;
	statisticsHistInName = "";
	statisticsHistOutName = "";

	if(not optionNode) {
		std::cerr<<"Warning: \"GlobalPlotOptions\" not found in configuration file."<<std::endl;
		return;
	}

	plotsForSequentialCuts = handleOnOffOption("PlotsForSequentialCuts", optionNode, "GobalPlotOptions");
	plotsWithSingleCutsOn = handleOnOffOption("PlotsWithSingleCutsOn", optionNode, "GobalPlotOptions");
	plotsWithSingleCutsOff = handleOnOffOption("PlotsWithSingleCutsOff", optionNode, "GobalPlotOptions");

	if(not hasNodeKey(optionNode, "StatisticsHistogram")) {
		std::cerr<<"Warning: \"StatisticsHistogram\" not found in \"GobalPlotOptions\", switching it off"<<std::endl;
	} else {
		const YAML::Node& statsHistOpt = optionNode["StatisticsHistogram"];
		bool state = handleOnOffOption("State", statsHistOpt, "StatisticsHistogram");
		if(state) {
			if(not (hasNodeKey(statsHistOpt, "InputName") and hasNodeKey(statsHistOpt, "OutputName"))) {
				std::cerr<<"Warning: \"InputName\" or \"OutputName\" not found in \"GobalPlotOptions\"'s \"StatisticsHistogram\", switching histogram off."<<std::endl;
			} else {
				statisticsHistInName = antok::YAMLUtils::getString(statsHistOpt["InputName"]);
				statisticsHistOutName = antok::YAMLUtils::getString(statsHistOpt["OutputName"]);
				if(statisticsHistInName == "" or statisticsHistOutName == "") {
					std::cerr<<"Warning: Could not convert either \"InputName\" or \"OutputName\" to std::string, switching histogram off."<<std::endl;
					statisticsHistInName = "";
					statisticsHistOutName = "";
				}
			}
		}
	}

	if(hasNodeKey(optionNode, "GlobalCuts")) {
		if(not antok::Plotter::handleAdditionalCuts(optionNode["GlobalCuts"], cutMasks)) {
			std::cerr<<"Warning: There was a problem when processing the \"GlobalCuts\" in \"GobalPlotOptions\"."<<std::endl;
		}
	}

	if(hasNodeKey(optionNode, "HistogramNameAppendix")) {
		std::string histNameAppendix = antok::YAMLUtils::getString(optionNode["HistogramNameAppendix"]);
		if(histNameAppendix == "") {
			std::cerr<<"Warning: \"HistogramNameAppendix\" in \"GlobalPlotOptions\" is empty or not a valid string."<<std::endl;
		}
		antok::ObjectManager::instance()->registerHistogramNameAppendix(histNameAppendix);
	}

}

bool antok::plotUtils::GlobalPlotOptions::handleOnOffOption(std::string optionName, const YAML::Node& option, std::string location) const {

	using antok::YAMLUtils::hasNodeKey;

	if(not hasNodeKey(option, optionName)) {
		std::cerr<<"Warning: \""<<optionName<<"\" not found in \""<<location<<"\", switching it off"<<std::endl;
	} else {
		std::string optionValue = antok::YAMLUtils::getString(option[optionName]);
		if(optionValue == "On") {
			return true;
		} else if (optionValue == "Off") {
			// returning at end of function
		} else {
			std::cerr<<"Warning: \""<<location<<"\"'s \""<<optionName<<"\" is \""<<optionValue<<"\" instead of \"On\" or \"Off\", switching it off"<<std::endl;
		}
	}
	return false;

}

