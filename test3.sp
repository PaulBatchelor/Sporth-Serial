# Part 3: arduino with 2 knobs, soundscape 3

_s "./serial.so" fl

_v1 var
_v2 var
_dtime var

_clk var

_seq "0 2 3 12" gen_vals

_s fe _v1 set _v2 set 

_v1 get 0.1 port 127 / 0.05 0.5 scale dmetro _clk set 

_v2 get 0.1 port 127 / 0.005 0.1 scale _dtime set


_clk get 0.001 0.001 0.001 tenvx 0.8 noise * 
1000 1.92 0 wpkorg35

dup 0.9 _dtime get 1.0 vdelay + 

_s fc
