#!/usr/bin/env python
# encoding: utf-8
"""
controller.py

Created by C. Anderson Miller on 2009-01-27.
Copyright (c) 2009 __MyCompanyName__. All rights reserved.
"""

import sys
import os
import osc
import time


last_beat = time.clock()



def main():
	osc.init()
	i = 0
	while(1):
		osc.sendMsg("/beat",[i],"127.0.0.1",9001)
		i = i + 1
		time.sleep(0.5);
		#if timedelta between last beat and right now is greater than some BIG DELTA which is the overall time difference, restart the program

if __name__ == '__main__':
	main()

