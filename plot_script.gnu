set terminal png size 800,600
set output 'complexity_comparison.png'
set title 'Algorithm Time Complexity Comparison'
set xlabel 'Input Size (log scale)'
set ylabel 'Time (ms)'
set logscale x
set grid
set key left top
plot 'timing_data.txt' using 1:2 title 'Linear Search' with linespoints,\
     '' using 1:3 title 'Binary Search' with linespoints,\
     '' using 1:4 title 'Bubble Sort' with linespoints,\
     '' using 1:5 title 'Merge Sort' with linespoints
