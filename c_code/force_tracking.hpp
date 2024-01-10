#ifndef __FORCE_TRACKING
#define __FORCE_TRACKING

#include <iostream>
#include <ostream>
#include <fstream>
#include <Eigen/Dense>

#include <leg_kinematics.hpp>

/* Eigen::Matrix2d StiffnessAdaption()
{
} */
Eigen::Vector2d InverseDyanmics(const Eigen::Matrix<double, 3, 2> &X_des);
Eigen::Vector2d ID2(const Eigen::Matrix<double, 3, 2> &X_des);
Eigen::Vector2d jointFriction(const Eigen::Vector2d &v_phi);
double stribeckFrictionModel(double v);

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
    // Fext = Fext * -1;

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

Eigen::Vector2d PositionBasedImpedanceFilter(const Eigen::Matrix2d &M, const Eigen::Matrix2d &K, const Eigen::Matrix2d &D,
                                             const Eigen::Matrix<double, 3, 2> &Xref, const Eigen::Matrix<double, 3, 2> &Fref,
                                             const Eigen::Matrix<double, 2, 2> &Xc, const Eigen::Matrix<double, 4, 2> &TB_fb,
                                             const Eigen::Matrix<double, 3, 2> &T_fb)
{
    /* Xref = [x_k, y_k;
              x_k_1, y_k_1;
              x_k_2, y_k_2;] */
    /* Xc = [xc_k_1, yc_k_1;
            yc_k_2, yc_k_2] */
    /* Fref = [Fx(k), Fy(k);
               Fx(k-1), Fy(k-1);
               Fx(k-2), Fy(k-2)] */
    /* TB_fb = [theta(k), beta(k);
                theta(k-1), beta(k-1);
                theta(k-2), beta(k-2)
                theta(k-3), beta(k-3)] */
    /* T_fb = [T_R(k), T_L(k);
               T_R(k-1), T_L(k-1);
               T_R(k-2), T_L(k-2)] */
    /* Fext: Force exert to ground (Obtain by Virtual work method)*/

    Eigen::Vector2d X_k = fk(TB_fb.row(0));
    Eigen::Vector2d X_k_1 = fk(TB_fb.row(1));
    Eigen::Vector2d X_k_2 = fk(TB_fb.row(2));

    Eigen::Vector2d tb_k = TB_fb.row(0);
    Eigen::Vector2d tb_k_1 = TB_fb.row(1);
    Eigen::Vector2d tb_k_2 = TB_fb.row(2);
    Eigen::Vector2d tb_k_3 = TB_fb.row(3);

    Eigen::Vector2d d_phi = dtb2dphi((tb_k - tb_k_1) / T_);
    Eigen::Vector2d d_phi_1 = dtb2dphi((tb_k_1 - tb_k_2) / T_);
    Eigen::Vector2d d_phi_2 = dtb2dphi((tb_k_2 - tb_k_3) / T_);
    Eigen::Vector2d tau_ft = jointFriction(d_phi);
    Eigen::Vector2d tau_ft_1 = jointFriction(d_phi_1);
    Eigen::Vector2d tau_ft_2 = jointFriction(d_phi_2);

    Eigen::Vector2d F_k = jointTrq2footendForce(T_fb.row(0).transpose() - tau_ft, TB_fb.row(0));
    Eigen::Vector2d F_k_1 = jointTrq2footendForce(T_fb.row(1).transpose() - tau_ft_1, TB_fb.row(1));
    Eigen::Vector2d F_k_2 = jointTrq2footendForce(T_fb.row(2).transpose() - tau_ft_2, TB_fb.row(2));

    // Eigen::Vector2d F_k = jointTrq2footendForce(T_fb.row(0).transpose(), TB_fb.row(0));
    // Eigen::Vector2d F_k_1 = jointTrq2footendForce(T_fb.row(1).transpose(), TB_fb.row(1));
    // Eigen::Vector2d F_k_2 = jointTrq2footendForce(T_fb.row(2).transpose(), TB_fb.row(2));

    Eigen::Vector2d d_F_k = F_k - Fref.row(0).transpose();
    Eigen::Vector2d d_F_k_1 = F_k_1 - Fref.row(1).transpose();
    Eigen::Vector2d d_F_k_2 = F_k_2 - Fref.row(2).transpose();

    /* Eigen::Vector2d d_F_k = F_k;
    Eigen::Vector2d d_F_k_1 = F_k_1;
    Eigen::Vector2d d_F_k_2 = F_k_2; */

    Eigen::Vector2d E_k_1 = Xref.row(1) - Xc.row(0);
    Eigen::Vector2d E_k_2 = Xref.row(2) - Xc.row(1);

    Eigen::Matrix<double, 2, 2> w1 = K * pow(T_, 2) + 2 * D * T_ + 4 * M;
    Eigen::Matrix<double, 2, 2> w2 = 2 * K * pow(T_, 2) - 8 * M;
    Eigen::Matrix<double, 2, 2> w3 = K * pow(T_, 2) - 2 * D * T_ + 4 * M;

    Eigen::Vector2d E_k;
    E_k = w1.inverse() * (pow(T_, 2) * (d_F_k + 2 * d_F_k_1 + d_F_k_2) - w2 * E_k_1 - w3 * E_k_2);
    Eigen::Vector2d Xc_k = Xref.row(0).transpose() - E_k;

    /* std::ofstream logfile;
    logfile.open ("/home/guanlunlu/Corgi_force_control/log.txt", std::ios_base::app | std::ios_base::in);
    logfile << "Trq: " << T_fb.row(0) << std::endl;
    logfile << "TB: " << TB_fb.row(0) << std::endl;
    logfile << "F_k: " << F_k.transpose() << std::endl;
    logfile << "F_k_1: " << F_k_1.transpose() << std::endl;
    logfile << "F_k_2: " << F_k_2.transpose() << std::endl;
    logfile << "E_k: " << E_k.transpose() << std::endl;
    logfile << "X_d: " << Xref.row(0) << std::endl;
    logfile << "Xc_k: " << Xc_k.transpose() << std::endl;
    logfile << "--" << std::endl;
    logfile.close(); */

    /* if (Xref.row(0)[0] > -0.1)
    {
        // std::cout << "Trq: " << T_fb.row(0) << std::endl;
        // std::cout << tb_k.transpose() << "\n" << tb_k_1.transpose() << std::endl;
        // std::cout << "dphi: " << d_phi.transpose() << std::endl;
        // std::cout << "Trq_ft: " << tau_ft.transpose() << std::endl;
        // std::cout << "Trq_total: " << T_fb.row(0)-tau_ft.transpose() << std::endl;
        // std::cout << "TB: " << TB_fb.row(0) << std::endl;
        // std::cout << "F_k: " << F_k.transpose() << std::endl;
        // std::cout << "F_k_1: " << F_k_1.transpose() << std::endl;
        // std::cout << "F_k_2: " << F_k_2.transpose() << std::endl;
        // // std::cout << "dF_k: " << d_F_k.transpose() << std::endl;
        // // std::cout << "w1: " << w1.inverse() << std::endl;
        // std::cout << "E_k: " << E_k.transpose() << std::endl;
        // std::cout << "X_d: " << Xref.row(0) << std::endl;
        // std::cout << "Xc_k: " << Xc_k.transpose() << std::endl;
        // std::cout << "--" << std::endl;
    } */
    Eigen::Vector2d X_d = Xref.row(0);
    // return X_d;
    return Xc_k;
}

