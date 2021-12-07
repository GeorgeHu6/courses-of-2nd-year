x=[0,60,120,180];
y=[0,0.45,3.6,12.15];
P=polyfit(x,y,3)
xx=0:180;
yy=polyval(P,xx);
plot(x,y,'ro',xx,yy)
