A=[1 1 1 0;1 2 1 -1;2 -1 0 -3;3 3 5 -6];
b=[1 8 3 5]';
% Gauss消元法
res = A\b;clc
disp('Gauss消元法结果')
disp(res)
% Jacobi迭代法
[x,n]=jacobi(A,b,[1 5 -5 -2]',1.0e-6);
disp('Jacobi迭代法结果')
disp(x)
disp(n)
% Gauss-Seidel迭代法
[x,n]=gauseidel(A,b,[0 3 -3 -1]');
disp('Gauss-Seidel迭代法结果')
disp(x)
disp(n)