#!/bin/bash

DESKTOP="/home/user/Рабочий стол/"
GENDIR=general_directory
DIR=$DESKTOP$GENDIR
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

function get_dir ()
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
}

echo "Varaint = "$VARIANT


if [[ ! -e $DIR ]] ; then
		mkdir $DIR
	elif [[ ! -d $DIR ]] ; then
		echo "$DIR already exists but is not a directory" 1>&2
	fi
if [[ -e $DIR ]]; then
	cd $DIR
fi

index=1
while true;
do
	mkdir -p ./$index
	cd ./$index
	index=$((index + 1))
	if [[ $index -gt $R ]] ; then
		break 
	fi
done

get_dir $r1
python3 $DESKTOP/opanasenko_processes.py $N1

get_dir $r2
python3 $DESKTOP/opanasenko_threads.py $N2

get_dir $r1
tar -czf archive_from_$r1_on_$a1_level.tar.gz *.txt
mv archive_from_$r1_on_$a1_level.tar.gz ../

get_dir $r2
tar -czf archive_from_$r2_on_$a2_level.tar.gz *.txt
mv archive_from_$r2_on_$a2_level.tar.gz ../

get_dir $r1
index=$t1
if [[ $index -gt 0 ]] ; then
	curr_dir=${PWD##*/}
	curr_dir_nb=`cut -b 1,2 $curr_dir`
	index=`expr $curr_dir_nb + $t1`
	get_dir $index
elif [[ $index -lt 0 ]] ; then
	while true ;
	do
		cd ..
		index=$((index + 1))
		if [[ $index -eq 0 ]] ; then
			break
		fi
	done
fi

destination=`pwd`
get_dir $r1
cat ./*.txt > input.txt 
sort -nr -o $destination/output$r1.txt input.txt
rm input.txt

get_dir $r2
index=$t2
if [[ $index -gt 0 ]] ; then
	curr_dir=${PWD##*/}
	curr_dir_nb=`cut -b 1,2 $curr_dir`
	index=`expr $curr_dir_nb + $t2`
	get_dir $index
elif [[ $index -lt 0 ]] ; then
	while true ;
	do
		cd ..
		index=$((index + 1))
		if [[ $index -eq 0 ]] ; then
			break
		fi
	done
fi

destination=`pwd`
get_dir $r1
cat ./*.txt > input.txt 
sort -nr -o $destination/output$r2.txt input.txt
rm input.txt
loc=`find $DIR -iname *output$r1.txt`
archive_loc=`find $DIR -iname *archive_from_$r1_*.tar.gz`
get_dir $r1
dest=`pwd`
tar -xzf $archive_loc 
rm $archive_loc
mv $loc .
tar -C ./ -czf $dest/archive_from_$r1_on_$a1_level.tar.gz *.txt 
mv $dest/archive_from_$r1_on_$a1_level.tar.gz ../

loc=`find $DIR -iname *output$r2.txt`
archive_loc=`find $DIR -iname *archive_from_$r2_*.tar.gz`
get_dir $r2
dest=`pwd`
tar -xzf $archive_loc 
rm $archive_loc
mv $loc .
tar -C ./ -czf $dest/archive_from_$r2_on_$a2_level.tar.gz *.txt 
mv $dest/archive_from_$r2_on_$a2_level.tar.gz ../
get_dir $a3
destin=`pwd`
archive_location=`find $DIR -iname archive_from_*_on_$a1_level.tar.gz`
tar -xzf $archive_location -C $destin 
get_dir $a4
destin=`pwd`
archive_location=`find $DIR -iname archive_from_*_on_$a2_level.tar.gz`
tar -xzf $archive_location -C $destin 
