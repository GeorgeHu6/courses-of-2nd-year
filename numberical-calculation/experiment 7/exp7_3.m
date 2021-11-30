x1 = [7 1 11 11 7 11 3 1 2 21 1 11 10];
x2 = [26 29 56 31 52 55 71 31 54 47 40 66 68];
x3 = [6 15 8 8 6 9 17 22 18 4 23 9 8];
x4 = [60 52 20 47 33 22 6 44 22 26 34 12 12];
y = [78.5 74.3 104.3 87.6 95.9 109.2 102.7 72.5 93.1 115.9 83.8 113.3 109.4];
subplot(2,2,1),plot(x1,y,'g*'),xlabel('x_1'),ylabel('y')
subplot(2,2,2), plot(x2,y,'g*'),xlabel('x_2'),ylabel('y')
subplot(2,2,3), plot(x3,y,'g*'),xlabel('x_3'),ylabel('y')
subplot(2,2,4), plot(x4,y,'g*'),xlabel('x_4'),ylabel('y')
rstool([x1' x2' x3' x4'],y,'purequadratic')
