function [J_G] = jacG(tb)
%JACG pointG Jacobian w.r.t. tb

theta = tb(1);
beta = tb(2);

fk_coeff = [-0.0004362, 0.00715474, -0.04529168, 0.13936602, -0.22479562, 0.19297458, 0.01846436, 0.08280706];
dfk_coeff = polyder(fk_coeff);

L_p_theta = polyval(dfk_coeff, theta); % L partial theta
L = polyval(fk_coeff, theta);

J_G = [-L_p_theta*sin(beta), -L*cos(beta);
       -L_p_theta*cos(beta), L*sin(beta)];


end

