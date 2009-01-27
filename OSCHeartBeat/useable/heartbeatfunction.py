#!/usr/bin/env python
# encoding: utf-8
"""
heartbeatfunction.py

Created by C. Anderson Miller on 2009-01-27.
Copyright (c) 2009 __MyCompanyName__. All rights reserved.
"""

import sys
import os
import time
import osc


def main():
	osc.init()
	i = 0
	while(1):
		osc.sendMsg("/beat",[i],"127.0.0.1",9001)
		i = i + 1
		time.sleep(1)


if __name__ == '__main__':
	main()

