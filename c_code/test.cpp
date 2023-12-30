#include <iostream>
#include <force_tracking.hpp>

int main()
{
    kinematics_setup();
    // Eigen::Vector2d tb_(deg2rad(17), deg2rad(0));
    Eigen::Vector2d tb_(3.08774, 1.57079);

    // Eigen::Matrix2d K{{1, 0}, {0, 1}};
    // Eigen::Matrix<double, 3, 2> xref{{1, 1},
    //                                  {2, 2},
    //                                  {3, 3}};
    Eigen::Vector2d trq(-17, 17);

    Eigen::Vector2d phi(0, 0);
    std::cout << phi2tb(phi) << std::endl;

    std::cout << jointTrq2footendForce(trq, tb_) << std::endl;

    return 0;
}