Eigen::Matrix<double, 2, 3> AdaptiveStiffness(const Eigen::Matrix2d &F_d, const Eigen::Matrix<double, 2, 2> &T_fb, const Eigen::Matrix2d &K, const Eigen::Matrix2d &Alpha,
                                              const Eigen::Matrix2d &r_k_1, const Eigen::Matrix<double, 2, 2> &X_des, const Eigen::Matrix<double, 2, 2> &TB_fb)
{
    // F_d: Desired Force, leg exerted to ground
    // F_b: Feedback Force, leg exerted to ground
    // Eigen::Vector2d E_F = F_d - F_b;
    /* TB_fb = [theta(k), beta(k);
                theta(k-1), beta(k-1)] */

    /* Eigen::Vector2d X_k = fk(TB_fb.row(0));
    Eigen::Vector2d E_k = X_des.row(0).transpose() - X_k;
    Eigen::Vector2d X_k_1 = fk(TB_fb.row(1));
    Eigen::Vector2d E_k_1 = X_des.row(1).transpose() - X_k_1;
    Eigen::Vector2d V_E_k = (E_k - E_k_1) / T_;

    Eigen::Vector2d tb_k = TB_fb.row(0);
    Eigen::Vector2d tb_k_1 = TB_fb.row(1);
    Eigen::Vector2d d_phi = dtb2dphi((tb_k - tb_k_1) / T_);
    Eigen::Vector2d tau_ft = jointFriction(d_phi);
    Eigen::Vector2d F_b = jointTrq2footendForce(T_fb - tau_ft, TB_fb.row(0));
    Eigen::Vector2d E_F = F_b - F_d;

    Eigen::Matrix2d E_F_M;
    E_F_M << E_F[0], 0,
        0, E_F[1];

    Eigen::Matrix2d V_E{{V_E_k[0], 0},
                        {0, V_E_k[1]}};

    Eigen::Matrix2d w{{1e-8, 0},
                      {0, 1e-8}};
    Eigen::Matrix2d r_k = r_k_1 + Alpha * K.inverse() * E_F_M;
    Eigen::Matrix2d d_K = K * (V_E + w).inverse() * r_k;
    Eigen::Matrix2d K_new = K + d_K;
    Eigen::Matrix<double, 2, 3> output;

    output << K_new.coeff(0, 0), K_new.coeff(0, 1), r_k.coeff(0, 0), K_new.coeff(1, 0), K_new.coeff(1, 1), r_k.coeff(1, 0);
    std::cout << "E_F: " << E_F.transpose() << std::endl;
    std::cout << "r_k_1: " << r_k_1.coeff(0, 0) << " " << r_k_1.coeff(1, 1) << std::endl;
    std::cout << "K: " << K_new.coeff(0, 0) << " " << K_new.coeff(1, 1) << std::endl;
    std::cout << "--" << std::endl;*/

    // Eigen::Vector2d tb_k = TB_fb.row(0);
    // Eigen::Vector2d tb_k_1 = TB_fb.row(1);
    // Eigen::Vector2d d_phi = dtb2dphi((tb_k - tb_k_1) / T_);
    // Eigen::Vector2d tau_ft = jointFriction(d_phi);

    Eigen::Vector2d F_b = jointTrq2footendForce(T_fb.row(0).transpose(), TB_fb.row(0));
    Eigen::Vector2d F_b_1 = jointTrq2footendForce(T_fb.row(1).transpose(), TB_fb.row(1));
    Eigen::Vector2d E_F = F_b - F_d.row(0).transpose();
    Eigen::Vector2d E_F_1 = F_b_1 - F_d.row(1).transpose();
    // E_F = E_F * -1;
    // E_F_1 = E_F_1 * -1;
    Eigen::Vector2d d_E_F = (E_F - E_F_1)/T_;
    
    Eigen::DiagonalMatrix<double, 2> E_F_M(E_F[0], E_F[1]);
    Eigen::DiagonalMatrix<double, 2> d_E_F_M(d_E_F[0], d_E_F[1]);

    Eigen::Matrix<double, 2, 3> output;
    Eigen::Matrix2d Kp{{100, 0}, 
                       {0, 100}};
    Eigen::Matrix2d Kd{{40, 0}, 
                       {0, 40}};
    Eigen::Matrix2d K_ = K + Kp * E_F_M + Kd * d_E_F_M;

    output << K_.coeff(0,0), K_.coeff(0,1), 0,
              K_.coeff(1,0), K_.coeff(1,1), 0;

    return output;
}

