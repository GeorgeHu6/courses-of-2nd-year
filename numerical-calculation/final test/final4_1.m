% 读取数据
rawData=load('Table4.txt');
x1=rawData(:,2);
x2=rawData(:,3);
x3=rawData(:,4);
y=rawData(:,5);
% 绘制散点图
subplot(1,3,1)
plot(x1,y,'b*');
xlabel('库存资金额'), ylabel('销售额')
subplot(1,3,2)
plot(x2,y,'k+');
xlabel('广告投入'), ylabel('销售额')
subplot(1,3,3),plot(x3,y,'ro');
xlabel('员工薪酬总额'), ylabel('销售额')
suptitle('各数据与销售额的散点图')
% 进行线性回归
n=18;
x=[ones(n,1),x1,x2,x3];
% b为回归得到的系数，bint为系数的置信边界上下界
% r为残差，rint为离群值的区间，stat为模型的统计量
[b,bint,r,rint,stats]=regress(y,x,0.05)
