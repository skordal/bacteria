#!/usr/bin/gnuplot
# GNUPlot Instructions for graphing bacteria population and food levels
# (c) Kristian K. Skordal 2009 - 2012 <kristian.skordal@gmail.com>

set autoscale
set title "Correlation between bacteria population and food levels"
set xlabel "Time (seconds)"
set ylabel "Population (individuals)"

plot "graph_data.dat" using 1:2 title 'Bacteria' with lines lt rgb "blue", \
     "graph_data.dat" using 1:3 title 'Food' with lines lt rgb "green"

pause -1
