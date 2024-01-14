function conf = getInitConf(theta)
%GETINITCONF Summary of this function goes here
%   Detailed explanation goes here

OA_R = nOA_R(theta)
OB_R = nOB_R(theta);
OC_R = nOC_R(theta);
OD_R = nOD_R(theta)
OE_R = nOE_R(theta);
OF_R = nOF_R(theta);
OG = nOG(theta);

AD_R = OD_R - OA_R;
DC_R = OC_R - OD_R;
BF_R = OF_R - OB_R;
FG_R = OG - OF_R;

out.angle_AR = vector_angle(OA_R, AD_R);
out.angle_DR = vector_angle(AD_R, DC_R);
out.angle_FR = vector_angle(BF_R, FG_R);

out.angle_AL = -1 * out.angle_AR;
out.angle_DL = -1 * out.angle_DR;
out.angle_FL = -1 * out.angle_FR;
% out.angle_AL = -1 * out.angle_AL;
% out.angle_DL = -1 * out.angle_DL;
% out.angle_AR = -1 * out.angle_AR;
% out.angle_DR = -1 * out.angle_DR;

conf = out;
end

