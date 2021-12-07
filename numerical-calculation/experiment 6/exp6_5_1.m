data1=load('无变位进油.txt');
data2=load('倾斜变位进油.txt');
y01=data1(:,1)+262;
x01=data1(:,2);
y02=data2(:,1)+215;
x02=data2(:,2);

subplot(2,2,1)
plot(x01,y01,'ob','MarkerFaceColor','b','MarkerSize',1)
xlabel('油位高度')
ylabel('实际容量')
title('无变位散点图')

subplot(2,2,2)
input1=polyfit(x01,y01,2);
x=1:10:1200;
y=polyval(input1,x);
plot(x,y,'-b',x,y,'ro','MarkerFaceColor','b','MarkerSize',2)
xlabel('油位高度')
ylabel('实际容量')
title(sprintf('无变位曲线拟合图\ny=%.4fx^2+%.4fx+%.4f',input1(1),input1(2),input1(3)))

subplot(2,2,3)
plot(x02,y02,'ob','MarkerFaceColor','b','MarkerSize',1)
xlabel('油位高度')
ylabel('实际容量')
title('倾斜变位散点图')

subplot(2,2,4)
input2=polyfit(x02,y02,2);
x=400:10:1100;
y=polyval(input2,x);
plot(x,y,'-b')
xlabel('油位高度')
ylabel('实际容量')
title(sprintf('倾斜变位曲线拟合图\ny=%.4fx^2+%.4fx+%.4f',input2(1),input2(2),input2(3)))


