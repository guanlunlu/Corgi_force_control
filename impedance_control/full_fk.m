%%
clc
clear
% symbols
syms t phi_L(t) phi_R(t) theta(t) beta(t);

%%
theta_0_ = deg2rad(17);

%% For testing
% theta(t) = deg2rad(17);
% beta(t) = 0;
% transform relation between theta-beta frame and phi_R-phi_L frame
% phi_R(t) = 1;
% phi_L(t) = 1;
% theta(t) = [1, 0] * (1/2* [1 -1; 1 1]*[phi_R; phi_L] + [1; 0]*theta_0_);
% beta(t) = [0, 1] * (1/2* [1 -1; 1 1]*[phi_R; phi_L] + [1; 0]*theta_0_);

%%
% geometric parameters (represented in millimeters)
R_ = 0.001*100;
n_HF_ = 130/180;
n_BC_ = 101/180;
% linkage length
% side OA
l1_ = 0.8*R_;
% side BC
l3_ = 2*R_*sin(pi*n_BC_/2);
% side DC
l4_ = 0.88296634 * R_;
% side AD
l5_ = 0.9*R_;
% side DE
l6_ = 0.4*R_;
% side CF
l7_ = 2*R_*sin((130-17-101)*pi/180/2);
% side GF
l8_ = 2*R_*sin(deg2rad(25));

%% coordinates in reference frame
syms ref_OG(t);
syms ref_OA_R(t) ref_OB_R(t) ref_OC_R(t) ref_OD_R(t) ref_OE_R(t) ref_OF_R(t);
syms ref_OA_L(t) ref_OB_L(t) ref_OC_L(t) ref_OD_L(t) ref_OE_L(t) ref_OF_L(t);

% in theta-beta frame
syms OG(t) O(t);
syms OA_R(t) OB_R(t) OC_R(t) OD_R(t) OE_R(t) OF_R(t);
syms OA_L(t) OB_L(t) OC_L(t) OD_L(t) OE_L(t) OF_L(t);

ref_OA_R(t) = [l1_*sin(theta); l1_*cos(theta)];
ref_OB_R(t) = [R_*sin(theta); R_*cos(theta)];

% OA_R = simplifyFraction(OA_R);
% OB_R = simplifyFraction(OB_R);

%% Derive vector OE & OD
% alpha_1 defined as angle EOB
alpha_1 = pi - theta;
% alpha_2 defined as angle OEA
alpha_2 = asin((l1_/(l5_+l6_)) * sin(alpha_1));

ref_OE_R(t) = [0; l1_*cos(theta)-(l5_+l6_)*cos(alpha_2)];
ref_OD_R(t) = l5_/(l5_+l6_) * ref_OE_R + l6_/(l5_+l6_) * ref_OA_R;

% OE_R = simplifyFraction(OE_R);
% OE_R = simplify(OE_R);
% OD_R = simplifyFraction(OD_R);
% OD_R = simplify(OD_R);

%% Derive vector OC
BD = ref_OD_R - ref_OB_R;
BD = simplify(BD);
DB = -BD;
l_BD = sqrt(transpose(BD) * BD);

% alpha_3 defined as angle BDC
cos_alpha_3 = (l_BD^2 + l4_^2 - l3_^2)/(2 * l_BD * l4_);
sin_alpha_3 = sqrt(1 - cos_alpha_3^2);
% rotate DB to DC direction
rot_alpha_3 = [cos_alpha_3, sin_alpha_3;
               -sin_alpha_3, cos_alpha_3];

DC = (l4_/l_BD) * rot_alpha_3 * DB;
ref_OC_R = ref_OD_R + DC;

% OC_R = simplifyFraction(OC_R);
% OC_R = simplify(OC_R);

%%
CB = ref_OB_R-ref_OC_R;
% alpha_4 defined as angle BCF
alpha_4 = acos(l3_/(2*R_)) + acos(l7_/(2*R_));
% rotate CB to CF direction
rot_alpha_4 = [cos(alpha_4), -sin(alpha_4);
               sin(alpha_4), cos(alpha_4)];

l_BF = sqrt(l3_^2 + l7_^2 - 2*l3_*l7_*cos(alpha_4));

