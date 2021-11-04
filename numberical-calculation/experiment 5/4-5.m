x = [129 140 103.5 88 185.5 195 105 157.5 107.5 77 81 162 162 117.5];
y = [7.5 141.5 23 147 22.5 137.5 85.5 -6.5 -81 3 56.5 -66.5 84 -33.5];
z = -[4 8 6 8 6 8 8 9 9 8 8 9 4 9];
[cx,cy]=meshgrid(75:5:200,-90:5:150);
cz = griddata(x,y,z,cx,cy,'linear');
mesh(cx,cy,cz);
figure(1),mesh(cx,cy,cz);view(-60,30);
figure(2), contour(cx,cy,cz,[-5,-5],'k')