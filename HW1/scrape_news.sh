#!/bin/bash

site="https://ynetnews.com/category/3082"

data=$(wget --no-check-certificate -O - $site 2>/dev/null)

articles=$(echo "$data" | \
		   grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+" | \
		   sort | uniq)
#pulls all the articles, sorts them, and returns only the unique 

echo "$articles" | wc -l >> results.csv

 for article in $articles; do 

 	curr_article=$(wget --no-check-certificate -O - $article 2>/dev/null)

	Netanyahu=$(echo $curr_article | grep -ioP 'Netanyahu' | wc -l)
	Gantz=$(echo $curr_article | grep -ioP 'Gantz' | wc -l)
	Bennett=$(echo $curr_article | grep -ioP 'Bennett' | wc -l)
	Peretz=$(echo $curr_article | grep -ioP 'Peretz' | wc -l)

	#each variable counts the amount of times a name appears in the article

	if [[ $(($Netanyahu + $Gantz + $Bennett + $Peretz)) -eq 0 ]]; then
		echo "$article"", -" >> results.csv

	else
		echo "$article"", Netanyahu," "$Netanyahu"", Gantz," "$Gantz"", Bennett,"\
		"$Bennett"", Peretz" "$Peretz" >> results.csv
	fi


 done


