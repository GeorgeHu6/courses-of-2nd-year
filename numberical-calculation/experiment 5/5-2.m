x0 = [0 3 5 7 9 11 12 13 14 15];
y0 = [0 1.2 1.7 2.0 2.1 2.0 1.8 1.2 1.0 1.6];
x = 0:0.1:15;
y1 = interp1(x0, y0, x);
y2 = interp1(x0, y0, x, 'spline');
subplot(1, 2, 1)
plot(x0, y0, 'k+', x, y1, 'r')
title('piecewise linear')
xlabel('x'), ylabel('y')
subplot(1, 2, 2)
plot(x0, y0, 'k+', x, y2, 'b')
title('spline')
