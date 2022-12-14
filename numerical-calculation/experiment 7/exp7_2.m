x1 = [5.5 2.5 8 3 3 2.9 8 9 4 6.5 5.5 5 6 5 3.5 8 6 4 7.5 7];
x2 = [31 55 47 50 38 71 30 56 42 73 60 44 50 39 55 70 40 50 62 59];
x3 = [10 8 12 7 8 12 12 5 8 5 11 12 6 10 10 6 11 11 9 9];
x4 = [8 6 9 16 15 17 8 10 4 16 7 12 6 4 4 14 6 8 13 11];
y = [79.3 200.1 163.2 200.1 146 177.7 30.9 291.9 160 339.4 159.6 86.3...
    237.5 107.2 155 201.4 100.2 135.8 223.3 195];
x = [ones(20,1) x1' x2' x3' x4'];
[b,bint,r,rint,stats] = regress(y',x);
tt = '销售量y,推销开支x_1,实际账目数x_2,同类商品竞争数x_3,地区销售潜力x_4';
tt = [tt sprintf('\ny=%.2f+%.2fx_1+%.2fx_2%.2fx_3%.2fx_4',b(1),b(2),b(3),b(4),b(5))];
sgtitle(tt)
subplot(2,2,1),plot(x1,y,'g*'),xlabel('推销开支'),ylabel('销售量')
subplot(2,2,2), plot(x2,y,'g*'),xlabel('实际账目数'),ylabel('销售量')
subplot(2,2,3), plot(x3,y,'g*'),xlabel('同类商品竞争数'),ylabel('销售量')
subplot(2,2,4), plot(x4,y,'g*'),xlabel('地区销售潜力'),ylabel('销售量')
