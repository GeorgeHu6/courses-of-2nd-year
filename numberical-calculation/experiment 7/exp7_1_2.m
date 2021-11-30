income = [800 1200 2000 3000 4000 5000 7000 9000 10000 12000];
payment = [770 1100 1300 2200 2100 2700 3800 3900 5500 6600];
income_ = [ones(10,1) income'];
b = regress(payment',income_);
f=@(x)b(1)+b(2)*x;
plot(income, payment, 'or','MarkerFaceColor','r','MarkerSize',4)
hold on
fplot(@(x)f(x),[500,15000],'-b','LineWidth',2)
xlabel('家庭收入（元）')
ylabel('家庭消费支出（元）')
title(sprintf('家庭收入与消费支出的关系\ny=%.2fx%.2f',b(2),b(1)),'FontSize',15)
