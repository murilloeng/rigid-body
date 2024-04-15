set pm3d
set view map
unset surface
set palette rgbformulae 33, 13, 10

set format x '%.2f'
set format y '%.2f'

set xrange [0.50 : 1.50]
set yrange [0.00 : 1.57]

set xlabel 'J_1 / J_3'
set ylabel '{/Symbol b}' norotate

splot 'test.txt' with lines