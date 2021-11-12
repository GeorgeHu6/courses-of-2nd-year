x0 = [1.1 1.2 1.3 1.4 1.5];
y0 = [1.15369 1.314534 1.482228 1.656502 1.837117];
x = 1:0.01:2;
x1 = [1.356];
h = interp1(x0, y0, x, 'linear');
y1 = interp1(x0, y0, x1, 'linear');
plot(x0, y0, '+', x, h, x1, y1, 'm*')
text(x1, y1, ['(', num2str(x1),', ', num2str(y1),')'], 'FontSize', 14)