Eigen::Vector2d PB_impf2(const Eigen::Matrix2d &M, const Eigen::Matrix2d &K, const Eigen::Matrix2d &D,
                         const Eigen::Matrix<double, 3, 2> &Xref, const Eigen::Matrix<double, 2, 1> &Fref,
                         const Eigen::Matrix<double, 3, 2> &TB_fb, const Eigen::Matrix<double, 2, 1> &T_fb)
{
    /* Xref = [x_d, y_d;
              vx_d, vy_d;
              ax_d, ay_d;] */
    /* Fref = [Fx(k), Fy(k)] */
    Eigen::Vector2d P_d = Xref.row(0);
    Eigen::Vector2d V_d = Xref.row(1);
    Eigen::Vector2d A_d = Xref.row(2);

    Eigen::Vector2d X_k = fk(TB_fb.row(0));
    Eigen::Vector2d X_k_1 = fk(TB_fb.row(1));
    Eigen::Vector2d X_k_2 = fk(TB_fb.row(2));
    Eigen::Vector2d V_k = (X_k - X_k_1) / T_;
    Eigen::Vector2d V_k_1 = (X_k_1 - X_k_2) / T_;
    Eigen::Vector2d A_k = (V_k - V_k_1) / T_;
    // Eigen::Matrix<double, 3, 2> eef_fb_state;
    // eef_fb_state << X_k[0], X_k[1], V_k[0], V_k[1], A_k[0], A_k[1];
    // Eigen::Vector2d tau_inertia = InverseDyanmics(eef_fb_state);

    Eigen::Vector2d tb_k = TB_fb.row(0);
    Eigen::Vector2d tb_k_1 = TB_fb.row(1);
    Eigen::Vector2d tb_k_2 = TB_fb.row(2);
    Eigen::Vector2d dtb_k = (tb_k - tb_k_1) / T_;
    Eigen::Vector2d dtb_k_1 = (tb_k_1 - tb_k_2) / T_;
    Eigen::Vector2d ddtb_k = (dtb_k - dtb_k_1) / T_;
    Eigen::Matrix<double, 3, 2> tb_fb_state;
    tb_fb_state << tb_k[0], tb_k[1], dtb_k[0], dtb_k[1], ddtb_k[0], ddtb_k[1];
    Eigen::Vector2d tau_inertia = ID2(tb_fb_state);

    Eigen::Vector2d d_phi = dtb2dphi((tb_k - tb_k_1) / T_);
    Eigen::Vector2d tau_ft = jointFriction(d_phi);
    Eigen::Vector2d F_k = jointTrq2footendForce(T_fb - tau_inertia - tau_ft, TB_fb.row(0));
    // Eigen::Vector2d F_k = jointTrq2footendForce(T_fb, TB_fb.row(0)); // no friction

    Eigen::Vector2d E_F_k = F_k - Fref;
    Eigen::Vector2d A_c = A_d - M.inverse() * (E_F_k - D * (V_d - V_k) - K * (P_d - X_k));
    std::cout << "T_fb:" << T_fb.transpose() << std::endl;
    std::cout << "tau_inertia:" << tau_inertia.transpose() << std::endl;
    std::cout << "tau_ft:" << tau_ft.transpose() << std::endl;
    std::cout << "Net torque: " << (T_fb - tau_inertia - tau_ft).transpose() << std::endl;
    std::cout << "Net force: " << F_k.transpose() << std::endl;
    std::cout << "E_F_k: " << E_F_k.transpose() << std::endl;
    std::cout << "P_d " << P_d.transpose() << std::endl;
    // std::cout << "X_k " << X_k.transpose() << std::endl;
    std::cout << "E_pos: " << (P_d - X_k).transpose() << std::endl;
    std::cout << "-" << std::endl;
    return A_c;
}

