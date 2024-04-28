set grid
set key above

if(index == 0){
	plot\
		sprintf('data/%s_state.txt', model) using 1:2 with lines linecolor rgb "#ff0000" title "q_0",\
		sprintf('data/%s_state.txt', model) using 1:3 with lines linecolor rgb "#00ff00" title "q_1",\
		sprintf('data/%s_state.txt', model) using 1:4 with lines linecolor rgb "#0000ff" title "q_2",\
		sprintf('data/%s_state.txt', model) using 1:4 with lines linecolor rgb "#000000" title "q_3"
}
if(index == 1){
	plot\
		sprintf('data/%s_energy.txt', model) using 1:2 with lines linecolor rgb "#0000ff" title "K"
}
if(index == 2){
	plot\
		sprintf('data/%s_position.txt', model) using 1:2 with lines linecolor rgb "#ff0000" title "x_1",\
		sprintf('data/%s_position.txt', model) using 1:3 with lines linecolor rgb "#00ff00" title "x_2",\
		sprintf('data/%s_position.txt', model) using 1:4 with lines linecolor rgb "#0000ff" title "x_3"
}
if(index == 3){
	plot\
		sprintf('data/%s_velocity.txt', model) using 1:2 with lines linecolor rgb "#ff0000" title "v_1",\
		sprintf('data/%s_velocity.txt', model) using 1:3 with lines linecolor rgb "#00ff00" title "v_2",\
		sprintf('data/%s_velocity.txt', model) using 1:4 with lines linecolor rgb "#0000ff" title "v_3"
}
if(index == 4){
	plot\
		sprintf('data/%s_acceleration.txt', model) using 1:2 with lines linecolor rgb "#ff0000" title "a_1",\
		sprintf('data/%s_acceleration.txt', model) using 1:3 with lines linecolor rgb "#00ff00" title "a_2",\
		sprintf('data/%s_acceleration.txt', model) using 1:4 with lines linecolor rgb "#0000ff" title "a_3"
}