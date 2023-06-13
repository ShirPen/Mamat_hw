#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi

#cleans rules file
rule_file=$(cat $1 | sed 's/ //g' | \
                sed 's/#.*//' | \
                sed '/^$/d' | \
                sed 's/,\{2,\}/,/g' | \
                sed 's/^,//g')

##stores input packets into a variable
packets=$(cat);

# Array to store the valid packets
valid_packets=()

while read -r complex_rule; do

    IFS=',';

    read -ra rules <<< "$complex_rule"

    # Check if the line passes all four sub-rules
    valid_packets+=$(echo "$packets" | ./firewall.exe "${rules[0]}" | \
                                      ./firewall.exe "${rules[1]}" | \
                                      ./firewall.exe "${rules[2]}" | \
                                      ./firewall.exe "${rules[3]}" )
    valid_packets+=$'\n'

done <<< "$rule_file"

# Sort the valid packets and remove duplicates
sorted_unique_packets=$(echo "$valid_packets" | sort | uniq | sed 's/ //g' | sed '/^$/d' )

# Print the sorted and unique packets
echo "$sorted_unique_packets"


