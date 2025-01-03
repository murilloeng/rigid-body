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
set cbrange [0 : 1]
set samples 500, 500
set lmargin at screen 0.00
set rmargin at screen 1.00
set tmargin at screen 1.00
set xlabel "{/Symbol g}_1"
set palette rgbformulae -3, 0, 3
set output sprintf("%s.pdf", file)
set ylabel "{/Symbol g}_2" norotate


splot sprintf("%s.txt", file) using ($1) : ($2) : ($3 == -1 ? NaN : $3) notitle