function [eef_pos] = fk(tb)
% Foward kinematics realized by polynomial fitting

theta = tb(1);
beta = tb(2);
coeff = [-0.0004362, 0.00715474, -0.04529168, 0.13936602, -0.22479562, 0.19297458, 0.01846436, 0.08280706];
L = polyval(coeff, theta);
eef_pos = [-L*sin(beta), -L*cos(beta)];
end

