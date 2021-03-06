#ifndef ANTOK_USER_CDREIS_H
#define ANTOK_USER_CDREIS_H

#include<yaml-cpp/yaml.h>

namespace antok {

	class Function;

	namespace user {

		namespace cdreis {

			antok::Function* getUserFunction(const YAML::Node& function,
			                                 std::vector<std::string>& quantityNames,
			                                 int index);

			antok::Function* generateGetRecoilLorentzVec(const YAML::Node& function, std::vector<std::string>& quantityNames, int index);

		}

	}

}

#endif
