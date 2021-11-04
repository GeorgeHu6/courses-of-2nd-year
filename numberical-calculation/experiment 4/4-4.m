x0 = 1200:400:4000;
y0 = 1200:400:3600;
z0=[1130 1250 1280 1230 1040 900 500 700
    1320 1450 1420 1400 1300 700 900 850
    1390 1500 1500 1400 900 1100 1060 950
    1500 1200 1100 1350 1450 1200 1150 1010
    1500 1200 1100 1550 1600 1550 1380 1070
    1500 1550 1600 1550 1600 1600 1600 1550
    1480 1500 1550 1510 1430 1300 1200 980];
[x, y] = meshgrid(1000:20:4000, 1000:20:4000);
subplot(2, 2, 1)
mesh(x0, y0, z0)
title('Origin')
xlabel('X')
ylabel('Y')
zlabel('Z')

near_z = interp2(x0, y0, z0, x, y, 'nearest');
subplot(2, 2, 2)
meshc(x, y, near_z)
title('Nearest')
xlabel('X')
ylabel('Y')
zlabel('Z')

line_z = interp2(x0, y0, z0, x, y, 'linear');
subplot(2, 2, 3)
meshc(x, y, line_z)
title('Linear')
xlabel('X')
ylabel('Y')
zlabel('Z')

cub_z = interp2(x0, y0, z0, x, y, 'cubic');
subplot(2, 2, 4)
meshc(x, y, cub_z)
title('Cubic')
xlabel('X')
ylabel('Y')
zlabel('Z')
