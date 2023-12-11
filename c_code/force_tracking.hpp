#ifndef __FORCE_TRACKING
#define __FORCE_TRACKING

#include <iostream>
#include <Eigen/Dense>

#include <leg_kinematics.hpp>

/* Eigen::Matrix2d StiffnessAdaption()
{
} */

Eigen::Vector2d ImpedanceFilter(const Eigen::Matrix2d &K, const Eigen::Matrix2d &D, const Eigen::Matrix2d &M,
                                const Eigen::Matrix<double, 3, 2> &Xref, const Eigen::Matrix<double, 3, 2> &Xfb,
                                const Eigen::Vector2d &tb, const Eigen::Vector2d &Tfb)
{
    /* Xref = [x_ref, y_ref;
              dx_ref, dy_ref;
              ddx_ref, ddy_ref] */
    /* Fext: Force exert to leg (Obtain by Virtual work method)*/
    /* Xeef_ddot: End-effector acc. */

    Eigen::Matrix<double, 3, 2> Xe = Xref - Xfb;
    Eigen::Vector2d Xeef_ddot;
    Eigen::Vector2d Xref_ddot = Xref.row(2);
    Eigen::Vector2d Xe_pos = Xe.row(0);
    Eigen::Vector2d Xe_vel = Xe.row(1);
    Eigen::Vector2d Fext = jointTrq2footendForce(Tfb, tb);

    Xeef_ddot = Xref_ddot + M.inverse() * (K * (Xe_pos) + D * (Xe_vel) + Fext);
    return Xeef_ddot;
}

Eigen::Vector2d InverseDyanmics(const Eigen::Matrix<double, 3, 2> &X_des)
{
    /* X_des = [xt, yt,
                d_xt, d_yt,
                dd_xt, dd_yt] */
    Eigen::Vector2d X_t = X_des.row(0);
    Eigen::Vector2d dX_t = X_des.row(1);
    Eigen::Vector2d ddX_t = X_des.row(2);

    Eigen::Vector2d tb = ik(X_t);
    Eigen::Matrix2d J_1 = jacG(tb).inverse();
    Eigen::Vector2d dtb = J_1 * dX_t;
    Eigen::Vector2d ddtb = J_1 * (ddX_t - djacG(tb, dtb) * J_1 * dtb);

    Eigen::Vector2d rb(Rm(tb[0]), tb[1]);
    Eigen::Vector2d drb(dRm(tb[0], dtb[0]), dtb[1]);
    Eigen::Vector2d ddrb(ddRm(tb[0], dtb[0], ddtb[0]), ddtb[1]);
}

#endif