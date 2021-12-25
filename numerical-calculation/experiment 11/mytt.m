function [dfy]=mytt(t,fy)
dfy=[fy(2);2*(1-fy(1)^2)*fy(2)-fy(1)];
