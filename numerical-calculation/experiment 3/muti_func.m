x1 = -6:0.01:0;
x2 = 0:0.01:3;
x3 = 3:0.01:6;
y = [sin(x1), x2 -x3+6];
plot([x1 x2 x3], y, 'b', 'LineWidth', 2);
grid on;
