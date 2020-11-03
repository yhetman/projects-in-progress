#!/home/yhetman/anaconda3/bin/python3

import time
import os
import numpy as np
import random
import multiprocessing as mp
from datetime import datetime, timedelta
from multiprocessing import current_process
from functools import partial
from concurrent.futures import ProcessPoolExecutor
import sys

def input_file_names(num):
	files = []
	for i in range(num):
		new_file = "example" #str(input("Enter file name : "))
		if len(new_file) > 1:
			files.append(new_file)
		else:
			("No input")
			num += 1
	return files


def several_files():
	num = 1 #int(input("How many files to use? "))
	if num > 0:
		return input_file_names(num) , num
	else:
		print("Invalid input")
		exit()


def read_4bytes(filename):
	numbers = []
	with open(filename, 'br') as f:
		data = f.read(4)
		while data:
			number = int.from_bytes(data, "big", signed=True)
			numbers.append(number)
			data = f.read(4)
	return numbers


def count_frequency(sequence): 
	freq = {} 
	for item in sequence: 
		freq[item] = freq.get(item, 0) + 1
	v_list = list(freq.values())
	k_list = list(freq.keys())
	max_val = max(v_list)
	key = k_list[v_list.index(max_val)]
	return key, max_val


def random_choices(x, tries):
	sequence = []
	while len(sequence) < tries:
		sequence.append(random.choice(x))
	return sequence


def make_subsample(num_items, x):
	resulting_sequence = []
	for _ in range(num_items):
		number_of_tries = num_items**2
		sequence = random_choices(x, number_of_tries)
		key, max_val = count_frequency(sequence)
		resulting_sequence.append(str(key))
		x.remove(key)
		random.shuffle(x)
	return resulting_sequence


def all_things_together(filename, num_items):
	start_time = datetime.now()
	arr_signed_ints, time_for_reading = count_timedelta(read_4bytes, args=[filename])
	subsample, time_for_sampling =  count_timedelta(make_subsample, args=[num_items, arr_signed_ints])
	pid = int(os.getpid())
	process_file = str(current_process().name)+"-"+ str(pid)+ ".txt"
	res = [i for i in subsample if int(i)%(3*pid) == 0]
	with open(process_file, "a+") as f:
		f.write("Process ID : %d\nParent ID : %d\n" % (pid, os.getppid()))
		f.write("\n".join(subsample))
		f.write("\nNumbers which remainders equal 0 when divided by 3 * PID : %s\n" % ("\t".join(res)))
		f.write("Execution time: %s\nTime spent for reading file: %s\nTime spent fot sampling: %s\n"
            % (str(datetime.now()- start_time)
            	, str(time_for_reading), str(time_for_sampling)))
		f.close()
	return 1


def count_timedelta(function, args=[]):
	t_0 = datetime.now()
	resulting = function(args[0]) if len(args) == 1 else function(args[0], args[1])
	t_1 = datetime.now()
	delta_t = t_1- t_0
	return resulting, delta_t


def multiprocessing_start():
	if len(sys.argv) > 1:
		PROCESSES = int(sys.argv[1])
	else:
		PROCESSES = 8
	N = 100
	files, number_of_files = several_files()
	parameters = [(i, N) for i in files]
	if number_of_files > 1: PROCESSES = number_of_files
	if number_of_files == 1: parameters *= PROCESSES
	parfunction = partial(count_timedelta, all_things_together)
	with ProcessPoolExecutor(PROCESSES) as pool:
		pool.map(parfunction, parameters)

if __name__ == "__main__":
	multiprocessing_start()
