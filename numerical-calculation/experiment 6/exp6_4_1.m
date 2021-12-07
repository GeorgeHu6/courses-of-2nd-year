x0=1:1:8;
y0=[15.3,20.5,27.4,36.6,49.1,65.5,87.8,117.6];
y0=log(y0);
res=polyfit(x0,y0,1);
x=1:0.1:8;
y=polyval(res,x);
plot(x,y,'-b',x0,y0,'ro','MarkerSize',5,'MarkerFaceColor','r')
title(sprintf('a=%.4f,b=%.4f',exp(res(2)),res(1)))