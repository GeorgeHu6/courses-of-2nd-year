theta=0:0.01:2*pi;
rho=1-cos(theta);
graph = polar(theta, rho, 'r');
axis square;
set(graph, 'LineWidth', 2);
title '\rho=1-cos\theta';