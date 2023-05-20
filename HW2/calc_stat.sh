#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Wrong number of arguments" 1>&2
	exit 1
fi

course_num=$(basename "$1")

if ! [[ -f "${course_num}.txt" ]]; then
	echo "Course not found" 1>&2
	exit 1
fi
#Checks that xxxxxx.txt exits

if [[ -d "${course_num}_stat" ]]; then
	rm -rf "${course_num}_stat"
fi
#Checks if a stat folder exists, and delets it and all its contents if it does

mkdir "${course_num}_stat"

for file in mean.exe median.exe min.exe max.exe; do

	"./$file" < "${course_num}.txt" >> "statistics.txt"
done
#loop that runs each exe file
#after running, it adds the result to the output file



./hist.exe -nbins 20 < "${course_num}.txt" > "pass.txt"

pass=$(awk -F '\t' '$1 > 55 {sum += $2 } END {print sum} ' pass.txt)
total=$(awk -F '\t' '{sum += $2} END {print sum}' pass.txt)
pass_percent=$(expr $pass \* 100 / $total)
#calculates the amount of students who passed and total valid grades

rm pass.txt
#deleting intermediate file

echo "$pass_percent%" >> "statistics.txt"

./hist.exe < "${course_num}.txt" > "histogram.txt"
#Compiles and runs histogram 

mv "statistics.txt" "${course_num}_stat"
mv "histogram.txt" "${course_num}_stat"
#moving the files to the folder













