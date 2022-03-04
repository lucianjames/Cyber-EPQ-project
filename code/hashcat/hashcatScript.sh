#!/bin/bash

# Some helpful paths
path=$HOME/Downloads/passwordStuff
hashes=$path/pwned-passwords-ntlm_first1M_cleaned
rules=$path/rules1.txt

# Top2Billion probable no rules
hashcat --potfile-disable -m 1000 $hashes $path/Top2Billion-probable-v2.txt -o top2billion_norules | tee top2billion_norules_term
# Top2Billion probable with rules
hashcat --potfile-disable -m 1000 $hashes $path/Top2Billion-probable-v2.txt -r $rules -o top2billion_withrules | tee top2billion_withrules_term

# hk_hlm_founds no rules
hashcat --potfile-disable -m 1000 $hashes $path/hk_hlm_founds.txt -o hk-hlm_norules | tee hk-hlm_norules_term
# hk_hlm_founds with rules
hashcat --potfile-disable -m 1000 $hashes $path/hk_hlm_founds.txt -r $rules -o hk-hlm_withrules | tee hk-hlm_withrules_term

# weakpass_3p no rules
hashcat --potfile-disable -m 1000 $hashes $path/weakpass_3p -o wp_3p_norules | tee wp_3p_norules_term
# weakpass_3p with rules
hashcat --potfile-disable -m 1000 $hashes $path/weakpass_3p -r $rules -o wp_3p_withrules | tee wp_3p_withrules_term

# ASLM no rules 
hashcat --potfile-disable -m 1000 $hashes $path/ASLM.txt -o ASLM_norules | tee ASLM_norules_term
# ASLM with rules
hashcat --potfile-disable -m 1000 $hashes $path/ASLM.txt -r $rules -o ASLM_withrules | tee ASLM_withrules_term
