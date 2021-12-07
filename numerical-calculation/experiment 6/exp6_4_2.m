x0=1:9;
y0=[1.78 2.24 2.74 3.74 4.45 5.31 6.92 8.85 10.97];
y0=log(y0);
res=polyfit(x0,y0,1);
y=polyval(res,x);
plot(x,y,'-b',x0,y0,'ro','MarkerSize',5,'MarkerFaceColor','r')
title(sprintf('y=%.4fe^{%.4fx}',exp(res(2)),res(1)))