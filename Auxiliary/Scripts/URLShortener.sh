#!/bin/bash

# author: Mikayel Egibyan <megibyan@gmail.com>

function usage {
    echo "usage: URLShortener [-ed] URL"
    echo "  -e      long url to short url"
    echo "  -d      short url to long url"
    exit 1
}

if [[ $# -eq 0 ]] ; then
    usage
    exit 0
fi

while getopts ":ed:" option; do
	case $option in
		e)
			curl --header "Content-Type: application/string" \
				--request POST \
				--data $$OPTARG \
				"http://localhost:8080/encode";;
		d)
			curl --header "Content-Type: application/string" \
				--request POST \
				--data $OPTARG \
				"http://localhost:8080/decode";;
		\?)
			echo "Error: Invalid option";;
	esac
done

exit
