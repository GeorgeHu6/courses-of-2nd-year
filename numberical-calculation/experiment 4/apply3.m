[x,y] = meshgrid(-10:0.2:10);
z1 = (x.^2-2*y.^2)+eps;
a = input('a=?');

z2 = a*ones(size(x));
subplot(1,2,1);
mesh(x,y,z1);
hold on;
mesh(x,y,z2);

v = [-10,10,-10,10,-100,100];
axis(v);
grid;
hold off;
r0 = abs(z1-z2) <= 1
xx = r0.*x;
yy = r0.*y;
zz = r0.*z2;
subplot(1,2,2);
plot3(xx(r0~=0),yy(r0~=0),zz(r0~=0),'*');
axis(v);
grid;
