
#include<assert.h>
#include<sstream>

#include<cutter.h>

hlib::Cutter::Cutter() {

	_cuts.push_back(new TrigMask(0x1));
	_cuts.push_back(new VrtxZ(-28.4, -68.4));
	_cuts.push_back(new VrtxR(1.75));
	_cuts.push_back(new nRPDTracks(1));
	_cuts.push_back(new RPDProtMass(0.2));
	_cuts.push_back(new CedarKaon());
	_cuts.push_back(new TPrime(0.1, -1.));
	_cuts.push_back(new RPDPlanarity());
	_cuts.push_back(new Exclusivity(191., 3.28));

}

int hlib::Cutter::get_cutmask(const hlib::Event& event) {

	int cutmask = 0;
	for(unsigned int i = 0; i < _cuts.size(); ++i) {
		if((*(_cuts.at(i)))(event)) {
			cutmask += (1<<i);
		}
	}
	return cutmask;

};

std::string hlib::Cutter::get_abbreviations(int bitmask) {

	unsigned int size = _cuts.size();
	assert(bitmask>>(size) == 0);
	std::stringstream sstr;
	sstr<<"(";
	if(bitmask == 0) {
		sstr<<"AllCuts";
	} else if (bitmask == ((1<<size)-1)) {
		sstr<<"NoCuts";
	} else {
		bool first = true;
		for(unsigned int i = 0; i < size; ++i) {
			if(!((bitmask>>i)&0x1)) {
				if(first) {
					first = false;
				} else {
					sstr<<"|";
				}
				sstr<<_cuts.at((size-1)-i)->get_abbreviation();
			}
		}
	}
	sstr<<")";
	std::string retval = sstr.str();
	return retval;

};
