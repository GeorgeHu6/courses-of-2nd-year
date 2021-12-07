datas = load('data3.txt');
names = {'As','Cd','Cr','Cu','Hg','Ni','Pb','Zn'};
x = datas(:,1)';
y = datas(:,2)';
[x0,y0]=meshgrid(min(x):300:max(x),min(y):300:max(y));

for i=3:10
  z = datas(:,i)';
  [X,Y,Z] = griddata(x,y,z,x0,y0,'v4');
  figure;
  surf(X,Y,Z)
  title(names{i-2});
end
