set term pdf
set out 'AVL_Tree_erase.pdf'
set xlabel "n"
set ylabel "time"
set title "map_insert"
plot 'file.txt' using 1:2, 'file.txt' using 1:3
