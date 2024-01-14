clear
theta = 0.2967;
theta = pi/2
O = [0;0]
OA_R = nOA_R(theta);
OB_R = nOB_R(theta);
OC_R = nOC_R(theta);
OD_R = nOD_R(theta);
OE_R = nOE_R(theta);
OF_R = nOF_R(theta);
OG = nOG(theta)
xy = [O,OA_R, OB_R, OC_R, OD_R, OE_R, OF_R, OG]
% n = ['O', 'A', 'B', 'C', 'D', 'E', 'F', 'G']
scatter(xy(1,:), xy(2,:))
grid on
axis equal

