m = 30;
z = 1.2*(0:m)/m;
r = ones(size(z));
theta = (0:m)/m*2*pi;
x1 = r'*cos(theta);
y1 = r'*sin(theta);
z1 = z'*ones(1,m+1);

x=(-m:2:m)/m;
x2 = x'*ones(1,m+1);
y2 = r'*cos(theta);
z2 = r'*sin(theta);
surf(x1,y1,z1);
axis equal, axis off
hold on
surf(x2,y2,z2);
axis equal, axis off
title('两个等直径圆管的交线');
hold off
