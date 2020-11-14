dir=my_virtual_dir

home_path=/mnt/DATA/projects-in-progress/uni/operation-systems/bash-scripting

virtdir=$home_path/$dir

script_path=/mnt/DATA/projects-in-progress/uni/operation-systems/processes_threads

R=12

N1=1
N2=1

r1=10
r2=12

a1=9
a2=11
a3=5
a4=6

t1=-9
t2=-8

folder=folder

function check()
{
	if [[ ! -e $1 ]] ; then
		mkdir $1
	elif [[ ! -d $1 ]] ; then
		echo "$1 already exists but is not a directory" 1>&2
	fi
	return 0
}


function recur_dirs ()
{
	counter=1
	while true
	do
		mkdir -p ./$counter$folder
		cd ./$counter$folder
		counter=$((counter + 1))
		if [[ $counter -gt $1 ]] ; then
			break 
		fi
	done
}


function get_dir ()
{
	cd $virtdir
	counter=1
	while true;
	do
		cd ./$counter$folder
		counter=$((counter + 1))
		if [[ $counter -gt $1 ]] ; then
			break
		fi
	done
}


function start_script()
{
	get_dir $1
	sudo dd if=/dev/urandom of=./file bs=4 count=10000
	$2 $3 1>/dev/null
	rm file
}

function create_archive()
{
	get_dir $1
	tar -czf ../archive_from_$1_on_$2_level.tar.gz ./* 
}


function sort_and_locate()
{
	get_dir $1
	locate $2
	destination=`pwd`
	get_dir $1
	cat ./*.txt > input.txt 
	sort -nr -o $destination/output$1.txt input.txt
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
	location=`find $virtdir -iname *$1.txt`
	archive_location=`find $virtdir -iname *$1_on_$2*.tar.gz`
	mkdir /tmp/tempo/
	tar -zxf $archive_location -C /tmp/tempo/ 2>/dev/null
	mv $location /tmp/tempo/
	get_dir $1
	tar -czf ../archive_from_$1_on_$2_level.tar.gz -C /tmp/tempo/* 2>/dev/null
	rm -rf /tmp/tempo
}


function extract_archive()
{
	get_dir $2
	destination=`pwd`
	archive_location=`find $virtdir -iname *_on_$1*.tar.gz`
	echo $destination
	tar -zxf $archive_location -C $destination 2>/dev/null

}

function finish()
{
	echo "Script has just finished its work! Thanks for using our service :)" \n

}
check $dir

if [[ -e $dir ]]; then
	cd $dir
fi

PWD=`pwd`

recur_dirs $R

start_script $r1 $script_path/processes_implementation.py $N1
start_script $r2 $script_path/threads_implementation.py $N2

create_archive $r1 $a1
create_archive $r2 $a2

sort_and_locate $r1 $t1
sort_and_locate $r2 $t2

add_file_to_archive $r1 $a1
add_file_to_archive $r2 $a2

extract_archive $a1 $a3
extract_archive $a2 $a4

finish