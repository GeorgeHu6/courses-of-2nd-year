x = 0:0.1:2*pi;
[x,y]=meshgrid(x);
z = sin(y).*cos(x)
mesh(x,y,z);
xlabel('x-axis'), ylabel('y-axis'), zlabel('z-axis');
title('mesh')
