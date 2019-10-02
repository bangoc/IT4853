#include "base.h"

#include <cmath>

#include "config.h"

double MyLog(double param) {
  if (kLogBase > 0) {
    return std::log(param)/std::log(kLogBase);
  }
  return std::log(param);
}