[t,yy]=ode45('mytt',[0 20],[1;0]);
plot(t,yy)
legend('y','dy')

syms y(x) u(x)
res=dsolve(diff(y)==u,diff(u)-7*(1-y^2)*u-y,y(0)==1,u(0)==0)