Eigen::Vector2d AdaptiveImpedanceFilter(const Eigen::Matrix2d &M, const Eigen::Matrix2d &K, const Eigen::Matrix2d &D,
                                        const Eigen::Matrix<double, 3, 2> &Xref, const Eigen::Matrix<double, 3, 2> &Fref,
                                        const Eigen::Matrix<double, 2, 2> &Xc, const Eigen::Matrix<double, 4, 2> &TB_fb,
                                        const Eigen::Matrix<double, 3, 2> &T_fb, const Eigen::Matrix2d &K_f, const Eigen::Matrix2d &K_v)
{
    /* Xref = [x_k, y_k;
              x_k_1, y_k_1;
              x_k_2, y_k_2;] */
    /* Xc = [xc_k_1, yc_k_1;
            yc_k_2, yc_k_2] */
    /* Fref = [Fx(k), Fy(k);
               Fx(k-1), Fy(k-1);
               Fx(k-2), Fy(k-2)] */
    /* TB_fb = [theta(k), beta(k);
                theta(k-1), beta(k-1);
                theta(k-2), beta(k-2)
                theta(k-3), beta(k-3)] */
    /* T_fb = [T_R(k), T_L(k);
               T_R(k-1), T_L(k-1);
               T_R(k-2), T_L(k-2)] */
    /* K_f = diag(Kf_x, kf_y) */
    /* K_v = diag(Kv_x, kv_y) */
    /* Fext: Force exert to ground (Obtain by Virtual work method)*/

    Eigen::Vector2d X_k = fk(TB_fb.row(0));
    Eigen::Vector2d X_k_1 = fk(TB_fb.row(1));
    Eigen::Vector2d X_k_2 = fk(TB_fb.row(2));

    Eigen::Vector2d tb_k = TB_fb.row(0);
    Eigen::Vector2d tb_k_1 = TB_fb.row(1);
    Eigen::Vector2d tb_k_2 = TB_fb.row(2);
    Eigen::Vector2d tb_k_3 = TB_fb.row(3);

    Eigen::Vector2d d_phi = dtb2dphi((tb_k - tb_k_1) / T_);
    Eigen::Vector2d d_phi_1 = dtb2dphi((tb_k_1 - tb_k_2) / T_);
    Eigen::Vector2d d_phi_2 = dtb2dphi((tb_k_2 - tb_k_3) / T_);
    Eigen::Vector2d tau_ft = jointFriction(d_phi);
    Eigen::Vector2d tau_ft_1 = jointFriction(d_phi_1);
    Eigen::Vector2d tau_ft_2 = jointFriction(d_phi_2);

    Eigen::Vector2d F_k = jointTrq2footendForce(T_fb.row(0).transpose() - tau_ft, TB_fb.row(0));
    Eigen::Vector2d F_k_1 = jointTrq2footendForce(T_fb.row(1).transpose() - tau_ft_1, TB_fb.row(1));
    Eigen::Vector2d F_k_2 = jointTrq2footendForce(T_fb.row(2).transpose() - tau_ft_2, TB_fb.row(2));

    Eigen::Vector2d d_F_k = F_k - Fref.row(0).transpose();
    Eigen::Vector2d d_F_k_1 = F_k_1 - Fref.row(1).transpose();
    Eigen::Vector2d d_F_k_2 = F_k_2 - Fref.row(2).transpose();

    /* Eigen::Vector2d d_F_k = F_k;
    Eigen::Vector2d d_F_k_1 = F_k_1;
    Eigen::Vector2d d_F_k_2 = F_k_2; */

    Eigen::Vector2d E_k_1 = Xref.row(1) - Xc.row(0);
    Eigen::Vector2d E_k_2 = Xref.row(2) - Xc.row(1);

    Eigen::Matrix2d I{{1, 1}, {1, 1}};

    Eigen::Matrix<double, 2, 2> c1 = pow(T_, 2) * (I - K_f);
    Eigen::Matrix<double, 2, 2> w1 = c1 - 2 * K_v * T_;
    Eigen::Matrix<double, 2, 2> w2 = 2 * c1;
    Eigen::Matrix<double, 2, 2> w3 = c1 + 2 * K_v * T_;
    Eigen::Matrix<double, 2, 2> w4 = 4 * M + 2 * D * T_;
    Eigen::Matrix<double, 2, 2> w5 = -8 * M;
    Eigen::Matrix<double, 2, 2> w6 = 4 * M - 2 * D * T_;

    Eigen::Vector2d E_k;
    E_k = w4.inverse() * (-w5 * E_k_1 - w6 * E_k_2 + w1 * d_F_k + w2 * d_F_k_1 + w3 * d_F_k_2);

    Eigen::Vector2d Xc_k = Xref.row(0).transpose() - E_k;
    if (Xref.row(0)[0] > -0.1)
    {
        // std::cout << "Trq: " << T_fb.row(0) << std::endl;
        // std::cout << tb_k.transpose() << "\n" << tb_k_1.transpose() << std::endl;
        // std::cout << "dphi: " << d_phi.transpose() << std::endl;
        // std::cout << "Trq_ft: " << tau_ft.transpose() << std::endl;
        // std::cout << "Trq_total: " << T_fb.row(0)-tau_ft.transpose() << std::endl;
        // std::cout << "TB: " << TB_fb.row(0) << std::endl;
        // std::cout << "F_k: " << F_k.transpose() << std::endl;
        // std::cout << "F_k_1: " << F_k_1.transpose() << std::endl;
        // std::cout << "F_k_2: " << F_k_2.transpose() << std::endl;
        // // std::cout << "dF_k: " << d_F_k.transpose() << std::endl;
        // // std::cout << "w1: " << w1.inverse() << std::endl;
        // std::cout << "E_k: " << E_k.transpose() << std::endl;
        // std::cout << "X_d: " << Xref.row(0) << std::endl;
        // std::cout << "Xc_k: " << Xc_k.transpose() << std::endl;
        // std::cout << "--" << std::endl;
    }
    Eigen::Vector2d X_d = Xref.row(0);
    // return X_d;
    return Xc_k;
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
    std::cout << "Frm_Tb = " << Frm_Tb.transpose() << std::endl;
    joint_trq = FrmTb2jointTrq(Frm_Tb, tb[0]);

    return joint_trq;
}

Eigen::Vector2d ID2(const Eigen::Matrix<double, 3, 2> &TB)
{
    Eigen::Vector2d tb = TB.row(0);
    Eigen::Vector2d dtb = TB.row(1);
    Eigen::Vector2d ddtb = TB.row(2);

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
    // std::cout << "Frm_Tb = " << Frm_Tb.transpose() << std::endl;
    joint_trq = FrmTb2jointTrq(Frm_Tb, tb[0]);

    return joint_trq;
}

Eigen::Vector2d jointFriction(const Eigen::Vector2d &v_phi)
{
    /* Apply Stribeck friction model */
    double tf_R = stribeckFrictionModel(v_phi[0]);
    double tf_L = stribeckFrictionModel(v_phi[1]);
    Eigen::Vector2d t_friction(tf_R, tf_L);
    return t_friction;
}

double stribeckFrictionModel(double v)
{
    double v_st = breakaway_vel * sqrt(2);
    double v_coul = breakaway_vel / 10;
    double e = std::exp(1);
    double F = sqrt(2 * e) * (breakaway_Ft - coulumb_Ft) * std::exp(-pow((v / v_st), 2)) * v / v_st + coulumb_Ft * tanh(v / v_coul) + viscous_cff * v;
    return F;
}

#endif