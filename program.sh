#!/bin/bash
if [ $# -gt 1 ]; then
	if [ -b "$1" ]; then
		sudo mount "$1" /mnt
		sudo cp "$2" /mnt
		sync
		sudo umount /mnt
	else
		echo "$1 not a block device"
	fi
else
	echo "Usage: /dev/sdx code.hex"
fi
