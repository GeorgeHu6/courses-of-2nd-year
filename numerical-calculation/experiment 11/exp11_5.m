syms y(t) x(t)
res=dsolve('Dx+3*x-y==0,Dy-2*x-3*y-exp(t)==0','x(0)==3/2,y(0)==0')
