#!/bin/bash
while true;do
	./gen
	./b
	./b1
	if diff b.out b1.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done