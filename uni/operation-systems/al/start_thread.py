import time
import sys, os
import numpy as np
from datetime import datetime, timedelta
from threading import Thread

def _task(context, filename):
	t_0 = datetime.now()
	outfile = str("./output") + str(os.getpid()) + ".txt"
	command = "grep -n " + context + " " + filename + " > " + outfile
	os.system(command)
	t_1 = datetime.now()
	with open(outfile, "a+") as f:
		f.write("Execution time: %s\n" % str(t_1 - t_0))
		f.close()
	

if __name__ == "__main__":
	thread = Thread(target=_task, args=(str(sys.argv[1]), sys.argv[2]))
	thread.start()
	thread.join()



