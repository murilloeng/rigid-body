set grid
set terminal windows

# plot\
# 	'data/test-1.dat' using 1:2 with lines linecolor rgb "#ff0000",\
# 	'data/test-1.dat' using 1:3 with lines linecolor rgb "#00ff00",\
# 	'data/test-1.dat' using 1:4 with lines linecolor rgb "#0000ff"

plot 'data/test-1.dat' using ($1) : (sqrt(25 * $5**2 + 25 * $6**2 + $7**2)) with lines linecolor rgb "#0000ff"