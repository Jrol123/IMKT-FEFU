clc

fin = fopen('file2.txt', 'r');
a = fscanf(fin, '%f', 3);

% Ќайти направл€ющие косинусы
%  осинусы углов, которые вектор образует с положительными полуос€ми координат

c = a.^ 2;

lenA = (c(1,1) + c(2,1) + c(3,1))^(0.5);

cosx = a(1,1) / lenA;
cosy = a(2,1) / lenA;
cosz = a(3,1) / lenA;

fprintf("length of vector = %6.3f\n", lenA);
fprintf("cos x = %6.3f\n", cosx);
fprintf("cos x = %6.3f\n", cosy);
fprintf("cos x = %6.3f\n", cosz);