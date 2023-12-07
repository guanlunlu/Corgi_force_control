# include <Eigen/Dense>

double deg2rad(double deg);
double rad2deg(double rad);
double polyval(const Eigen::VectorXd& coeff, double x);
Eigen::VectorXd polyder(const Eigen::VectorXd& coeff);


Eigen::Vector2d phi2tb(const Eigen::Vector2d& phi){
    Eigen::Vector2d tb;
    Eigen::Matrix2d t;
    Eigen::Vector2d b;
    t << 1, -1, 1, 1;
    b << deg2rad(17), 0;
    tb = 1/2 * t * phi + b;
    return tb;
}

Eigen::Vector2d tb2phi(const Eigen::Vector2d& tb){
    Eigen::Vector2d phi;
    Eigen::Matrix2d t;
    Eigen::Vector2d b;
    t << 1, 1, -1, 1;
    b << deg2rad(17), -deg2rad(17);
    phi = t*tb-b;
    return phi;
}

Eigen::Vector2d fk(const Eigen::Vector2d& tb)
{
    double theta = tb[0];
    double beta = tb[1];

    Eigen::VectorXd fk_pc_(8);
    fk_pc_ << -0.0004362, 0.00715474, -0.04529168, 0.13936602, -0.22479562, 0.19297458, 0.01846436, 0.08280706;

    double L = polyval(fk_pc_, theta);
    Eigen::Vector2d point_G;
    point_G << -L*sin(beta), -L*cos(beta);
    return point_G;
}

Eigen::Vector2d ik(const Eigen::Vector2d& xy)
{
    double x = xy[0];
    double y = xy[1];

    Eigen::VectorXd ik_pc_(8);
    ik_pc_ << 4.10837754e+05, -6.25071622e+05, 4.02616603e+05, -1.41754291e+05, 2.93469460e+04, -3.56228405e+03, 2.44240485e+02, -7.12383946e+00;

    double L = sqrt(pow(x, 2)+pow(y, 2));
    double theta = polyval(ik_pc_, L);

    Eigen::Vector2d u_xy;
    Eigen::Vector2d u_y(0,1);
    u_xy = xy/L;
    double beta = acos(-u_xy.adjoint()*u_y);
    Eigen::Vector2d tb;
    tb << theta, beta;
    return tb;
}

Eigen::Matrix2d jacG(const Eigen::Vector2d& tb){
    /* Jacobian of foot end point G */
    double theta = tb[0];
    double beta = tb[1];

    Eigen::VectorXd fk_pc_(8);
    fk_pc_ << -0.0004362, 0.00715474, -0.04529168, 0.13936602, -0.22479562, 0.19297458, 0.01846436, 0.08280706;
    Eigen::VectorXd d_fk_pc(7);
    d_fk_pc = polyder(fk_pc_);

    double L_p_theta = polyval(d_fk_pc, theta);
    double L = polyval(fk_pc_, theta);

    Eigen::Matrix2d jacG;
    jacG << -L_p_theta * sin(beta), -L*cos(beta),
            -L_p_theta * cos(beta), L*sin(beta);
    return jacG;
}

double polyval(const Eigen::VectorXd& coeff, double x){
    double px = 0;
    int ord = coeff.size()-1;
    
    for(int n = ord; n >= 0; n--){
        px += coeff(coeff.size()-1-n) * pow(x, n);
    }
    return px;
}

Eigen::VectorXd polyder(const Eigen::VectorXd& coeff){
    int n = coeff.size()-1;
    Eigen::VectorXd d_coeff(n);
    d_coeff.fill(0);

    for(int i = 0; i <= n-1; i++){
        d_coeff[i] = coeff[i] * (n-i);
    }
    return d_coeff;
}


double deg2rad(double deg){
    return deg * M_PI /180.0;
}

double rad2deg(double rad){
    return rad * 180.0 / M_PI;
}