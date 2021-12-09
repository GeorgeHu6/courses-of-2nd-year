raw_data=load('data1.txt');
X=zscore(raw_data);
[coeff,score,latent]=pca(X);
