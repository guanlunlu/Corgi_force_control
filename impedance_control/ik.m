function tb = ik(xy)
x = xy(1);
y = xy(2);
ik_pc_ = [4.10837754e+05, -6.25071622e+05, 4.02616603e+05, -1.41754291e+05, 2.93469460e+04, -3.56228405e+03, 2.44240485e+02, -7.12383946e+00];
L = sqrt(x^2 + y^2);
theta = polyval(ik_pc_, L);
u_xy = [x, y]/L;
beta = acos(-u_xy*[0;1]);

tb = [theta, beta];
