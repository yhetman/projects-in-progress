import os
import sys
from multiprocessing import Process
import time
from datetime import datetime, timedelta

def _task(context, filename):
	t_0 = datetime.now()
	outfile = str("./output")+ str(os.getpid()) + ".txt"
	command = "grep -n " + context + " " + filename + " > " + outfile
	os.system(command)
	t_1 = datetime.now()
	with open(outfile, "a+") as f:
		f.write("Execution time: %s\n" % str(t_1 - t_0))
		f.close()
	

if __name__ == "__main__":
	proc = Process(target=_task, args=(str(sys.argv[1]), sys.argv[2]))
	proc.start()
	proc.join()
