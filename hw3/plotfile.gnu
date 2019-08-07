set pm3d interpolate 2,2
set term post enhanced color
set out 'nten.eps'
set xlabel '{/*2 X}'
set ylabel '{/*2 Y}'
set zlabel '{/*2 Phi}'
set title 'part 1'
splot 'hw3_2.dat' with pm3d title 'part 1'
