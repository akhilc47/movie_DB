# -*- coding: utf-8 -*-

import os, sys
import shutil
import json
import urllib2
import time
import io

finfo = io.open('info.txt', 'a', encoding = 'utf-8') # Some names have special characters, so encode it in utf-8
fmovies = open('movies_english.txt', 'r')

moviedb_api_key = 'xxx'
omdb_api_key = 'xxx'

for _ in xrange(303): # Look how many lines in movies.txt already have data for them grepped
    next(fmovies)     # Skip that many lines

for line in fmovies:
    line = line.strip()
    if "Series" in line:
       dir = line.split('\\')[2]
    else:
        dir = line.split('\\')[1]
    print "---------------", dir, "---------------"
    movie_name_plus = '+'.join(dir.split('[')[0].split())
    time.sleep(2)
    num_tries = 1
    while num_tries < 4:    # If urlopen times out retry 2 more times
        try:
            response = urllib2.urlopen('http://www.omdbapi.com/?apikey='+omdb_api_key+'&t='+movie_name_plus).read()
        except urllib2.HTTPError:
            time.sleep(30)  # Wait 30 second before trying again
            num_tries += 1
            continue
        except urllib2.URLError:
            time.sleep(30)  # Wait 30 second before trying again
            num_tries += 1
            print 'urllib2.URLError', 'URL: ', 'http://www.omdbapi.com/?apikey='+omdb_api_key+'&t='+movie_name_plus
            continue
        except socket.error:
            time.sleep(30)  # Wait 30 second before trying again
            num_tries += 1
            continue
        js_response = json.loads(response)
        if "Error" in js_response.keys():
            print dir, js_response["Error"]
            finfo.write(line+'\t'+js_response["Error"]+"\n")
        else:
            print js_response["Title"].encode('utf-8')
            print js_response["imdbRating"].encode('utf-8')
            print js_response["Director"].encode('utf-8')
            print js_response["Genre"].encode('utf-8')
            print js_response["Year"].encode('utf-8')
            rt_rating = unicode(0)
            for rating in js_response["Ratings"]:
                if rating["Source"] == "Rotten Tomatoes":
                    rt_rating = rating["Value"]
            print js_response["Actors"].encode('utf-8')
            print js_response["Poster"].encode('utf-8')
            finfo.write(unicode(line)+'\t'+js_response["Title"]+\
                '\t'+js_response["Director"]+'\t'+js_response["Actors"]+'\t'+\
                js_response["Year"]+'\t'+js_response["Genre"]+'\t'+\
                js_response["imdbRating"]+'\t'+rt_rating+"\n")
            if "http" in js_response["Poster"]:
                with open("posters/"+dir+".jpg","wb") as fimg:
                    fimg.write(urllib2.urlopen(js_response["Poster"]).read())
        break # break out of the while loop, which is meant for retries in case of HTTP error

finfo.close()
fmovies.close()

#response = urllib2.urlopen('https://api.themoviedb.org/3/search/movie?api_key='+api_key+'&query=Jack+Reacher').read()
#js_response = json.loads(response)

#for i in xrange(js_response['total_results']):
#    print js_response['results'][i]['title']
