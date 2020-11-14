#!/home/yhetman/anaconda3/bin/python3

import time
import os
import sys
import numpy as np
import random
from datetime import datetime, timedelta
from functools import partial
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor
import _thread
import threading
from threading import current_thread, Lock


def input_file_names(num):
	files = []
	for i in range(num):
		new_file = "./file" #str(input("Enter file name : "))
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


def count_timedelta(function, args=[]):
	t_0 = datetime.now()
	resulting = function(args[0]) if len(args) == 1 else function(args[0], args[1])
	t_1 = datetime.now()
	delta_t = t_1- t_0
	return resulting, delta_t



class myThread(threading.Thread):
	def __init__(self, indx, parameters, lock):
		threading.Thread.__init__(self)
		self.threadID = threading.current_thread().ident
		self.name = "Thread-" + str(indx)
		self.filename, self.number = parameters
		self.lock = lock
	def run(self):
		parfunction = partial(count_timedelta, _thread_task)
		print ("Starting " + self.name + "...\n")
		parfunction([self])
		print ("Exiting " + self.name + "...\n")


def _thread_task(myThread):
	myThread.lock.acquire()
	filtering(myThread)
	myThread.lock.release()


def filtering(myThread):
	start_time = datetime.now()
	arr_signed_ints, time_for_reading = count_timedelta(read_4bytes, args=[myThread.filename])
	subsample, time_for_sampling =  count_timedelta(make_subsample, args=[myThread.number, arr_signed_ints])
	res = [i for i in subsample if int(i)%(3*myThread.threadID) == 0]
	with open(myThread.name +".txt", "a+") as f:
		f.write("Thread ID : %d\nParent ID : %d\n" % (myThread.threadID ,os.getppid()))
		f.write("\n".join(subsample))
		f.write("\nNumbers which remainders equal 0 when divided by 3 * PID : %s\n" % ("\t".join(res)))
		f.write("Execution time: %s\nTime spent for reading file: %s\nTime spent fot sampling: %s\n"
			% (str(datetime.now()- start_time), str(time_for_reading), str(time_for_sampling)))
		f.close()
	return 1


def create_threads(parameters):
	lock = threading.Lock() 
	threads = [myThread(indx, parameter, lock)
		for indx, parameter in enumerate(parameters)]
	for thread in threads:
		thread.start()
	return threads


def main():
	if len(sys.argv) > 1:
		THREADS = int(sys.argv[1])
	else:
		THREADS = 8
	N = 100
	files, number_of_files = several_files()
	parameters = [(i, N) for i in files]
	if number_of_files > 1: THREADS = number_of_files
	if number_of_files == 1: parameters *= THREADS
	threads = create_threads(parameters)
	for thread in threads:
		thread.join()
	print ("Exiting to the main thread")


if __name__ == "__main__":
	main()