#include <iostream>
#include <math.h>
#include <tuple>
#include "Core" // Eigen Library
#include "LU"   // Eigen Library

using namespace std;
using namespace Eigen;

float measurements[3] = {1, 2, 3};

tuple<MatrixXf, MatrixXf> kalman_filter(MatrixXf x, MatrixXf P, MatrixXf u, MatrixXf F, MatrixXf H, MatrixXf R, MatrixXf I)
{
    for (int n = 0; n < sizeof(measurements) / sizeof(measurements[0]); n++)
    {
        //****** TODO: Kalman-filter function********//

        // Measurement Update
        // Code the Measurement Update
        // Initialize and Compute Z, y, S, K, x, and P

        // measurement update
        // get the current measurement (using z as it is an instance in time)
        MatrixXf z(1, 1);
        z << measurements[n];

        // calculate the residual for the measurement y = z - Hx
        MatrixXf y(1, 1);
        y << z - (H * x);

        // map the uncertainty into the observation space and combine with the measurement noise
        // S = H P H(t) + R where R is the measurement noise (N(0, sigma2))
        MatrixXf S(1, 1);
        S << H * P * H.transpose() + R;

        // calculate the Kalman Gain K = P H(t) S(inv)
        MatrixXf K(2, 1);
        K << P * H.transpose() * S.inverse();

        // update the prior belief using the measurement residual weighted by the Kalman gain
        x << x + (K * y);

        // update the covariance P' = (I-KH)P
        P << (I - (K * H)) * P;

        // state prediction
        // take into accound control action (external motion)
        x << (F * x) + u;
        P << F * P * F.transpose();
    }

    return make_tuple(x, P);
}

int main()
{
    MatrixXf x(2, 1); // Initial state (location and velocity)
    x << 0,
        0;
    MatrixXf P(2, 2); // Initial Uncertainty
    P << 100, 0,
        0, 100;
    MatrixXf u(2, 1); // External Motion
    u << 0,
        0;
    MatrixXf F(2, 2); // Next State Function
    F << 1, 1,
        0, 1;
    MatrixXf H(1, 2); // Measurement Function
    H << 1,
        0;
    MatrixXf R(1, 1); // Measurement Uncertainty
    R << 1;
    MatrixXf I(2, 2); // Identity Matrix
    I << 1, 0,
        0, 1;

    tie(x, P) = kalman_filter(x, P, u, F, H, R, I);
    cout << "x= " << x << endl;
    cout << "P= " << P << endl;

    return 0;
} 