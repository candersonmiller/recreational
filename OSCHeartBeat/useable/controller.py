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


def heartBeat(*msg):
	if(msg[0][2] > 0):
		global last_beat
		last_beat = time.clock()
		#print last_beat
		#last beat = now

def main():
	osc.init()
	osc.listen("127.0.0.1",9001)
	osc.bind(heartBeat, "/beat")
	while(1):
		global last_beat
		time_diff = (time.clock() - last_beat)
		print time_diff;
		time.sleep(0.1);
		#if timedelta between last beat and right now is greater than some BIG DELTA which is the overall time difference, restart the program



if __name__ == '__main__':
	main()

