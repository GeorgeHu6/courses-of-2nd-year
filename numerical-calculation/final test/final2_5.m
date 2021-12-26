f=@(x)(sin(x).^2.*exp(-0.1*x)-0.5*x);
res = fzero(f,[0.5,1]);
disp(res)
