import os
from multiprocessing import Pool
import time
from datetime import datetime, timedelta
from concurrent.futures import ThreadPoolExecutor

def input_file_names(num):
	files = []
	for i in range(num):
		new_file = str(input("Enter file name : "))
		if len(new_file) > 1:
			files.append(new_file)
		else:
			("No input")
			num += 1
	return files


def _task(args):
	context, filename, index = args
	t_0 = datetime.now()
	outfile = filename + str(index) + ".txt"
	command = "grep -n " + context + " " + filename + " > " + outfile
	os.system(command)
	t_1 = datetime.now()
	with open(outfile, "a+") as f:
		f.write("Execution time: %s\n" % str(t_1 - t_0))
		f.close()
	

def main():
	args = []
	context = input("Input a context to search for : ")
	file_n = int(input("How many files to look throught? "))
	files = input_file_names(file_n)
	files *= 4
	for i, filename in enumerate(files):
		args.append((context, filename, i))
	variant = int(input("Enter 1 to use multiprocessing or press 2 to use multithreading : "))
	if variant == 1:
		with Pool(len(args)) as p:
			p.map(_task, args)
	if variant == 2:
		with ThreadPoolExecutor(max_workers=len(args)) as executor:
			executor.map(_task, args)
	else:
		print("Invalid variant")

if __name__ == "__main__":
	main()
