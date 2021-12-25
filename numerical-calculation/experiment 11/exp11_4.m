syms y(x);
y=dsolve(diff(y)==-3*y-8,y(0)==2);
disp(y)
