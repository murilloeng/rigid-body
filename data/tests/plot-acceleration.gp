set grid
set key above
set xlabel 't (s)'
set ylabel 'a (rad / s^2)'

plot\
	sprintf("%s-acceleration.dat", file) using 1:2 with lines linecolor rgb "#ff0000" title 'a_1',\
	sprintf("%s-acceleration.dat", file) using 1:3 with lines linecolor rgb "#00ff00" title 'a_2',\
	sprintf("%s-acceleration.dat", file) using 1:4 with lines linecolor rgb "#0000ff" title 'a_3'