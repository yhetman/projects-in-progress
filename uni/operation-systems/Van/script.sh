#!/bin/bash

R=12

N1=5
N2=5

r1=10
r2=12

a1=9
a2=11
a3=5
a4=6

t1=-9
t2=-8

START_DIR="/home/yhetman/Documents/Van"
VIRTUAL="Virtual"
SCRIPT_HOME=$START_DIR/$VIRTUAL

function check_if_exists()
{
	if [[ ! -e $1 ]] ; then
		mkdir $1
	elif [[ ! -d $1 ]] ; then
		echo "$1 already exists but is not a directory" 1>&2
		exit 2
	fi
	return 0
}


function create_nested_folders()
{
	level=1
	while true
	do
		mkdir -p ./$level
		cd ./$level
		level=$((level + 1))
		if [[ $level -gt $1 ]] ; then
			break 
		fi
	done
}

function dive_to_level()
{
	cd $SCRIPT_HOME
	level=1
	while true;
	do
		cd ./$level
		level=$((level + 1))
		if [[ $level -gt $1 ]] ; then
			break
		fi
	done
}


function sort_and_count_new_level()
{
	dive_to_level $1
	count_new_level $2
	destination=`pwd`
	dive_to_level $1
	ls | grep output*
	cat output*.txt > in_sorted.txt 
	sort -nr -o $destination/sorted$1.txt in_sorted.txt
	rm in_sorted.txt
}

function count_new_level()
{
	level=$1
	if [[ $level -gt 0 ]] ; then
		curr=${PWD##*/}
		level_number=`cut -b 1 $curr`
		level=`expr $level_number + $1`
		dive_to_level $level
	elif [[ $level -lt 0 ]] ; then
		while true ;
		do
			cd ..
			level=$((level + 1))
			if [[ $level -eq 0 ]] ; then
				break
			fi
		done
	fi
}


function main()
{
	echo -e "\e[1m\e[94m"
	echo "Script started running ..."
	check_if_exists $SCRIPT_HOME
	cd $VIRTUAL
	create_nested_folders $R
	echo "Nested folders were created"
	cd $SCRIPT_HOME
	dive_to_level $r1
	counter=0
	while true;
	do
		python $START_DIR/start_process.py $START_DIR/input2.txt &
		counter=$((counter + 1))
		if [[ $counter -eq $N1 ]] ; then
			break ;
		fi
	done
	wait
	ls
	echo "All processes finished their work"
	tar -czf processes_archive.tar.gz output*.txt 2>/dev/null
	mv processes_archive.tar.gz ../
	echo "Archived Processes' results"
	dive_to_level $r2
	counter=0
	while true;
	do
		python $START_DIR/start_thread.py $START_DIR/input2.txt &
		counter=$((counter + 1))
		if [[ $counter -eq $N2 ]] ; then
			break ;
		fi
	done
	wait
	ls
	echo "All threads finished their work"
	tar -czf threads_archive.tar.gz output*.txt 2>/dev/null
	mv threads_archive.tar.gz ../
	echo "Archived Threads' results"
	sort_and_count_new_level $r1 $t1
	sort_and_count_new_level $r2 $t2
	echo "Content of BOTH archives was sorted and saved to the new location"
	loc=`find $SCRIPT_HOME -iname sorted$r1.txt`
	archive_loc=`find $SCRIPT_HOME -iname processes_archive.tar.gz`
	dive_to_level $r1
	dest=`pwd`
	tar -xzf $archive_loc 2>/dev/null
	rm $archive_loc
	mv $loc .
	tar -C ./ -czf $dest/processes_archive.tar.gz *.txt 2>/dev/null
	mv $dest/processes_archive.tar.gz ../

	loc=`find $SCRIPT_HOME -iname sorted$r2.txt`
	archive_loc=`find $SCRIPT_HOME -iname threads_archive.tar.gz`
	dive_to_level $r2
	dest=`pwd`
	tar -xzf $archive_loc 2>/dev/null
	rm $archive_loc
	mv $loc .
	tar -C ./ -czf $dest/threads_archive.tar.gz *.txt 2>/dev/null
	mv $dest/threads_archive.tar.gz ../
	echo "New elements were added to both of archives"
	dive_to_level $a3
	destin=`pwd`
	archive_location=`find $SCRIPT_HOME -iname processes_archive.tar.gz`
	tar -xzf $archive_location -C $destin 2>/dev/null
	echo "Processes' archive was extracted at $destin"
	dive_to_level $a4
	destin=`pwd`
	archive_location=`find $SCRIPT_HOME -iname threads_archive.tar.gz`
	tar -xzf $archive_location -C $destin 2>/dev/null
	echo "Threads' archive was extracted at $destin"
	echo ""
}



main
