year = 1949:5:1994;
population = [5.4 6 6.7 7 8.1 9.1 9.8 10.3 11.3 11.8];
year_ = [ones(10,1) year'];
b = regress(population', year_);
f=@(x)b(1)+b(2)*x;
plot(year, population, 'or','MarkerFaceColor','r','MarkerSize',4)
hold on
fplot(@(x)f(x),[1949,2000],'-b','LineWidth',2)
xlabel('年份')
ylabel('人口数量（亿人）')
title(sprintf('1949-1994年中国人口\ny=%.2fx%.2f',b(2),b(1)),'FontSize',15)

