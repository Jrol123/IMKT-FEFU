clear variables

a = 5;
b = 6;
c = 12;
x = linspace(-7, 7, 51);
y = linspace(-7, 7, 51);


for(i = 1:length(x))
    z(i,:) = c*sqrt((x(i)^2)/(a^2) + (y(:).^2)/(b^2));
end

figure
%surfc(x,y,z')
hold on;
zlim ([-c, 0]);
surfc(x,y,-z')
shading Flat;
colormap('jet')

colorbar