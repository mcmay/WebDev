# script for assembling the desired htm file

#!/bin/sh

# Exit immediately if a command exits with a non-zero status.
set -e

if [ "$#" -ne 1 ]; then
    echo "Usage: ./scripthtm.sh htm file (e.g. ./scripthtm 1_i_bawl1.htm)"
    exit 1
fi

#First step: create an empty file temp1.htm
touch ../../Studying/htm_samples_with_tests/temp1.htm

#Second step: append beforeHead.htm to the new file
cat ./beforeBody.htm > ../../Studying/htm_samples_with_tests/temp1.htm

#Third step: read the body part of $1 into temp2.htm
./getBodyElement ../../Studying/raw_htm_samples/$1.htm

#Fourth step: move temp2.htm to the same directory as temp1.htm
mv ~/temp2.htm ../../Studying/htm_samples_with_tests/

#Fifth step: append temp2.htm to temp1.htm
cat ../../Studying/htm_samples_with_tests/temp2.htm >> ../Studying/htm_samples_with_tests/temp1.htm

#sixth step: append myScriptLast.htm to temp1.htm
cat ./myScriptLast.htm >> ../Studying/htm_samples_with_tests/temp1.htm

#seventh step: remove $1.htm
rm ../../Studying/htm_samples_with_tests/$1.htm

#eight step: remove temp2.htm
rm ../../Studying/htm_samples_with_tests/temp2.htm

#nineth step: change temp1.htm to $1.htm
mv ../../Studying/temp1.htm ../Studying/htm_samples_with_tests/$1.htm

#tenth step: use insertTagsInExample to put an edited example in the page's example slot
./insertTagsInExample ../../Studying/htm_samples_with_tests/$1.htm

#eleventh step: remove $1.htm
rm ../../Studying/htm_samples_with_tests/$1.htm

#last step: change temp3.htm to $1.htm
mv ~/temp3.htm ../../Studying/htm_samples_with_tests/$1.htm
