#ifndef LINEARREGRESION_H
#define LINEARREGRESION_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <list>
#include <vector>
#include <fstream>

class LinearREgresion
{
public:
    float F_OLS_Costo(Eigen::MatrixXd x, Eigen::MatrixXd y, Eigen::MatrixXd thetas);
    std::tuple<Eigen::VectorXd, std::vector<float>> GradientDescent(Eigen::MatrixXd x,
                                                                    Eigen::MatrixXd y,
                                                                    Eigen::VectorXd thetas,
                                                                    float alpha,
                                                                    int num_iter);
    float R2_Score(Eigen::MatrixXd y, Eigen::MatrixXd y_hat);
};

#endif // LINEARREGRESION_H
