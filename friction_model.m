clear;
close all;

bk_ft= 25; % breakaway friction force
bk_vel = 0.1; % breakaway friction velocity
col_ft = 20; % Coulomb friction force
vis_ft = 1; % Viscous friction coeff.

bk_ft= 0.7;
bk_vel = 0.05;
col_ft = 0.5;
vis_ft = 0.1;

v = linspace(-2*pi, 2*pi, 1000);

F_brk = bk_ft;
F_c = col_ft;
v_brk = bk_vel;
v_st = v_brk*sqrt(2);
v_coul = v_brk/10;
F_v = vis_ft * v;

F = sqrt(2*exp(1)) .* (F_brk - F_c).*exp(-(v/v_st).^2).*v/v_st + F_c .* tanh(v/v_coul) + F_v;

plot(v, F, "LineWidth",2)
grid on