[x0,y0] = meshgrid(0:200:29000,0:200:19000);
a = load('data1.txt');
x = a(:,1)';
y = a(:,2)';
z = a(:,3)';
[X,Y,Z] = griddata(x,y,z,x0,y0,'v4');
surf(X,Y,Z)
