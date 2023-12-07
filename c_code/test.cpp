#include <iostream>
#include <force_tracking.hpp>

int main(){
    Eigen::Vector2d tb_(deg2rad(17), deg2rad(1));
    
    Eigen::Vector2d xy_(-0.0501915, -0.0869342);
    std::cout << fk(tb_) << "\n";
    double t = ik(xy_)[0];
    double b = ik(xy_)[1];
    std::cout << rad2deg(t) << ", " <<  rad2deg(b) << "\n";
    std::cout << "---" << std::endl;
    std::cout << rad2deg(tb2phi(tb_)[0]) << "," << rad2deg(tb2phi(tb_)[1]) << std::endl;
    return 0;
}