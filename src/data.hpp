#ifndef ANTOK_DATA_H
#define ANTOK_DATA_H

#include<constants.h>

#include<map>

namespace antok {

	struct Data {

		std::map<std::string, double> doubles;
		std::map<std::string, int> ints;
		std::map<std::string, Long64_t> long64_ts;

		std::map<std::string, std::vector<double> > particle_doubles;
		std::map<std::string, std::vector<int> > particle_ints;

		int Run;
		int TrigMask;
		Long64_t EvNbr;
		int SpillNbr;

		double X_primV;
		double Y_primV;
		double Z_primV;

		double gradx;
		double grady;

		double beam_time;

		std::vector<double> Mom_x;
		std::vector<double> Mom_y;
		std::vector<double> Mom_z;

		std::vector<double> z_max;

		std::vector<double> theta_RICH;
		std::vector<int> PID_RICH;

		double chi2PV;

		double RPD_Px;
		double RPD_Py;
		double RPD_Pz;
		double RPD_E;
		double RPD_Tz;
		double RPD_z;
		double RPD_beta;
		double RPD_Phi;
		double RPD_dEA;
		double RPD_dEB;
		int nbrRPDTracks;

		int cedarID_bayes;
		double cedarTheta_X;
		double cedarTheta_Y;
		double cedarProbK1;
		double cedarProbK2;
		double cedarProbK3;

		Data() {
			const unsigned int& N_PARTICLES = antok::Constants::n_particles();
			Mom_x.resize(N_PARTICLES);
			Mom_y.resize(N_PARTICLES);
			Mom_z.resize(N_PARTICLES);
			z_max.resize(N_PARTICLES);
			theta_RICH.resize(N_PARTICLES);
			PID_RICH.resize(N_PARTICLES);
		}

	};

}

#endif
