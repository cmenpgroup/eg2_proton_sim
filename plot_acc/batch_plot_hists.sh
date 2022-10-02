#!/bin/bash

################################################################################
# ./batch_plot_hists_Pt2vsZh.sh <target> <first run> <final run> <ana> <sigma> #
#     <target> = (D, C, Fe, Pb)                                                #
#     <nrun>   = (1 - 25)                                                      #
#     <ana>    = (1d, 2d, 3d)                                                  #
#     <sigma>  = proton sigma cut                                              #
#                                                                              #
# EG: ./batch_plot_hists_Pt2vsZh.sh D 1 25 2d                                  #
#                                                                              #
################################################################################

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
ANA=${INPUTARRAY[3]}
SIGMA=${INPUTARRAY[4]}

#####
# Main
###
COUNTER=0
for (( RN=${FIRSTRUN}; RN<=${LASTRUN}; RN++ ))
do
    RUNNO=$(get_num_2dig ${RN});
    FILE=/Users/wood5/jlab/clas6/DMS/eg2/proton/Simulations/Proton_Lepto/GST_out/${TARNAME}/pruned${TARNAME}_${RUNNO}.root;
    if [ -e ${FILE} ]; then
        cmd=plot_hists_${ANA}.C\(\"${TARNAME}\",${RN},-1,${SIGMA}\);
        echo "Running ${cmd}"; 
	date;
        root -l -q ${cmd};
    fi
done

PREFIX=plot_hists_${ANA}_pruned${TARNAME};
${ROOTSYS}/bin/hadd ${PREFIX}_all.root ${PREFIX}_*.root

DIR=${TARNAME}/${ANA}/sig${SIGMA};
if [ ! -d "$DIR" ];
then
	echo "$DIR directory does not exist."
        mkdir -p $DIR
else
	echo "$DIR directory exists."
fi
mv -v ${PREFIX}_*.root $DIR
