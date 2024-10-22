set pm3d
set grid
set view map
set key above
unset surface
unset colorbox
set size ratio 1
set terminal pdf
set encoding utf8
set format x '%.2f'
set format y '%.2f'
set xrange [0 : 2]
set yrange [0 : 2]
set cbtics 0, 1, 3
set cbrange [0 : 3]
set samples 500, 500
set xlabel "{/Symbol g}_1"
set palette rgbformulae -3, 0, 3
set output sprintf("%s.pdf", file)
set ylabel "{/Symbol g}_2" norotate

map(x) = x == -1 ? NaN : x

if(file eq '0-full') {
	set label '(0)' at 1.125, 0.375 front center
	set label '(0)' at 0.375, 1.125 front center
	set label '(1)' at 0.425, 0.750 front center
	set label '(1)' at 0.750, 0.425 front center
	set label '(1)' at 1.250, 1.250 front center
	set label '(2)' at 1.250, 0.750 front center
	set label '(2)' at 0.750, 1.250 front center
	set label '(3)' at 0.750, 0.750 front center
} else {
	if(file eq '1-full') {
		set label '(0)' at 0.500, 0.875 front center
		set label '(1)' at 1.000, 0.500 front center
		set label '(2)' at 0.500, 0.650 front center
	} else {
		set label '(0)' at 0.875, 0.500 front center
		set label '(1)' at 0.500, 1.000 front center
		set label '(2)' at 0.650, 0.500 front center
	}
}

splot sprintf("%s.txt", file) using ($1) : ($2) : (map($3)) notitle