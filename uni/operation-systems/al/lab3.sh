#!/bin/bash


folder=LABA3_RESULTS
desktop=/Users/developer/Desktop/
worker_dir=$desktop/$folder

echo "V A R I A N T  : 1"

R=8

N1=40
N2=55

r1=6
r2=8

a1=5
a2=7
a3=3
a4=4

t1=-3
t2=-2


function recur_dirs ()
{
	counter=1
	while true
	do
		mkdir -p ./$counter
		cd ./$counter
		counter=$((counter + 1))
		if [[ $counter -gt $1 ]] ; then
			break 
		fi
	done
}

function checker ()
{
	if [[ ! -e $1 ]] ; then
		mkdir -p $1
	elif [[ ! -d $1 ]] ; then
		echo "$1 already exists but is not a directory"
	fi
	if [[ -e $1 ]]; then
		cd $1
	fi
}


function get_dir ()
{
	cd $worker_dir
	counter=1
	while true;
	do
		cd ./$counter
		counter=$((counter + 1))
		if [[ $counter -gt $1 ]] ; then
			break
		fi
	done
}


function create_archive()
{
	get_dir $1
	tar -czf archive_from_$1_on_$2_level.tar.gz ./output*.txt 2>/dev/null
	mv archive_from_$1_on_$2_level.tar.gz ../
}


function sort_and_locate()
{
	get_dir $1
	locate $2
	destination=`pwd`
	get_dir $1
	cat ./output*.txt > input.txt  2>/dev/null
	sort -nr -o $destination/results_of_sort$1.txt input.txt
	rm input.txt
}

function locate()
{
	counter=$1
	if [[ $counter -gt 0 ]] ; then
		curr_dir=${PWD##*/}
		curr_dir_nb=`cut -b 1,2 $curr_dir`
		counter=`expr $curr_dir_nb + $1`
		get_dir $counter
	elif [[ $counter -lt 0 ]] ; then
		while true ;
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
	loc=`find $worker_dir -iname *results_of_sort$1.txt`
	archive_loc=`find $worker_dir -iname *archive_from_$1_*.tar.gz`
	get_dir $1
	dest=`pwd`
	tar -xzf $archive_loc  2>/dev/null
	rm $archive_loc
	mv $loc .
	tar -C ./ -czf $dest/archive_from_$1_on_$2_level.tar.gz *.txt 2>/dev/null
	mv $dest/archive_from_$1_on_$2_level.tar.gz ../
}


function extract_archive()
{
	get_dir $2
	destin=`pwd`
	archive_location=`find $worker_dir -iname archive_from_*_on_$1_level.tar.gz`
	tar -xzf $archive_location -C $destin  2>/dev/null
}


function main()
{
	checker $worker_dir
	recur_dirs $R
	get_dir $r1
	seq $N1 | parallel python3 $desktop/start_process.py "im" $desktop/example
	echo "Processes done!"
	wait
	seq $N2 | parallel python3 $desktop/start_thread.py "lorem" $desktop/example
	echo "Threads done!"
	wait

	create_archive $r1 $a1
	create_archive $r2 $a2

	sort_and_locate $r1 $t1
	sort_and_locate $r2 $t2

	add_file_to_archive $r1 $a1
	add_file_to_archive $r2 $a2

	extract_archive $a1 $a3
	extract_archive $a2 $a4

	echo "Here are the resulting locaitons anf files :"
	ls -aRhl
}

main
