import os
import subprocess
import sys

subprocess.call('make')
subprocess.call(['./gear_params']+sys.argv)

