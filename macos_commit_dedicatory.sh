#!/bin/bash

tail -c +4  /Users/camilo/Library/Application\ Support/ca2/system/config/todo/obs.txt > /Volumes/apple/Dropbox/ca2/macded.txt
echo >> /Volumes/apple/Dropbox/ca2/macded.txt
tail -c +4  /Volumes/apple/Dropbox/ca2/DedBody.txt >> /Volumes/apple/Dropbox/ca2/macded.txt
echo >> /Volumes/apple/Dropbox/ca2/macded.txt
tail -c +4  /Volumes/apple/Dropbox/ca2/bilbo_macos.txt >> /Volumes/apple/Dropbox/ca2/macded.txt

open /Volumes/apple/Dropbox/ca2/macded.txt


