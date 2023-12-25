#include "mex.hpp"
#include "mexAdapter.hpp"
#include "MatlabDataArray.hpp"

#include "force_tracking.hpp"

// using namespace matlab::data;
// using matlab::mex::ArgumentList;

// Base class for c++ mex function
class MexFunction : public matlab::mex::Function
{
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
    {
        matlab::data::ArrayFactory factory; // create output arrays
        matlab::data::TypedArray<double> x = std::move(inputs[0]);
        matlab::data::TypedArray<double> y = std::move(inputs[1]);
        matlab::data::TypedArray<double> K = std::move(inputs[2]);
        matlab::data::TypedArray<double> D = std::move(inputs[3]);
        matlab::data::TypedArray<double> M = std::move(inputs[4]);

        Eigen::Matrix<double, 3, 2> X_des;
        X_des << x[0], y[0],
            x[1], y[1],
            x[2], y[2];

        std::cout << "X_des \n"
                  << X_des << std::endl;

        matlab::data::TypedArray<double> z = factory.createArray({1, 2}, {0.0, 0.0});

        z = factory.createArray({1, 2}, {0.0, 1.0});
        outputs[0] = z;
    }
};