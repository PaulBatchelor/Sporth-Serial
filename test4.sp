# Part 4: arduino with 2 knobs 1 button

_s "./serial.so" fl

_v1 var
_v2 var
_v3 var

_dtime var

_clk var

_t var


_s fe _v3 set _v1 set _v2 set 

_v1 get 0.1 port 127 / 0.05 1 scale dmetro 0.5 maytrig _clk set 

_v2 get 0.1 port 127 / 0.0005 0.3 scale _dtime set

_v3 get 64 0 thresh _t set 

_clk get 0.001 0.001 0.001 tenvx 0.8 noise * 
_v2 get 0.01 port 127 / 500 2000 scale 1.95 0 wpkorg35

_t get tog "state" print *
dup 0.95 _dtime get 1.0 vdelay + 

_s fc
