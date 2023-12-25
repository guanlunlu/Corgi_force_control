#include <iostream>
#include <force_tracking.hpp>

int main()
{
    kinematics_setup();
    // Eigen::Vector2d tb_(deg2rad(17), deg2rad(0));
    Eigen::Vector2d tb_(deg2rad(17), deg2rad(0));

    Eigen::Matrix2d K{{1, 0}, {0, 1}};
    Eigen::Matrix<double, 3, 2> xref{{1, 1},
                                     {2, 2},
                                     {3, 3}};
    Eigen::Vector2d trq(1, -1);

    std::cout << jointTrq2footendForce(trq, tb_) << std::endl;

    return 0;
}