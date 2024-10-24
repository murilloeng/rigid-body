set grid
set key above
set xlabel 't (s)'
set ylabel 'U (J)'

plot\
	sprintf("%s-energy.dat", file) using 1:2 with lines linecolor rgb "#ff0000" title 'K',\
	sprintf("%s-energy.dat", file) using 1:3 with lines linecolor rgb "#0000ff" title 'V',\
	sprintf("%s-energy.dat", file) using ($1) : ($2 + $3) with lines linecolor rgb "#000000" title 'E'