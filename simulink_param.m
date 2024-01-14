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

joint_kp = 90;
joint_ki = 0;
joint_kd = 1;

% Start touch ground pose
start_time = 0.5;
init_xy = [-0.05, -0.185];
init_tb = ik(init_xy);
init_sphi = getSimPhiRL(init_tb);
% init_tb = [pi/2, 0];

% Simulink Start simulation pose
init_xy_0 = [-0.34*cos(deg2rad(30)), -0.34*sin(deg2rad(30))];
init_tb_0 = ik(init_xy_0);
% init_jp = getInitConf(init_tb_0(1))
init_sphi_0 = getSimPhiRL(init_tb_0);

%
adaptive_kp = 20;
adaptive_ki = 10;
adaptive_kd = 40;

%optimize
ts = linspace(0,2)
ys = [zeros(1,20), 50*ones(1,80)]
