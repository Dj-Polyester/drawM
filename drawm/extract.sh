#!/usr/bin/env bash
case $BASH_VERSION in (""|[123].*) echo "Bash 4.0 or newer required" >&2; exit 1;; esac

declare -A keys=( ) values=( ) 

while IFS= read -r key &&
      IFS= read -r value; do
  keys[$key]=$key
  values[$key]=$value
done < <(jq -r '.[] | (.key, .value)' <var.json)