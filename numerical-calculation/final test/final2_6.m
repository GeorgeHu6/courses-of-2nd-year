[t,yy]=ode45('mytt',[0 30],[1 0]);
plot(t,yy)
legend('y','dy')