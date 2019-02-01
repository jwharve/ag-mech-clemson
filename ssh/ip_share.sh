#!/bin/bash

# Based on script written by Jake Ammons

#Give OS time to connect to wifi
sleep 1m

#Open repo and get upates, stashing any uncommitted changes
cd /home/pi/ag-mech-clemson/
git add *
git stash
git fetch --all
git reset --hard origin/master

#Move to ssh folder
cd ssh

#Write IP address and timestamp to repo and push update
ifconfig wlan0 | grep "inet " | awk -F'[: ]+' '{ print $3 }' > ip_address
date > last_updated
git add *
git commit -m 'updated ip address'
git push
