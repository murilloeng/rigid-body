set grid
set key above
set terminal windows

plot\
	'data/cylinder_1_state.txt' using 1:2 with lines linecolor rgb "#0000ff" notitle,\
	'data/cylinder_1_state.txt' using 1:5 with lines linecolor rgb "#ff0000" notitle

# plot 'data/cylinder_1_energy.txt' using 1:2 with lines linecolor rgb "#0000ff" notitle

# plot 'data/cylinder_1_velocity.txt' using 1:4 with lines linecolor rgb "#0000ff" notitle

# plot 'data/cylinder_1_acceleration.txt' using 1:4 with lines linecolor rgb "#0000ff" notitle