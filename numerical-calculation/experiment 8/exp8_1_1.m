f1=@(x)((x+sin(x))./(1+cos(x)));
f2=@(x)(log(1+tan(x)));
f3=@(x)(1./(x+sqrt(1-x.^2)));
f4=@(x)(sqrt(1-sin(2.*x)));
f5=@(x)(1./(1+cos(x).^2));
f6=@(x)(x.*sqrt(cos(x).^2-cos(x).^4));
res=[];
res=[res quad(f1,0,pi/2)];
res=[res quad(f2,0,pi/4)];
res=[res quad(f3,0,1)];
res=[res quad(f4,0,pi/2)];
res=[res quad(f5,0,pi/2)];
res=[res quad(f6,0,pi)];
disp(res)
