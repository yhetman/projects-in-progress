#!/bin/bash

HOME=/home/user
DESKTOP=$HOME/Desktop
GENDIR=general_directory
DIR=$DESKTOP/$GENDIR
VARIANT=19

R=8
N1=42
N2=43
r1=6
r2=8
a1=5
a2=7
a3=4
a4=3
t1=-5
t2=-4


function go_to_directory ()
{
	cd $DIR
	index=1
	while true;
	do
		cd ./$index
		index=$((index + 1))
		if [[ $index -gt $1 ]] ; then
			break
		fi
	done
	echo "[INFO] Get to location  :  `pwd`"
}


function check_folder_existence ()
{
	if [[ ! -e $1 ]] ; then
		mkdir -p $1
	elif [[ ! -d $1 ]] ; then
		echo "$1 already exists but is not a directory"
	fi
	if [[ -e $1 ]]; then
		cd $1
	fi
	echo "[INFO] Folder $1 exists ..."
}


function tarring()
{
	go_to_directory $1
	echo "[INFO] Creating tar archive archive_$1_$2 from files in foler `pwd` ..."
	tar -czf archive_$1_$2.tar.gz M* 2>/dev/null
	echo "[INFO] Moving archive archive_$1_$2 to folder `pwd`/../$2 ..."
	mv archive_$1_$2.tar.gz ../ 2>/dev/null
}


function sorting()
{
	go_to_directory $1
	locate $2
	destination=`pwd`
	go_to_directory $1
	echo "[INFO] Concatenate content of files..."
	cat ./M* > input.txt 2>/dev/null
	echo "[INFO] Sorting..."
	sort -nr -o $destination/output$1.txt input.txt 2>/dev/null
	rm input.txt
}


function locate()
{
	echo "[INFO] Looking for a folder on level $r1$t1 ..."
	counter=$1
	if [[ $counter -gt 0 ]] ; then
		curr_dir=${PWD##*/}
		curr_dir_nb=`cut -b 1 $curr_dir`
		counter=`expr $curr_dir_nb + $1`
		go_to_directory $counter
	elif [[ $counter -lt 0 ]] ; then
		while true
		do
			cd ..
			counter=$((counter + 1))
			if [[ $counter -eq 0 ]] ; then
				break
			fi
		done
	fi
}


function add_file_to_archive()
{
	loc=`find $DIR -iname *output$1.txt`
	echo "[INFO] Remember location : $loc..."
	archive_loc=`find $DIR -iname *archive_$1_*.tar.gz`
	echo "[INFO] Remember location : $archive_loc ..."
	go_to_directory $1
	dest=`pwd`
	echo "[INFO] Extracting archive..."
	tar -xzf $archive_loc 2>/dev/null
	rm $archive_loc
	mv $loc . 2>/dev/null
	echo "[INFO] Adding file to archive..."
	tar -C ./ -czf $dest/archive_$1_$2.tar.gz *.txt M* 2>/dev/null
	mv $dest/archive_$1_$2.tar.gz ../ 2>/dev/null
}


function extract_archive()
{
	archive_location=`find $DIR -iname *archive*_$1.tar.gz`
	go_to_directory $2
	destin=`pwd`
	echo "[INFO] Extracting archive to folder $destin..."
	tar -xzf $archive_location -C $destin 2>/dev/null
}

echo "[VARIANT] : "$VARIANT

cheвотck_folder_existence $DESKTOP
check_folder_existence $DIR

index=1

echo "[INFO] Creating nested folders ..."

while true;
do
	mkdir -p ./$index
	cd ./$index
	index=$((index + 1))
	if [[ $index -gt $R ]] ; then
		break 
	fi
done

go_to_directory $r1
echo "[INFO] Starting implementation of processes..."
echo ""

python3 ~/Рабочий\ стол/opanasenko_processes.py $N1
go_to_directory $r2
echo "[INFO] Starting implementation of threads..."
echo ""
python3 ~/Рабочий\ стол/opanasenko_threads.py $N2
tarring $r1 $a1
tarring $r2 $a2
sorting $r1 $t1
sorting $r2 $t2
add_file_to_archive $r1 $a1
add_file_to_archive $r2 $a2
extract_archive $a1 $a3
extract_archive $a2 $a4
echo "[FINISH] Execution finished!"
