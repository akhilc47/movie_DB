'''
This section will find all the files which are greater than 100MB,
including files in subdirectories
'''
import os
import subprocess

path = 'E:/FILMS/ENGLISH/'



def getLength(filename):
  result = subprocess.Popen(["ffprobe", filename],
    stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
  return [x for x in result.stdout.readlines() if "Duration" in x]

count = 0
for root, dirnames, filenames in os.walk(path):
    for file in filenames:
        if os.stat(os.path.join(root,file)).st_size > 100000000:
            count += 1
            print count, os.path.join(root,file)

'''
Reading only directories of movies will give the names of all movies in a folder.
This means, skipping 6+, Series, Malayalam etc.
'''
import os, sys

path = 'E:/FILMS/English/'
fmovies = open('movies.txt', 'w')
for root, dirnames, filenames in os.walk(path):
    for dir in dirnames:
        if any(s for s in ["Series", "6+", "7+", "8+", "9+", "English", "Malayalam",\
           "Other Indian", "Korean and Other", "Unsorted"] if s in dir):
            continue
        else:
            fmovies.write(os.path.join(root,dir)+'\n')

fmovies.close()


import os, sys
import shutil

'''
This section will find movie files(size check should ignore subtitle files) which are not
in a folder and move them to a folder which has same name as the original file
'''

path = "E:/FILMS/ENGLISH/7+"

for files in os.listdir(path): # all files and folders
    if not os.path.isdir(path+"/"+files): # Ignore directories
        if os.stat(path+"/"+files).st_size > 100000000: # Ignore subtitles and any other small files
            new_dir_name = path+"/"+files[:-4] # Remove the extension for directory
            new_dir_name = new_dir_name.strip()
            os.makedirs(new_dir_name)
            print files, os.stat(path+"/"+files).st_size
            shutil.move(path+"/"+files, new_dir_name+"/"+files) # Move to new directory
            print "\n"

''' This section will grep the folder names, which need to be rectified, and correct them
'''

for files in os.listdir(path): # Loop over all files and folders
    print files
    badline = files.replace('.', ' ').replace('(', ' ').replace(')', ' ').replace('[', ' ').replace(']', ' ').split()
    goodline = ""
    for token in badline:
        if ((len(token) == 4) and ((token[:2] == '19') or (token[:2] == '20'))):
            goodline += '['+token+'] '
            break
        elif token.lower() in ['a', 'an', 'and', 'the', 'of', 'for', 'with', 'to']:
            goodline += token.lower()+' '
        elif '\'' in token:
            goodline += token[:token.find('\'')+1]
            goodline += token[token.find('\'')+1:].lower()+' '
        else:
            goodline += token.title()+' '
    goodline = goodline[0:1].capitalize()+goodline[1:]
    if '720p' in badline:
       goodline += '['+'720p'+']'
    elif ('1080p' in badline):
        goodline += '['+'1080p'+']'
    print goodline.strip()+"\n"
    os.rename(path+'/'+files, path+'/'+goodline)