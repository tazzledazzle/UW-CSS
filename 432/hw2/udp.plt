set terminal postscript landscape
set nolabel
set xlabel "window"
set xrange [0:30]
set ylabel "usec"
set yrange [0:8000000]
set output "udp.ps"
plot "100mbps_sw.dat" title "100mbps slinding window" with linespoints, "1gbps_sw.dat" title "1gbps slinding window" with linespoints, 7772391 title "100mbs stopNwait" with line, 2687999 title "1gbps stopNwait" with line
