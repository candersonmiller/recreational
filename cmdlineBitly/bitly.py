#!/usr/bin/env python
# encoding: utf-8
"""
bitly.py

Created by C. Anderson Miller on 2009-01-28.
Copyright (c) 2009 __MyCompanyName__. All rights reserved.
"""

import sys
import os
import urllib
import urllib2
import base64
from xml.dom import minidom


def getText(nodelist):
    rc = ""
    for node in nodelist:
        if node.nodeType == node.TEXT_NODE:
            rc = rc + node.data
    return rc

def shorten(url):
	api_key = "your api key goes here"
	username = "your username goes here"
	url = "http://api.bit.ly/shorten?version=%s&format=%s&longUrl=%s&login=%s&apiKey=%s" % ("2.0.1","xml",url,username,api_key)
	request = urllib2.Request(url)
	opener = urllib2.build_opener()
	feeddata = opener.open(request).read()
	opener.close()
	hashes = []
	dom = minidom.parseString(feeddata)
	hsh = dom.getElementsByTagName('hash')
	for h in hsh:
		hashes.append(getText(h.childNodes))
	for ha in hashes:
		return "http://bit.ly/%s" % ha

def main():
	arg1 = False
	try:
		arg1 = sys.argv[1]
	except IndexError:
		print "proper usage is ./bitly.py http://www.whateverwebsitey.com/a/longname.html"
		exit()
	print shorten(arg1)

if __name__ == '__main__':
	main()

