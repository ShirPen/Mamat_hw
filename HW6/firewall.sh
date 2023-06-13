#!/bin/bash

if [[ $# -ne 2 ]]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi

rule_file="$1"
input_file="$2"

##stores input packets into a variable
packets=$(cat "$input_file");

# Array to store the valid packets
valid_packets=()

while read -r rule_line; do

    IFS=',';

    read -ra rules < "$rule_file"

    while read -r packets; do
        IFS=','
        read -ra packets < "$input_file"
    # Check if the line passes all four sub-rules
    if echo "$packets" | firewall.exe "${rules[0]}" && \
       echo "$packets" | firewall.exe "${rules[1]}" && \
       echo "$packets" | firewall.exe "${rules[2]}" && \
       echo "$packets" | firewall.exe "${rules[3]}"; then
        # If the line passes all sub-rules
        valid_packets+="$packet"$'\n'
    fi
    done <<< "$valid_pkts"

done <<< "$rule_file"

# Sort the valid packets and remove duplicates
sorted_unique_packets=$(printf "%s" "$valid_packets" | sort | uniq)

# Print the sorted and unique packets
echo "$sorted_unique_packets"


