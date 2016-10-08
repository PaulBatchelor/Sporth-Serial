# part 1: button serial test

_s "./serial.so" fl

# Disturbia Riff by Rihanna 
#_seq "4 4 7 2 0 0 -1 0 2" gen_vals 

# Where the streets have no name
_seq "0 -1 0 2 7 2" gen_vals 


_s fe 0 1 thresh dup 
0 _seq tseq swap 0.01 0.01 0.15 tenvx 

_note var
_dry var

swap dup _note set 79 + mtof 0.5 1 1 1 fm 
_note get 55 + mtof 0.7 1 1 2 fm + 
*

#dup 0.3 0.5 delay 1000 butlp -10 ampdb * +
dup 0.6 0.7 delay 1000 butlp -5 ampdb * + -3 ampdb * _dry set
_dry get dup 0.90 10000 revsc drop -12 ampdb * _dry get +

#"val" print

_s fc
