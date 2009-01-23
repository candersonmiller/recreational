#!/usr/bin/env python
# encoding: utf-8
"""
untitled.py

Created by C. Anderson Miller on 2009-01-23.
Copyright (c) 2009 __MyCompanyName__. All rights reserved.
"""

import sys
import os
import re
from ftplib import FTP
from tumblr import Api


BLOG='tumblrusername.tumblr.com'
USER='tumblremail@gmail.com'
PASSWORD='pass'

# python-tumblr comes from http://code.google.com/p/python-tumblr/
# and sudo easy_install simplejson first


def main():
	if len(sys.argv) != 2:
		print "Usage: tumbl <photofile>"
		sys.exit(-1)

	photo_filename = sys.argv[1]
	parts = photo_filename.split('.')
	file_extension = parts[1]


	ftp = FTP('www.fakemachine.com')
	ftp.login('serveradmin@fakemachine.com','password')
	ftp.cwd('/domains/fakemachine.com/html/tumblrimages/')
	text = ftp.retrlines('list')


	m = re.search('\d+ matches', text)
	match = m.group(0)
	parts = match.split(' ')
	file_number = int(parts[0]) + 1

	remote_filename = "%d.%s" % (file_number,file_extension)
	fp = open(photo_filename,'rb')
	ftp.storbinary('STOR %s' % remote_filename, fp) # Send the file

	fp.close()
	ftp.quit()

	image_url = "http://www.fakemachine.com/tumblrimages/%s" % remote_filename
	api = Api(BLOG,USER,PASSWORD)
	post = api.write_photo(source=image_url)
	print "Published: ", post['url']


if __name__ == '__main__':
	main()

