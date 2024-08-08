#!/bin/bash

usage()
{
   echo "Usage: PrepareInput.sh InputFolder ScriptFolder OutputBase BackgroundFolder BackgroundCount [the rest...]"
}

if [[ "$1" == "-h" || "$1" == "--help" || "$#" -lt 3 ]]; then
   usage
   exit
fi

Directory=$1
shift

ScriptFolder=$1
shift

OutputBase=$1
shift

BackgroundFolder=$1
shift

BackgroundCount=$1
shift

mkdir -p $ScriptFolder
mkdir -p $OutputBase

Condor=Submit.condor

echo "Universe              = vanilla"                         > $Condor
echo "Executable            = $PWD/RunCondor.sh"               >> $Condor
echo "should_transfer_files = NO"                              >> $Condor
echo "requirements = (OpSysAndVer =?= \"AlmaLinux9\")"         >> $Condor
echo "+JobFlavour           = \"testmatch\""                   >> $Condor
echo                                                           >> $Condor

Count=0
for i in `ls $Directory/*root`
do
   BackgroundFiles=`ls $BackgroundFolder/*.root | shuf | head -n$BackgroundCount | tr '\n' ',' | sed "s/,$//"`

   echo "Arguments = $PWD $ProjectBase $CMSSW_BASE $OutputBase/Result${Count}.root $Count --Background $BackgroundFiles --Input $i $@" >> $Condor
   echo "Output    = $ScriptFolder/Part${Count}.out"                                         >> $Condor
   echo "Error     = $ScriptFolder/Part${Count}.err"                                         >> $Condor
   echo "Log       = $ScriptFolder/Part${Count}.log"                                         >> $Condor
   echo "Queue"                                                                              >> $Condor
   echo                                                                                      >> $Condor

   Count=$(($Count + 1))
done




