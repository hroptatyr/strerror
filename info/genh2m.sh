#!/bin/sh

## Usage: BINARY EXFILE

BINARY="${1}"
EXFILE="${2}"
TOOLNM=`basename "${BINARY}"`

echo "[EXAMPLES]"

cat "${EXFILE}" | \
	awk '{print "% " $0;
sub(/'${TOOLNM}'/, "'${BINARY}'");
system($0);
print "";
}' | \
	awk '{printf "  "; print;}'
