raw_data=load('Table5.txt');
% 原始数据标准化 %
std_data=zscore(raw_data);
% coeff为特征向量矩阵即主成分系数，score为主成分得分矩阵，latent为特征值 %
[coeff,score,latent]=pca(std_data);
% 计算累积贡献率 %
latents=latent/sum(latent);

% 选取前四个主成分 %
points=score(:,1:4);

% k均值聚类法分为4类 %
cf=kmeans(points,4)
