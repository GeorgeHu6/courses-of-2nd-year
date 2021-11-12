x0 = 0:50:29000;
y0 = 0:50:19000;
a = load('data1.txt');
x = a(:,1);
y = a(:,2);
z = a(:,3);
[X,Y,Z] = griddata(x,y,z,x0,y0,'cubic');
mesh(X,Y,Z)
