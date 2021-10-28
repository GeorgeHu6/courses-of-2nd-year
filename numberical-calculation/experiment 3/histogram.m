A=[170 120 180 200 190 220]';
B=[120 100 110 180 170 180]';
C=[70 50 80 100 95 120]';
bar([A,B,C],'stacked')
colormap(cool)
legend('A','B','C', 'Location', 'northwest')