import urllib, urllib2
from lxml import html
import os
import requests
import urlparse
import re

Path = './Images/'
UrlWebPage = 'https://www.youtube.com'
Content = urllib2.urlopen(UrlWebPage).read() #save as HTML code
UrlImages = re.findall('img .*?src="(.*?)"', Content)
count = 1
if UrlImages:
    if not os.path.exists(Path): #create new folder
        os.mkdir(Path)
    TheAbsolutePath = [urlparse.urljoin(UrlWebPage, url) for url in UrlImages]
    for url in TheAbsolutePath: #download img
        print url
         
        image = requests.get(url)
        count += 1
        fil = open(Path + str(count) + url.split('/')[-1], 'wb')
        fil.write(image.content)
        fil.close()
    
