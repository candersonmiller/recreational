#!/usr/bin/env python
# encoding: utf-8
"""
newtorrent.py

Created by C. Anderson Miller on 2009-09-28.
Copyright (c) 2009 SubmarineRich. All rights reserved.
"""

import sys
import os
import urllib2
import MySQLdb
from BeautifulSoup import BeautifulSoup
from BeautifulSoup import SoupStrainer

tvshows = ("House", "Family Guy", "The Cleveland Show", "Heroes", "True Blood",\
 			"Curb Your Enthusiasm", "Mad Men", "Entourage", "Dollhouse", "Californication",\
 			"The Big Bang Theory", "How I Met Your Mother", "Fringe", "American Dad",\
			"The Office")

falsePositives = ("Desperate Housewives", "Season", "mkv")  #things that are showing up in torrents you decide you don't want

url = "http://thepiratebay.org/top/205"  # catch the top 100 TV shows on piratebay


# This script definitely requires BeautifulSoup and Mysql to run.
# BeautifulSoup can be found here http://www.crummy.com/software/BeautifulSoup/
# probably takes os x dev tools too
# mysql for python should be gettable via instructions here 
# (I'm on Snow Leopard, I'm assuming you are too) http://www.davidcramer.net/code/57/mysqldb-on-leopard.html
# Also - you'll need wget for OS X  http://www.statusq.org/archives/2008/07/30/1954/

#after installing sql, install and run as root this sequence of things
#CREATE DATABASE torrent;
#CREATE USER 'torrent'@'localhost' IDENTIFIED BY 'assface';
#GRANT ALL PRIVILEGES on torrents.* TO 'torrent'@'localhost' WITH GRANT OPTION;
#CREATE TABLE torrents(id INT AUTO_INCREMENT PRIMARY KEY, link VARCHAR(300));



def checkForDupesAndReturnNewLinks(listOfLinks):
	conn = MySQLdb.connect(
		host = "localhost",
		user = "torrent",
		passwd = "assface",
		db = "torrent")
	cursor = conn.cursor()
	listToDownload = list()
	for link in listOfLinks:
		cursor.execute( "SELECT * FROM torrents WHERE link=\"%s\"" % link)
		while(1):
			row = cursor.fetchone()
			if(row == None):
				listToDownload.append(link)
				cursor.execute("INSERT INTO torrents VALUES (id, \"%s\")" % link)
				break
			else:
				break
	return listToDownload
	
def main():
	request = urllib2.Request(url) #create a request
	request.add_header('User-Agent', 'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.5; en-US; rv:1.9.0.4) Gecko/2008102920 Firefox/3.0.4') #http://whatsmyuseragent.com/
	opener = urllib2.build_opener()
	feeddata = opener.open(request).read() #feeddata is the html data received
	opener.close()
	#request.close()
	soup = BeautifulSoup(''.join(feeddata)) #make it into beautifulsoup
	downloadLinks = soup.findAll("a",{"title":"Download this torrent"})  #find all the torrent links
	
	listOfPotentials = list()
	
	for dl in downloadLinks:
		d = str(dl)
		split1 = d.split("<a href=\"")
		split2 = split1[1].split("\" title")
		torrentURL = split2[0]
		for show in tvshows:
			altshow = show.replace(' ','.')
			falsePositive = False
			for fp in falsePositives:
				donottation = fp.replace(' ','.')
				if(torrentURL.count(donottation)):
					falsePositive = True
			if(torrentURL.count(altshow) and not falsePositive ):
				listOfPotentials.append(torrentURL)
		
	listOfActuals = checkForDupesAndReturnNewLinks(listOfPotentials)
	print listOfActuals
	
	for item in listOfActuals:  # got get those links and put them into the running folder!
		os.system("wget %s" % item)
		
	
if __name__ == '__main__':
	main()

