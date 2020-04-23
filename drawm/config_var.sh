#!/usr/bin/bash
clear
source extract.sh

populate-config() { 
  jq "map(if .key == \"$1\"
          then . + {\"value\":$2} 
          else . 
          end)"
}

for pair in "$@" ;
do
    IFS='=' read -ra ARR <<< "$pair"
     
    if [[ "${ARR[1]}" != true && "${ARR[1]}" != false ]]; then
        ARR[1]=\"${ARR[1]}\"
    fi
    
    cat var.json | populate-config ${ARR[0]} ${ARR[1]} > var_tmp.json
    cat var_tmp.json > var.json
done
rm -f var_tmp.json




