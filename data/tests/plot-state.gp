set grid
set key above
set ylabel 'q'
set xlabel 't (s)'

plot\
	sprintf("%s-state.dat", file) using 1:2 with lines linecolor rgb "#ff0000" title 'q_1',\
	sprintf("%s-state.dat", file) using 1:3 with lines linecolor rgb "#00ff00" title 'q_2',\
	sprintf("%s-state.dat", file) using 1:4 with lines linecolor rgb "#0000ff" title 'q_3',\
	sprintf("%s-state.dat", file) using 1:5 with lines linecolor rgb "#000000" title 'q_4'