#!/bin/bash

##############################################################
# ./run_GST_JPSim.sh <target> <first run> <final run>        #
#     <target> = (D, C, Fe, Pb)                              #
#     <nrun>   = (1 - 25)                                    #
#                                                            #
# EG: ./batch_zlc_dPhiLab.sh D 1 25                          #
#                                                            #
##############################################################

#####
# Function
###select 

function get_num_4dig()
{
  sr=$1
  srn=""
  if [[ $sr -lt 10 ]]; then
    srn="000$sr"
  elif [[ $sr -lt 100 ]]; then
    srn="00$sr"
  elif [[ $sr -lt 1000 ]]; then
    srn="0$sr"
  else
    srn="$sr"
  fi
  echo $srn
}


function get_num_2dig()
{
  sr2=$1
  srn2=""
  if [[ $sr2 -lt 10 ]]; then
    srn2="0$sr2"
  else
    srn2="$sr2"
  fi
  echo $srn2
}

#####
# Input
###

INPUTARRAY=("$@")

TARNAME=${INPUTARRAY[0]}
FIRSTRUN=${INPUTARRAY[1]}
LASTRUN=${INPUTARRAY[2]}

#####
# Main
###
COUNTER=0
for (( RN=${FIRSTRUN}; RN<=${LASTRUN}; RN++ ))
do
    RUNNO=$(get_num_2dig ${RN});
    FILE=/Users/wood5/jlab/clas6/DMS/eg2/proton/Simulations/Proton_Lepto/GST_out/${TARNAME}/pruned${TARNAME}_${RUNNO}.root;
    if [ -e ${FILE} ]; then
        cmd=plot_zlc_dPhiLab.C\(\"${TARNAME}\",${RN},-1\);
        echo "Running ${cmd}";
        root -l -q ${cmd};
    fi
done

${ROOTSYS}/bin/hadd plot_zlc_dPhiLab_pruned${TARNAME}_all.root plot_zlc_dPhiLab_pruned${TARNAME}_*.root
