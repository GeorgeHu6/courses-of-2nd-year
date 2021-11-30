tdata=0:2:24;
ydata=[0.2,0.4,0.5,0.9,1.5,2.4,3.1,3.8,4.1,4.2,4.5,4.4,4.5];
f=@(x,t)1./(x(1)+x(2)*exp(x(3)*t));
x=lsqcurvefit(f,[0.5,10,0],tdata,ydata);
plot(tdata,ydata,'ko')
hold on
fplot(@(t)f(x,t),[0,30])
legend({'数据散点图','拟合曲线'},'Location','northwest')
title(sprintf('a=%.4f,b=%.4f,c=%.4f',x))
