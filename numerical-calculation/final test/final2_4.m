f=@(x)(exp(-x.^2./2));
[S,n]=quad(f,0,1,1.0e-6);
disp(S)
disp(n)
