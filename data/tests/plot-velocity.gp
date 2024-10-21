set grid
set key above
set xlabel 't (s)'
set ylabel 'w (rad/s)'

plot\
	sprintf("%s-velocity.dat", file) using 1:2 with lines linecolor rgb "#ff0000" title 'w_1',\
	sprintf("%s-velocity.dat", file) using 1:3 with lines linecolor rgb "#00ff00" title 'w_2',\
	sprintf("%s-velocity.dat", file) using 1:4 with lines linecolor rgb "#0000ff" title 'w_3'