#!/bin/bash

# Some helpful paths
path=$HOME/Downloads/passwordStuff
hashes=$path/pwned-passwords-ntlm_first1M_cleaned
rules=$path/rules1.txt

# cyclone.hashesorg.hashkiller.combined.txt no rules
hashcat --potfile-disable -m 1000 $hashes $path/cyclone.hashesorg.hashkiller.combined.txt -o CHHC_norules | tee CHHC_norules_term
# cyclone.hashesorg.hashkiller.combined.txt with rules
hashcat --potfile-disable -m 1000 $hashes $path/cyclone.hashesorg.hashkiller.combined.txt -r $rules -o CHHC_withrules | tee CHHC_withrules_term
