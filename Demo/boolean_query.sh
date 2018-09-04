#!/bin/bash
awk '/aeroelastic/ && /law/' cran.all.1400.oneline
awk '/analytical/ && /solution/ && /wave/ && !/approximation/' cran.all.1400.oneline
