set term pdf
set out 'Red_Black_Tree_find.pdf'
set xlabel "n"
set ylabel "time"
set title "map_insert"
plot 'file.txt' using 1:2, 'file.txt' using 1:3
