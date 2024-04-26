set grid
set key above
# set terminal windows

array results[5] = ["state", "energy", "position", "velocity", "acceleration"]

if(index == 0){
	plot\
		'data/pyramid_vertical_state.txt' using 1:2 with lines linecolor rgb "#ff0000" title "q_0",\
		'data/pyramid_vertical_state.txt' using 1:3 with lines linecolor rgb "#00ff00" title "q_1",\
		'data/pyramid_vertical_state.txt' using 1:4 with lines linecolor rgb "#0000ff" title "q_2",\
		'data/pyramid_vertical_state.txt' using 1:4 with lines linecolor rgb "#000000" title "q_3"
}
if(index == 1){
	plot\
		'data/pyramid_vertical_energy.txt' using 1:2 with lines linecolor rgb "#0000ff" title "K"
}
if(index == 2){
	plot\
		'data/pyramid_vertical_position.txt' using 1:2 with lines linecolor rgb "#ff0000" title "x_1",\
		'data/pyramid_vertical_position.txt' using 1:3 with lines linecolor rgb "#00ff00" title "x_2",\
		'data/pyramid_vertical_position.txt' using 1:4 with lines linecolor rgb "#0000ff" title "x_3"
}
if(index == 3){
	plot\
		'data/pyramid_vertical_velocity.txt' using 1:2 with lines linecolor rgb "#ff0000" title "v_1",\
		'data/pyramid_vertical_velocity.txt' using 1:3 with lines linecolor rgb "#00ff00" title "v_2",\
		'data/pyramid_vertical_velocity.txt' using 1:4 with lines linecolor rgb "#0000ff" title "v_3"
}
if(index == 4){
	plot\
		'data/pyramid_vertical_acceleration.txt' using 1:2 with lines linecolor rgb "#ff0000" title "a_1",\
		'data/pyramid_vertical_acceleration.txt' using 1:3 with lines linecolor rgb "#00ff00" title "a_2",\
		'data/pyramid_vertical_acceleration.txt' using 1:4 with lines linecolor rgb "#0000ff" title "a_3"
}