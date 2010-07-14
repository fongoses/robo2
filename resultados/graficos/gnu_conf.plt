set term png size 640,480
set style line 1 linecolor rgb "gray60" lw 2
set style line 2 linecolor rgb "black"
set key inside center bottom
set xlabel "Tempo (s)"
set ylabel "Grau de Urgência Total"
set output '/home/heitor/robo2/resultados/graficos/quatro.png' ; plot '/home/heitor/robo2/resultados/curvas/quatro_3_curva.txt' with lines ls 1 t "Offline", '/home/heitor/robo2/resultados/curvas/quatro_4_curva.txt' with lines ls 2 t "Tempo Real"
set style line 1 linecolor rgb "gray60" lw 1
set output '/home/heitor/robo2/resultados/graficos/quatro_diff.png' ; plot '/home/heitor/robo2/resultados/curvas/quatro_diff_3_curva.txt' with lines ls 1 t "Offline", '/home/heitor/robo2/resultados/curvas/quatro_diff_4_curva.txt' with lines ls 2 t "Tempo Real"
set output '/home/heitor/robo2/resultados/graficos/x.png' ; plot '/home/heitor/robo2/resultados/curvas/x_3_curva.txt' with lines ls 1 t "Offline", '/home/heitor/robo2/resultados/curvas/x_4_curva.txt' with lines ls 2 t "Tempo Real"
set output '/home/heitor/robo2/resultados/graficos/x_incompleto.png' ; plot '/home/heitor/robo2/resultados/curvas/x_incompleto_3_curva.txt' with lines ls 1 t "Offline", '/home/heitor/robo2/resultados/curvas/x_incompleto_4_curva.txt' with lines ls 2 t "Tempo Real"
set output '/home/heitor/robo2/resultados/graficos/espinha.png' ; plot '/home/heitor/robo2/resultados/curvas/espinha_3_curva.txt' with lines ls 1 t "Offline", '/home/heitor/robo2/resultados/curvas/espinha_4_curva.txt' with lines ls 2 t "Tempo Real"
set output '/home/heitor/robo2/resultados/graficos/espinha_diff.png' ; plot '/home/heitor/robo2/resultados/curvas/espinha_diff_3_curva.txt' with lines ls 1 t "Offline", '/home/heitor/robo2/resultados/curvas/espinha_diff_4_curva.txt' with lines ls 2 t "Tempo Real"
set output '/home/heitor/robo2/resultados/graficos/ap.png' ; plot '/home/heitor/robo2/resultados/curvas/ap_3_curva.txt' with lines ls 1 t "Offline", '/home/heitor/robo2/resultados/curvas/ap_4_curva.txt' with lines ls 2 t "Tempo Real"
