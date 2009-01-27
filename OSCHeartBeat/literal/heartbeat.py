#!/usr/bin/env python
# encoding: utf-8
"""
oscHeart.py

Created by C. Anderson Miller on 2009-01-27.
Copyright (c) 2009 __MyCompanyName__. All rights reserved.
"""

import sys
import os
import osc

def heartBeat(*msg):
	if( ( msg[0][2]) % 2 > 0):
		print "thump"
	elif(msg[0][2] % 2 < 1):
		print "thud"

def main():
	osc.init()
	osc.listen("127.0.0.1",9001)
	osc.bind(heartBeat, "/beat")


if __name__ == '__main__':
	main()

