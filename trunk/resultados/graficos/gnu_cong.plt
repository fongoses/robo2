set term png size 1024,768
set output '/home/heitor/robo2/resultados/graficos/tres.png' ; plot '/home/heitor/robo2/resultados/curvas/tres_3_curva.txt' with lines, '/home/heitor/robo2/resultados/curvas/tres_4_curva.txt' with lines
set output '/home/heitor/robo2/resultados/graficos/quatro.png' ; plot '/home/heitor/robo2/resultados/curvas/quatro_3_curva.txt' with lines, '/home/heitor/robo2/resultados/curvas/quatro_4_curva.txt' with lines
set output '/home/heitor/robo2/resultados/graficos/quatro_diff.png' ; plot '/home/heitor/robo2/resultados/curvas/quatro_diff_3_curva.txt' with lines, '/home/heitor/robo2/resultados/curvas/quatro_diff_4_curva.txt' with lines
set output '/home/heitor/robo2/resultados/graficos/x.png' ; plot '/home/heitor/robo2/resultados/curvas/x_3_curva.txt' with lines, '/home/heitor/robo2/resultados/curvas/x_4_curva.txt' with lines
set output '/home/heitor/robo2/resultados/graficos/x_incompleto.png' ; plot '/home/heitor/robo2/resultados/curvas/x_incompleto_3_curva.txt' with lines, '/home/heitor/robo2/resultados/curvas/x_incompleto_4_curva.txt' with lines
set output '/home/heitor/robo2/resultados/graficos/espinha.png' ; plot '/home/heitor/robo2/resultados/curvas/espinha_3_curva.txt' with lines, '/home/heitor/robo2/resultados/curvas/espinha_4_curva.txt' with lines
set output '/home/heitor/robo2/resultados/graficos/espinha_diff.png' ; plot '/home/heitor/robo2/resultados/curvas/espinha_diff_3_curva.txt' with lines, '/home/heitor/robo2/resultados/curvas/espinha_diff_4_curva.txt' with lines
