#!/usr/bin/env python
# encoding: utf-8
"""
totumblr.py

Created by C. Anderson Miller on 2009-01-22.
Copyright (c) 2009 __MyCompanyName__. All rights reserved.
"""


import os
from tumblr import Api
import sys


BLOG='tumblrusername.tumblr.com'
USER='tumblremailaddress@gmail.com'
PASSWORD='password'

# python-tumblr comes from http://code.google.com/p/python-tumblr/
# and sudo easy_install simplejson first


def main():
	if len(sys.argv) != 2:
		print "Usage: ./totumblr.py <photofile>"
		sys.exit(-1)
	photo_filename = sys.argv[1]
	#data1 = open(photo_filename,'rb').read()
	#print data1
	api = Api(BLOG,USER,PASSWORD)
	post = api.write_photo(data=photo_filename)
	print "Published: ", post['url']

if __name__ == '__main__':
	main()

