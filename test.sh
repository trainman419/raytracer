#!/bin/bash
# generate test plots for the optics subsystem

mkdir -p testdata

echo "set title 'Test filter responses'" > test.plot

plot=false

for (( i=50; i<200; i++ ))
do
   ./model $i > testdata/$i.dat
   if $plot
   then
      echo "replot 'testdata/$i.dat' title '$i' with lines" >> test.plot
   else
      echo "plot 'testdata/$i.dat' title '$i' with lines" >> test.plot
      plot=true
   fi
done

echo "set terminal png size 1024,1024" >> test.plot
echo "set output 'test.png'" >> test.plot
echo "replot" >> test.plot

gnuplot test.plot
