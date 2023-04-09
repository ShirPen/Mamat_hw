#!/bin/bash

site="https://ynetnews.com/category/3082"

data=$(wget --no-check-certificate -O - $site 2>/dev/null)

articles=$(echo "$data" | \
		   grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+" | \
		   sort | uniq)
#pulls all the articles, sorts them, and returns only the unique 

echo "$articles" | wc -l

 for article in $articles; do 

	Netanyahu=$(curl -s "$article" | grep -o 'Netanyahu' | wc -l)
	Gantz=$(curl -s "$article" | grep -o 'Gantz' | wc -l)
	Bennett=$(curl -s "$article" | grep -o 'Bennett' | wc -l)
	Peretz=$(curl -s "$article" | grep -o 'Peretz' | wc -l)

	#each variable counts the amount of times a name appears in the article

	if [[ $(($Netanyahu + $Gantz + $Bennett + $Peretz)) -eq 0 ]]; then
		echo "$article"", -"

	else
		echo "$article"", Netanyahu," "$Netanyahu"", Gantz," "$Gantz"", Bennett,"\
		"$Bennett"", Peretz" "$Peretz"
	fi

#This is a Test

 done


