#include "mex.hpp"
#include "mexAdapter.hpp"
#include "MatlabDataArray.hpp"

#include "force_tracking.hpp"

// using namespace matlab::data;
// using matlab::mex::ArgumentList;

// Base class for c++ mex function
class MexFunction : public matlab::mex::Function {
public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
        Eigen::Vector2d a(2,4);

        matlab::data::ArrayFactory factory; //create output arrays
        matlab::data::TypedArray<double> x = std::move(inputs[0]);
        matlab::data::TypedArray<double> y = std::move(inputs[1]);

        std::cout << "x" << x[0] << x[1] << std::endl;
        std::cout << "y" << y[0] << y[1] << std::endl;

        matlab::data::TypedArray<double> z = factory.createArray({2,2}, {0.0, 0.0, 0.0, 0.0});
        
        for (auto& i: x){
            i+=5;
        }
        
        for (auto& i: y){
            i-=5;
        }

        z = factory.createArray({2,2}, {double(x[0]), double(x[1]), double(y[0]), double(y[1])});
        outputs[0] = z;
    }

};