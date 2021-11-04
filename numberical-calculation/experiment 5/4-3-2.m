d0 = [466 714 950, 1422, 1634];
temp0 = [7.04, 4.28, 3.40, 2.54, 2.13];
d = 460:1:1700;
d1 = [500 1000]
temp1 = interp1(d0, temp0, d1, 'spline');

h = interp1(d0, temp0, d, 'spline')
plot(d0, temp0, 'r+', d, h, 'LineWidth', 2)

for i = 1:2
  text(d1(i), temp1(i), ['(', num2str(d1(i)),', ', num2str(temp1(i)),')'], 'FontSize', 14)
endfor

