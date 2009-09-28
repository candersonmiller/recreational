#!/usr/bin/env python
# encoding: utf-8
"""
untitled.py

Created by C. Anderson Miller on 2009-01-19.
Copyright (c) 2009 __MyCompanyName__. All rights reserved.
"""

import sys
import os
import time
import MySQLdb
import urllib2
from BeautifulSoup import BeautifulSoup
from BeautifulSoup import SoupStrainer
from pytorrent import TorrentClient

#CREATE DATABASE torrent;
#CREATE USER 'torrent'@'localhost' IDENTIFIED BY 'assface';
#grant all privileges on torrent.* to 'torrent'@'localhost' WITH GRANT OPTION;




def getPirateBay():
	url = "http://thepiratebay.org/top/205"  # catch the top 100 TV shows on piratebay
	request = urllib2.Request(url) #create a request
	request.add_header('User-Agent', 'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.5; en-US; rv:1.9.0.4) Gecko/2008102920 Firefox/3.0.4') #http://whatsmyuseragent.com/
	opener = urllib2.build_opener()
	feeddata = opener.open(request).read() #feeddata is the html data received
	opener.close()
	#request.close()
	soup = BeautifulSoup(''.join(feeddata)) #make it into beautifulsoup
	soup.prettify() #correct errors
	return soup
	
	
def programs():
	programs = ["The Office", "House", "Fringe", "Bones", "30 Rock", "Big Love", "Terminator"]
	return programs
	
	
def torrentList(tvshows, piratebaypage):
	conn = MySQLdb.connect(
		host = "localhost",
		user = "torrent",
		passwd = "assface",
		db = "torrent")
	cursor = conn.cursor()
	listToDownload = list()
	
	links = piratebaypage.findAll("a", {"class" : "detLink"})
	for link in links:
		linktext = "%s" % link
		for show in tvshows:
			altshow = show.replace(' ', '.')
			if( (linktext.count(show) or linktext.count(altshow) )and not linktext.count("Housewives") and not linktext.count("Season")):
				#print linktext
				text = linktext.split('\"')
				url = "http://www.thepiratebay.org" + text[1]
				#print url
				####If the link is already in the database, skip it, otherwise, listToDownload.append(torrentlink)
				cursor.execute( "SELECT * FROM torrents WHERE link=\"%s\"" % url)
				while(1):
					row = cursor.fetchone()
					if(row == None):
						listToDownload.append(url)
						cursor.execute("INSERT INTO torrents VALUES (id, \"%s\")" % url)
						break
					else:
						break
	return listToDownload



def torrentLinkFromUrl(url):
	request = urllib2.Request(url) #create a request
	request.add_header('User-Agent', 'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.5; en-US; rv:1.9.0.4) Gecko/2008102920 Firefox/3.0.4') #http://whatsmyuseragent.com/
	opener = urllib2.build_opener()
	feeddata = opener.open(request).read() #feeddata is the html data received
	opener.close()
	#request.close()
	soup = BeautifulSoup(''.join(feeddata)) #make it into beautifulsoup
	soup.prettify() #correct errors
	downloadLinks = soup.findAll("a", {"title" : "Download this torrent"})
	first = downloadLinks[0]
	firstlink = "%s" % first
	linksplit = firstlink.split('\"')
	return linksplit[1]
	
def commandLineFormat(url):
	first = url.replace('[', '\[')
	second = first.replace(']', '\]')
	third = second.replace('!','\!')
	
	return third
	
def getFileName(url):
	filename = "%s" % url
	linksplit = filename.split('/')
	filename = ""
	for item in linksplit:
		filename = item
		
	return filename
		
def main():
	tvshows = programs()
	piratebaypage = getPirateBay()
	client = TorrentClient("localhost", 9091)
	
	
#	while(1):
#		listToDownload = torrentList(tvshows, piratebaypage)
#		for url in listToDownload:
#			linkUrl = torrentLinkFromUrl(url)
#			client.add_torrent(linkUrl)
#		
#		
#		for torrent in client.torrents:
#			torrent.start()
#	
#		print "one more cycle"
#		seconds = 60 * 30
#		time.sleep(seconds)
	
		
		
		
		
	#for item in listToDownload:
	#	print item
	#for item in listToDownload:
	#	"wget %s"item






if __name__ == '__main__':
	main()

