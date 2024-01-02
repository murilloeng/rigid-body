set grid
set key above
set terminal windows

# plot\
# 	'data/pyramid_2_state.txt' using 1:2 with lines linecolor rgb "#000000" notitle,\
# 	'data/pyramid_2_state.txt' using 1:3 with lines linecolor rgb "#ff0000" notitle,\
# 	'data/pyramid_2_state.txt' using 1:4 with lines linecolor rgb "#00ff00" notitle,\
# 	'data/pyramid_2_state.txt' using 1:5 with lines linecolor rgb "#0000ff" notitle

# plot 'data/pyramid_2_energy.txt' using 1:2 with lines linecolor rgb "#0000ff" notitle

plot\
	'data/pyramid_2_velocity.txt' using 1:2 with lines linecolor rgb "#0000ff" notitle,\
	'data/pyramid_2_velocity.txt' using 1:3 with lines linecolor rgb "#ff0000" notitle,\
	'data/pyramid_2_velocity.txt' using 1:4 with lines linecolor rgb "#000000" notitle

# plot\
# 	'data/pyramid_2_acceleration.txt' using 1:2 with lines linecolor rgb "#ff0000" notitle,\
# 	'data/pyramid_2_acceleration.txt' using 1:3 with lines linecolor rgb "#00ff00" notitle,\
# 	'data/pyramid_2_acceleration.txt' using 1:4 with lines linecolor rgb "#0000ff" notitle