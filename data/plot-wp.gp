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
set cbrange [0 : 1]
set samples 500, 500
set xlabel "{/Symbol g}_1"
set palette rgbformulae -3, 0, 3
set output sprintf("%s.pdf", file)
set ylabel "{/Symbol g}_2" norotate

splot sprintf("%s.txt", file) using ($1) : ($2) : ($3 == -1 ? NaN : $3) notitle