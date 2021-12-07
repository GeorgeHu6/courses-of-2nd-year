data=load('实际数据.txt');
x0=data(:,1);
y0=data(:,2);
res=polyfit(x0,y0,2);

subplot(1,2,1)
plot(x0,y0,'ob','MarkerFaceColor','r','MarkerSize',1);
title('散点图')
xlabel('油位高度')
ylabel('实际容量')

subplot(1,2,2)
x=250:100:3000;
y=polyval(res,x);
plot(x,y,'-b');
title(sprintf('曲线拟合图\ny=%.4fx^2+%.4fx+%.4f',input1(1),input1(2),input1(3)))
xlabel('油位高度')
ylabel('实际容量')