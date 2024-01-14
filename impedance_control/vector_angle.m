function angle = vector_angle(v1,v2)
%VECTOR_ANGLE Summary of this function goes here
%   Detailed explanation goes here
v1_ = [v1; 0];
v2_ = [v2; 0];

a = asin(cross(v1_,v2_)/(norm(v1)*norm(v2)));
% if a(3) < 0
%     a = a + 2*pi;
% end

angle = a(3);
% angle = acos(dot(v1_ / norm(v1_), v2_ / norm(v2_)));
end
