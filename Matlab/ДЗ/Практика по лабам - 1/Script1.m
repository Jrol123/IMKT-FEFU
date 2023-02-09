fin = fopen('file1.txt', 'r');
a = fscanf(fin, '%f', 2);
b = fscanf(fin, '%f', 2);

a0 = [0; 0];
a1 = a;
b0 = a1;
b1 = a1 + b;

figure ('Name','Сумма')
hold on
grid on

plot([a0(1,1) a1(1,1)], [a0(2,1) a1(2,1)],'b')
plot([b0(1,1) b1(1,1)], [b0(2,1) b1(2,1)],'r')
plot([a0(1,1) b1(1,1)], [a0(2,1) b1(2,1)],'g')

legend('a', 'b', 'c')

figure ('Name', 'Разность')
hold on
grid on

plot([a0(1,1) a1(1,1)], [a0(2,1) a1(2,1)],'b')
plot([a0(1,1) b(1,1)], [a0(2,1) b(2,1)],'r')
plot([a1(1,1) b(1,1)], [a1(2,1) b(2,1)],'g')

legend('a', 'b', 'c')