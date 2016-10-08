# Part 2: arduino with 2 knobs, soundscape 1

_s "./serial.so" fl

_v1 var
_v2 var
_frq var

_note var
_clk var

_seq "0 2 3 12" gen_vals


_s fe _v1 set _v2 set 

_v1 get 0.1 port 127 / 0.05 0.5 scale dmetro _clk set 

_v2 get 0.1 port 127 / 100 2000 scale _frq set

_clk get 0.001 0.03 0.03 tenvx 

_clk get 0 _seq tseq 48 + 0.003 port dup 0.1 - mtof 0.6 saw
swap 0.1 + mtof 0.6 saw + *

_frq get 0.4 moogladder

dup jcrev + 
_s fc
