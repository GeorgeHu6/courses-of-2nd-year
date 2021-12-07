t = (-2*pi):0.05:2*pi;
x = t;
y = 2.*t.*cos(t);
z = 5.*t.*sin(t);
plot3(x,y,z, 'LineWidth', 1.5)
