#include "linearregresion.h"
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>

/* Primera función: Función de costo
 * para la regresión lineal basada en los
 * minimos cuadrados ordinarios demostrado en clase */
float LinearREgresion::F_OLS_Costo(Eigen::MatrixXd X, Eigen::MatrixXd y, Eigen::MatrixXd thetas)
{
    Eigen::MatrixXd m_interior = pow((X*thetas-y).array(), 2);
    return (m_interior.sum() / (2 * X.rows()));
}


/* Función de gradiante descendiente: En función de
 * un ratio de aprendizaje se avanza hasta encontrar
 * el punto minimo que representa el valor optimo para la función */
std::tuple<Eigen::VectorXd, std::vector<float>> LinearREgresion::GradientDescent(Eigen::MatrixXd X,
                                                                                Eigen::MatrixXd y,
                                                                                Eigen::VectorXd thetas,
                                                                                float alpha,
                                                                                int num_iter){
    //std::cout<<X<<std::endl;
    //std::cout<<"\n\n"<<y<<std::endl;
    Eigen::MatrixXd temporal = thetas;
    int parametros = thetas.rows();
    std::vector<float> costo;

    /*En costo ingresaremos los valores de la función de costo */
    costo.push_back(F_OLS_Costo(X, y, thetas));

    /* Se itera segun el numero de iteraciones y el ratio
     * de aprendizaje para encontrar los valores optimos */
    for(int i = 0; i < num_iter; i++){
        Eigen::MatrixXd error = X*thetas-y;
        for(int j = 0; j < parametros; j++){
            Eigen::MatrixXd X_i = X.col(j);
            Eigen::MatrixXd termino = error.cwiseProduct(X_i);
            temporal(j, 0) = thetas(j, 0) - ((alpha/X.rows())*termino.sum());
        }
        thetas = temporal;
        costo.push_back(F_OLS_Costo(X, y, thetas));
    }
    return std::make_tuple(thetas, costo);
}


/* A continuación se presenta la función para revisar que tan bueno es nuestro modelo:
 * Se procede a crear la metrica de rendimiento:
 * Vamos a crear R² score: Coeficiente de determinación, donde el mejor valor posible es 1 */

float LinearREgresion::R2_Score(Eigen::MatrixXd y,Eigen::MatrixXd y_hat){
    auto numerador = pow((y - y_hat).array(), 2).sum();
    auto denominador = pow(y.array() - y.mean(), 2).sum();

    return 1 - numerador/denominador;
}
