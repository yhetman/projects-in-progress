#!/usr/bin/env bash

dir=my_virtual_dir

home_path=/mnt/DATA/projects-in-progress/uni/operation-systems/bash-scripting

script_path=/mnt/DATA/projects-in-progress/uni/operation-systems/processes_threads
R=12
N1=10
N2=51
r1=10
r2=12
a1=9
a2=11
a3=5
a4=6
t1=-9
t2=-8
folder=folder

function check ()
{
	if [[ ! -e $1 ]]; then
		mkdir $1
	elif [[ ! -d $1 ]]; then
		echo "$1 already exists but is not a directory" 1>&2
	fi
	return 0
}


function recur_dirs ()
{
	counter=1
	while true
	do
		mkdir -p ./$counter$2
		cd ./$counter$2
		counter=$((counter + 1))
		if [[ $counter -gt $1 ]] 
		then
			break
		fi
	done
}

function get_dir ()
{
	counter=1
	while true;
	do
		cd ./$counter$2
		counter=$((counter + 1))
		if [[ $counter -gt $1 ]]
		then
			break
		fi
	done
}

check $dir

if [[ -e $dir ]]; then
	cd $dir
fi

#for x in {1..$R}; do mkdir -pv ./$x$folder;cd ./$x$folder; done;

PWD=`pwd`

recur_dirs $R $folder


cd $home_path/$dir

get_dir $r1 $folder


$script_path/process_call.sh

