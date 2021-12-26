function [y,n]=jacobi(A,b,x0,eps)
if nargin==3 %函数输入参数个数
    eps=1.0e-6;
elseif nargin<3 %至少得输入前3个参数
    error
    return
end
D=diag(diag(A)); %求A的对角矩阵
L=-tril(A,-1); %求A的 不包括主对角线下三角阵
U=-triu(A,1); %求A的不包括主对角线上三角阵
B=D\(L+U);
f=D\b;
y=B*x0+f;
n=1; %迭代次数
while norm(y-x0)>=eps
    x0=y;
    y=B*x0+f;
    n=n+1;
end