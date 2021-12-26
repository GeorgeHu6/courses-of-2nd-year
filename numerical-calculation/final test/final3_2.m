datas = load('data2.txt');
x = datas(:,1);
y = datas(:,2);
t = datas(:,3);
xi = linspace(min(x),max(x));
yi = linspace(min(y),max(y));
marker = {'d','o','s','p','x'};
color = {'m','b','g','r','c'};
str = {'生活区','工业区','山区','主干道区','公园绿地区','6'};
str1 = {'1','2','3','4','5','6'};
figure;
hold on

for i = 1:5
  loc = t == i;
  plot(x(loc),y(loc),marker{i},'Markersize',5,'MarkerEdgeColor',color{i});
end

legend(str,'Location','northwest')
