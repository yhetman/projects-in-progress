import time
import os
import numpy as np
import random
from datetime import datetime, timedelta
from functools import partial
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor
import _thread
import threading
from threading import current_thread, Lock
from processes_implementation import read_4bytes, count_timedelta, make_subsample,several_files



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


def multithreading_start():
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
	multithreading_start()