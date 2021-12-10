raw_data=load('data1.txt');
% 原始数据标准化 %
std_data=zscore(raw_data);
% coeff为特征向量矩阵即主成分系数，score为主成分得分矩阵，latent为特征值 %
[coeff,score,latent]=pca(std_data);
% 计算累积贡献率 %
latents=latent/sum(latent)
% 选取第一个主成分进行排名并输出第一主成分得分 %
F1=score(:,1)

% 输出各城市在第一主成分中的排名 %
[~,l1]=sort(F1,'ascend');
[~,l2]=sort(l1);
l2
