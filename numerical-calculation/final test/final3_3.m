scores=[82 73 66 54 100 78 96 88 64 75];
% 求平均分
mean(scores)
% 统计每一类评价的个数
perfect=0;
excellent=0;
good=0;
pass=0;
unpass=0;
% 记录频数
stat=zeros(1,10);

for i=1:10
    grade=scores(i);
    if grade==100
        disp('满分');
        stat(i)=4;
        perfect=perfect+1;
    elseif grade>=90
        disp('优秀')
        stat(i)=3;
        excellent=excellent+1;
    elseif grade>=75
        disp('良好')
        stat(i)=2;
        good=good+1;
    elseif grade>=60
        disp('合格')
        stat(i)=1;
        pass=pass+1;
    else
        disp('不合格')
        stat(i)=0;
        unpass=unpass+1;
    end
end
X=[perfect excellent good pass unpass];
% 绘制饼图
pie(X)
legend('满分','优秀','良好','合格','不合格','Location','northwest')
figure(2)
% 绘制频数直方图
histogram(stat)
set(gca,'xticklabel',{'';'不合格';'';'合格';'';'良好';'';'优秀';'';'满分'})
