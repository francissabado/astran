#!/bin/bash -e

#Astran Setup
BASEDIR=$(f_currentPath)
export ASTRAN_PATH=$BASEDIR/build
export PATH=$BASEDIR/../wxSightGL/build/bin:$PATH
export PATH=${ASTRAN_PATH}/bin:$PATH

#Setup to get Gurobi Working
export GUROBI_HOME=/opt/gurobi652/linux64
export PATH=${GUROBI_HOME}/bin:${PATH}
export LD_LIBRARY_PATH=${GUROBI_HOME}/lib:${LD_LIBRARY_PATH}
export GRB_LICENSE_FILE=$GUROBI_HOME/../gurobi.lic










