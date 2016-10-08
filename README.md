# Sporth Serial

This is a repository aimed at providing arduino serial communication 
inside of Sporth. 

At the moment, things are a bit jumbled around and are in playground form.

At the moment, there are four sporth patches, each which need particular build
instructions:

## test.sp
- TEST1 macro should be enabled in Makefile
- button.ino sketch is flashed

## test2.sp and test3.sp
These sporth patches are themes on a variation, and 
are virtually identical from a compilation point of view.
- TEST2 or TEST3 macro should be enabled in Makefile
- knobs\_7bit.ino sketch should be flashed to arduino


## test4.sp
- TEST4 macro should be enabled in Makefile
- knobs\_7bit.ino sketch should be flashed to the arduino
- USE\_PUSHBUTTON macro should be defined in the ino sketch

The circuit for this arduino patch requires 2 knobs in analog inputs 0 and 1, 
and one button input in digital pin 2.
