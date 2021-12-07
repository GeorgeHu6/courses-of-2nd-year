f=@(x)(exp(-x.^2./2));
res = quad(f,0,1);
vpa(res,6)
