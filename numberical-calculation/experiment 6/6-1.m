x0=0:0.1:1;
y0=[-0.447,1.978,3.11,5.25,5.02,4.66,4.01,4.58,3.45,5.35,9.22];
n=3;
P=polyfit(x0,y0,n);
xx=0:0.01:1;yy=polyval(P,xx);
plot(xx,yy,'-b',x0,y0,'.r','MarkerSize',20)
legend('拟合曲线','原始数据','Location','SouthEast')
xlabel('x')
