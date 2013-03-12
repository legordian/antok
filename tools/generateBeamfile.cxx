
#include<iostream>
#include<string>

#include<TFile.h>
#include<TH2D.h>
#include<THnSparse.h>
#include<TLorentzVector.h>
#include<TTree.h>
#include<TTreeIndex.h>

#include<basic_calcs.h>
#include<beamfileGeneratorHelpers.h>
#include<constants.h>
#include<initializer.h>


void fillFiveDimHist(std::string inFileName) {

	std::string configfilename = "../../antok/config/monte_carlo_run2.yaml";
	antok::Initializer* initializer = antok::Initializer::instance();
	if(not initializer->readConfigFile(configfilename)) {
		std::cerr<<"Could not open config file. Aborting..."<<std::endl;
		exit(1);
	}
	const double& PION_MASS = antok::Constants::charged_pion_mass();

	TFile* inFile = TFile::Open(inFileName.c_str(), "READ");
	TTree* inTree = (TTree*)inFile->Get("Standard Event Selection/USR55");
	TFile* outFile = TFile::Open("bla.root", "RECREATE");
	outFile->cd();

	TH1D* vtxX = new TH1D("vtxX", "vtxX", 10000, -2, 2);
	TH1D* vtxY = new TH1D("vtxY", "vtxY", 10000, -2, 2);
	TH1D* momX = new TH1D("momX", "momX", 50000, -0.8, 0.8);
	TH1D* momY = new TH1D("momY", "momY", 50000, -0.8, 0.8);
	TH1D* momZ = new TH1D("momZ", "momZ", 10000, 187, 196);

	double px1, py1, pz1;
	double px2, py2, pz2;
	double px3, py3, pz3;
	double px4, py4, pz4;
	double px5, py5, pz5;
	double gradx, grady;
	double primVx, primVy;

	inTree->SetBranchAddress("Mom_x1", &px1);
	inTree->SetBranchAddress("Mom_y1", &py1);
	inTree->SetBranchAddress("Mom_z1", &pz1);
	inTree->SetBranchAddress("Mom_x2", &px2);
	inTree->SetBranchAddress("Mom_y2", &py2);
	inTree->SetBranchAddress("Mom_z2", &pz2);
	inTree->SetBranchAddress("Mom_x3", &px3);
	inTree->SetBranchAddress("Mom_y3", &py3);
	inTree->SetBranchAddress("Mom_z3", &pz3);
	inTree->SetBranchAddress("Mom_x4", &px4);
	inTree->SetBranchAddress("Mom_y4", &py4);
	inTree->SetBranchAddress("Mom_z4", &pz4);
	inTree->SetBranchAddress("Mom_x5", &px5);
	inTree->SetBranchAddress("Mom_y5", &py5);
	inTree->SetBranchAddress("Mom_z5", &pz5);
	inTree->SetBranchAddress("gradx", &gradx);
	inTree->SetBranchAddress("grady", &grady);
	inTree->SetBranchAddress("X_primV", &primVx);
	inTree->SetBranchAddress("Y_primV", &primVy);

	double bx, by, bz;
	TTree* tempTree = new TTree("beamTreeTemp", "beamTreeTemp");
	tempTree->Branch("vertex_x_position", &primVx, "vertex_x_position/D");
	tempTree->Branch("vertex_y_position", &primVy, "vertex_y_position/D");
	tempTree->Branch("beam_momentum_x", &bx,"beam_momentum_x/D");
	tempTree->Branch("beam_momentum_y", &by,"beam_momentum_y/D");
	tempTree->Branch("beam_momentum_z", &bz,"beam_momentum_z/D");
	TTree* outTree = (TTree*)tempTree->Clone("beamTree");

	std::vector<TLorentzVector> particles;
	particles.resize(6);
	unsigned int entries = inTree->GetEntries();

	for(unsigned int i = 0; i < entries; ++i) {

		inTree->GetEntry(i);

		particles[1].SetXYZM(px1, py1, pz1, PION_MASS);
		particles[2].SetXYZM(px2, py2, pz2, PION_MASS);
		particles[3].SetXYZM(px3, py3, pz3, PION_MASS);
		particles[4].SetXYZM(px4, py4, pz4, PION_MASS);
		particles[5].SetXYZM(px5, py5, pz5, PION_MASS);

		TLorentzVector pSum;
		for(unsigned int j = 1; j < 6; ++j) {
			pSum += particles.at(j);
		}
		particles[0] = antok::get_beam_energy(TVector3(gradx, grady, 1.), pSum);
		TVector3 beam = particles[0].Vect();
		bx = beam.X();
		by = beam.Y();
		bz = beam.Z();

		vtxX->Fill(primVx);
		vtxY->Fill(primVy);
		momX->Fill(bx);
		momY->Fill(by);
		momZ->Fill(bz);

		tempTree->Fill();

		if(i % 100000 == 0) {
			std::cout<<"Entry "<<i<<" of "<<entries<<std::endl;
		}
/*		if(i > 500000) {
			entries = tempTree->GetEntries();
			break;
		}
*/
	}

	std::vector<double> lowerCorner(5, 0);
	std::vector<double> upperCorner(5, 0);
	bool first = true;
	for(unsigned int i = 0; i < entries; ++i) {
		tempTree->GetEntry(i);
		if(first) {
			lowerCorner[0] = primVx;
			lowerCorner[1] = primVy;
			lowerCorner[2] = bx;
			lowerCorner[3] = by;
			lowerCorner[4] = bz;
			upperCorner[0] = primVx;
			upperCorner[1] = primVy;
			upperCorner[2] = bx;
			upperCorner[3] = by;
			upperCorner[4] = bz;
			first = false;
		} else {
			if(primVx < lowerCorner[0]) lowerCorner[0] = primVx;
			if(primVy < lowerCorner[1]) lowerCorner[1] = primVy;
			if(bx < lowerCorner[2]) lowerCorner[2] = bx;
			if(by < lowerCorner[3]) lowerCorner[3] = by;
			if(bz < lowerCorner[4]) lowerCorner[4] = bz;
			if(primVx > upperCorner[0]) upperCorner[0] = primVx;
			if(primVy > upperCorner[1]) upperCorner[1] = primVy;
			if(bx > upperCorner[2]) upperCorner[2] = bx;
			if(by > upperCorner[3]) upperCorner[3] = by;
			if(bz > upperCorner[4]) upperCorner[4] = bz;
		}
	}
	antok::beamfileGenerator::fiveDimBin bin(lowerCorner, upperCorner);
	std::cout<<"Got first bin: "<<std::endl;
	bin.print(std::cout);

	std::list<std::pair<TTree*, antok::beamfileGenerator::fiveDimBin> > adaptiveBins;
	antok::beamfileGenerator::getAdaptiveBins(adaptiveBins, bin, tempTree);
	unsigned int nBins = adaptiveBins.size();
	std::cout<<"Split phase space in "<<nBins<<" bins."<<std::endl;

	double primVx_sigma, primVy_sigma, bx_sigma, by_sigma, bz_sigma;
	int binContent = 0;
	outTree->SetBranchAddress("vertex_x_position", &primVx);
	outTree->SetBranchAddress("vertex_y_position", &primVy);
	outTree->SetBranchAddress("beam_momentum_x", &bx);
	outTree->SetBranchAddress("beam_momentum_y", &by);
	outTree->SetBranchAddress("beam_momentum_z", &bz);
	outTree->Branch("vertex_x_position_sigma", &primVx_sigma, "vertex_x_position_sigma/D");
	outTree->Branch("vertex_y_position_sigma", &primVy_sigma, "vertex_y_position_sigma/D");
	outTree->Branch("beam_momentum_x_sigma", &bx_sigma,"beam_momentum_x_sigma/D");
	outTree->Branch("beam_momentum_y_sigma", &by_sigma,"beam_momentum_y_sigma/D");
	outTree->Branch("beam_momentum_z_sigma", &bz_sigma,"beam_momentum_z_sigma/D");
	outTree->Branch("bin_content", &binContent, "bin_content/I");

	std::cout << "Calculating and saving sigmas." << std:: endl;

	unsigned binNumber = 0;
	for(std::list<std::pair<TTree*, antok::beamfileGenerator::fiveDimBin> >::const_iterator binIt = adaptiveBins.begin(); binIt != adaptiveBins.end(); ++binIt) {
		std::cout<<"Bin "<<++binNumber<<" of "<<nBins<<std::endl;
		const antok::beamfileGenerator::fiveDimBin& currentBin = binIt->second;
		TTree* currentTree = binIt->first;
		currentTree->SetBranchAddress("vertex_x_position", &primVx);
		currentTree->SetBranchAddress("vertex_y_position", &primVy);
		currentTree->SetBranchAddress("beam_momentum_x", &bx);
		currentTree->SetBranchAddress("beam_momentum_y", &by);
		currentTree->SetBranchAddress("beam_momentum_z", &bz);
		binContent = currentTree->GetEntries();
		primVx_sigma = (currentBin._b[0] - currentBin._a[0]) / entries;
		primVy_sigma = (currentBin._b[1] - currentBin._a[1]) / entries;
		bx_sigma = (currentBin._b[2] - currentBin._a[2]) / entries;
		by_sigma = (currentBin._b[3] - currentBin._a[3]) / entries;
		bz_sigma = (currentBin._b[4] - currentBin._a[4]) / entries;
		for(int i = 0; i < binContent; ++i) {
			currentTree->GetEntry(i);
			outTree->Fill();
		}
	}
//	tempTree->Delete("all");

	outFile->Write();
	outFile->Close();

}

int main(int argc, char* argv[]) {
	if(argc == 2) {
		fillFiveDimHist(argv[1]);
	} else {
		std::cerr<<"Wrong number of arguments, is "<<argc<<", should be 1."<<std::endl;
	}
}
