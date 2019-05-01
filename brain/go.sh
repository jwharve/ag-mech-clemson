#!/bin/bash

# turn off power
./p 0

# look for open minicom programs
MINICOM=`ps -a | grep minicom | awk -F " " '{print $1}'`

# if a minicom is open, kill it
if test -z $MINICOM
then
	echo "no minicoms"
else
	kill -s SIGTERM $MINICOM
	echo "killed a minicom"
fi

# upload to pi
make upload
