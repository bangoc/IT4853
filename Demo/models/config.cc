#include "config.h"

#include <cstdlib>
#include <sstream>

double kLogBase = 2.71828182845904523536;
double kBnormAlpha = 1.0;

void DefaultConfig() {
  char* pointer;
	if (pointer = std::getenv("VSM_LOG_BASE")) {
		std::stringstream ss{pointer};
    ss >> kLogBase;
	} 
  if (pointer = std::getenv("VSM_BNORM_ALPHA")) {
    std::stringstream ss{pointer};
    ss >> kBnormAlpha;
  }
}