l_CB = sqrt(transpose(CB) * CB);
CF = (l7_/l_CB) * rot_alpha_4 * CB;

ref_OF_R = ref_OC_R + CF;

% OF_R = simplifyFraction(OF_R);
% OF_R = simplify(OF_R);

%%
% alpha_5 defined as angle OGF
% alpha_6 defined as angle GOF
l_OF = sqrt(transpose(ref_OF_R) * ref_OF_R);
OF_x = [1 0]*ref_OF_R;
OF_y = [0 1]*ref_OF_R;
sin_alpha_6 = OF_x/l_OF;
sin_alpha_5 = (l_OF/l8_) * sin_alpha_6;
cos_alpha_5 = sqrt(1- sin_alpha_5^2);

ref_OG = [0; OF_y - l8_ * cos_alpha_5];

% OF_R = simplifyFraction(OF_R);
% OF_R = simplify(OF_R);

%% 
mirror_mat = [-1 0; 0 1];
ref_OA_L(t) = mirror_mat * ref_OA_R(t);
ref_OB_L(t) = mirror_mat * ref_OB_R(t);
ref_OC_L(t) = mirror_mat * ref_OC_R(t);
ref_OD_L(t) = mirror_mat * ref_OD_R(t);
ref_OE_L(t) = mirror_mat * ref_OE_R(t);
ref_OF_L(t) = mirror_mat * ref_OF_R(t);

%% transform to beta-theta frame
rot_beta = [cos(beta), sin(beta);
            -sin(beta), cos(beta)];

O(t) = [0; 0];
OA_R(t) = vpa(rot_beta * ref_OA_R(t));
OB_R(t) = vpa(rot_beta * ref_OB_R(t));
OC_R(t) = vpa(rot_beta * ref_OC_R(t));
OD_R(t) = vpa(rot_beta * ref_OD_R(t));
OE_R(t) = vpa(rot_beta * ref_OE_R(t));
OF_R(t) = vpa(rot_beta * ref_OF_R(t));
OA_L(t) = vpa(rot_beta * ref_OA_L(t));
OB_L(t) = vpa(rot_beta * ref_OB_L(t));
OC_L(t) = vpa(rot_beta * ref_OC_L(t));
OD_L(t) = vpa(rot_beta * ref_OD_L(t));
OE_L(t) = vpa(rot_beta * ref_OE_L(t));
OF_L(t) = vpa(rot_beta * ref_OF_L(t));
OG(t) = vpa(rot_beta * ref_OG(t));

%%
% diff_OG = diff(OG, t);

jacobian_OG = jacobian(OG, [phi_R; phi_L]);
%%
j_OG_11 = [1 0]*jacobian_OG.'*[1;0];
j_OG_21 = [0 1]*jacobian_OG.'*[1;0];
j_OG_12 = [1 0]*jacobian_OG.'*[0;1];
j_OG_22 = [0 1]*jacobian_OG.'*[0;1];

%%
det_j_OG = j_OG_11 * j_OG_22 - j_OG_12 * j_OG_21;
jacobian_OG_invT = (1/det_j_OG)* [j_OG_22, -1*j_OG_12;
                                  -1*j_OG_21, j_OG_11];
disp("link leg foward kinematic symbols init")

%%
% Convert to numeric
syms th
nOA_R = matlabFunction(subs(ref_OA_R, theta, th))
nOB_R = matlabFunction(subs(ref_OB_R, theta, th))
nOC_R = matlabFunction(subs(ref_OC_R, theta, th))
nOD_R = matlabFunction(subs(ref_OD_R, theta, th))
nOE_R = matlabFunction(subs(ref_OE_R, theta, th))
nOF_R = matlabFunction(subs(ref_OF_R, theta, th))

nOA_L = matlabFunction(subs(ref_OA_L, theta, th))
nOB_L = matlabFunction(subs(ref_OB_L, theta, th))
nOC_L = matlabFunction(subs(ref_OC_L, theta, th))
nOD_L = matlabFunction(subs(ref_OD_L, theta, th))
nOE_L = matlabFunction(subs(ref_OE_L, theta, th))
nOF_L = matlabFunction(subs(ref_OF_L, theta, th))

nOG = matlabFunction(subs(ref_OG, theta, th))

