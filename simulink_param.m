clear
addpath(genpath("c_code/"));
addpath("CAD/");
addpath("function/");
addpath("script");
addpath("impedance_control/")

bk_ft= 0.1;
bk_vel = 0.001;
col_ft = 0.01;
vis_ft = 1.5;

% bk_ft= 0.5;
% bk_vel = 0.01;
% col_ft = 0.5;
% vis_ft = 1.5;

contact_stf = 1e8;
contact_dmp = 1e3;
contact_trs = 1e-4;

joint_kp = 60;
joint_ki = 0.8;
joint_kd = 1.75;

init_xy = [-0.15, -0];
init_sphi = getSimPhiRL(ik(init_xy));
