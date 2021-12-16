coef1 = [4 2 -1;3 -1 2;11 3 0];
abs1 = [2 10 8]';
coef2 = [34 17 47 47;42 -32 47 4; -29 -15 -26 32;43 9 48 -28];
abs2 = [-2 43 32 47]';
coef3 = [8 10 6 11;10 16 9 15; 6 9 20 13;11 15 13 20];
abs3 = [1 8 7 9]';

disp('rank1='),disp(rank(coef1))
T=rref([coef1 abs1])
x2 = coef2\abs2;
x3 = coef3\abs3;

disp('Gauss消元法求解结果')
disp('X2='),disp(x2),disp('X3='),disp(x3)


[L2,U2]=lu(coef2);
x2 = U2\(L2\abs2);

[L3,U3]=lu(coef3);
x3 = U3\(L3\abs3);

disp('LU分解求解结果')
disp('X2='),disp(x2),disp('X3='),disp(x3)

[Q2,R2]=qr(coef2);
x2 = R2\(Q2\abs2);

[Q3,R3]=qr(coef3);
x3 = R3\(Q3\abs3);

disp('QR分解求解结果')
disp('X2='),disp(x2),disp('X3='),disp(x3)

[x2,n2]=jacobi(coef2,abs2,[0 0 0 0]');
[x3,n3]=jacobi(coef3,abs3,[0 0 0 0]');

disp('Jacobi迭代法求解结果')
disp('X2='),disp(x2),disp('X3='),disp(x3)

[x2,n2]=gauseidel(coef2,abs2,[0 0 0 0]');
[x3,n3]=gauseidel(coef3,abs3,[0 0 0 0]');
disp('Gauss-Seidel迭代法求解结果')
disp('X2='),disp(x2),disp('X3='),disp(x3)
