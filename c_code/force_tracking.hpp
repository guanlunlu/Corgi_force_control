#ifndef __FORCE_TRACKING
#define __FORCE_TRACKING

#include <iostream>
#include <Eigen/Dense>

#include <leg_kinematics.hpp>

/* Eigen::Matrix2d StiffnessAdaption()
{
} */

Eigen::Vector2d ImpedanceFilter(const Eigen::Matrix2d &M, const Eigen::Matrix2d &K, const Eigen::Matrix2d &D,
                                const Eigen::Matrix<double, 3, 2> &Xref, const Eigen::Matrix<double, 2, 2> &TB_fb,
                                const Eigen::Vector2d &T_fb)
{
    /* Xref = [x_ref, y_ref;
              dx_ref, dy_ref;
              ddx_ref, ddy_ref] */
    /* TB_fb = [theta, beta;
               dtheta, dbeta] */
    /* Fext: Force exert to leg (Obtain by Virtual work method)*/
    /* Xeef_ddot: End-effector acc. */

    /* Transform joint state to foot-end state */
    std::vector<Eigen::Vector2d> footend_state;
    footend_state = joint2footend_transform(TB_fb.row(0), TB_fb.row(1));
    // std::cout << "-- fk --\n";
    // std::cout << "d_ThetaBeta = \n";
    // std::cout << TB_fb.row(1) << std::endl;

    /* std::cout << "---\n";
    std::cout << "ThetaBeta = \n";
    std::cout << TB_fb.row(0) << std::endl;
    std::cout << "fe_fb_pos = \n";
    std::cout << footend_state[0] << std::endl;
    std::cout << "fe_fb_vel = \n";
    std::cout << footend_state[1] << std::endl; */

    Eigen::Vector2d fe_fb_pos = footend_state[0];
    Eigen::Vector2d fe_fb_vel = footend_state[1];

    Eigen::Vector2d Xref_ddot = Xref.row(2);
    Eigen::Vector2d Xe_pos = Xref.row(0).transpose() - fe_fb_pos;
    Eigen::Vector2d Xe_vel = Xref.row(1).transpose() - fe_fb_vel;
    Eigen::Vector2d Fext = jointTrq2footendForce(T_fb, TB_fb.row(0));
    Fext = Fext * -1;

    Eigen::Vector2d Xeef_ddot;
    Xeef_ddot = Xref_ddot + M.inverse() * (K * (Xe_pos) + D * (Xe_vel) + Fext);

    /* std::cout << "Xref_ddot: \n";
    std::cout << Xref_ddot << std::endl;

    std::cout << "Xe_pos: \n";
    std::cout << Xe_pos << std::endl;

    std::cout << "Xe_vel: \n";
    std::cout << Xe_vel << std::endl;

    std::cout << "Fext: \n";
    std::cout << Fext << std::endl;

    std::cout << "Xeef_ddot: \n";
    std::cout << Xeef_ddot << std::endl; */

    /* std::cout << "M: \n";
    std::cout << M << std::endl;
    std::cout << M.inverse() << std::endl;
    std::cout << "K: \n";
    std::cout << K << std::endl;
    std::cout << "D: \n";
    std::cout << D << std::endl; */

    return Xeef_ddot;
}

Eigen::Vector2d InverseDyanmics(const Eigen::Matrix<double, 3, 2> &X_des)
{
    /* X_des = [xt, yt,
                d_xt, d_yt,
                dd_xt, dd_yt] */
    Eigen::Vector2d Xd_t = X_des.row(0);
    Eigen::Vector2d dXd_t = X_des.row(1);
    Eigen::Vector2d ddXd_t = X_des.row(2);

    Eigen::Vector2d tb = ik(Xd_t);
    Eigen::Matrix2d J_1 = jacG(tb).inverse();
    Eigen::Vector2d dtb = J_1 * dXd_t;
    Eigen::Vector2d ddtb = J_1 * (ddXd_t - djacG(tb, dtb) * J_1 * dtb);

    /* q = [Rm; beta] */
    Eigen::Vector2d q(Rm(tb[0]), tb[1]);
    Eigen::Vector2d dq(dRm(tb[0], dtb[0]), dtb[1]);
    Eigen::Vector2d ddq(ddRm(tb[0], dtb[0], ddtb[0]), ddtb[1]);
    Eigen::Matrix2d Mq;
    Eigen::Vector2d Cq;
    Eigen::Vector2d Gq;
    Mq << leg_m, 0,
        0, Ic(tb[0]) + leg_m * pow(q[0], 2);
    Cq << -leg_m * q[0] * pow(q[1], 2),
        2 * leg_m * q[0] * dq[0] * dq[1] + dIc(tb[0], dtb[0]) * dq[1];
    Gq << -leg_m * g * cos(q[1]),
        -leg_m * g * q[0] * sin(q[1]);

    Eigen::Vector2d Frm_Tb;
    Eigen::Vector2d joint_trq;
    Frm_Tb = Mq * ddq + Cq + Gq;
    std::cout << "Frm_Tb = " << Frm_Tb << std::endl;
    joint_trq = FrmTb2jointTrq(Frm_Tb, tb[0]);
    // std::cout << "joint_trq = " << joint_trq << std::endl;

    return joint_trq;
}

#endif