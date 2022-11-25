/*
 * Fecha: 21 sept 2022
 * Autor: Juan PAblo Blanco
 * Materia: HPC
 * Tópico: Implementación de la Regresión Lineal como
 * modelo en C++
 * Requerimientos:
 * - Construir una clase Extraction, que permita
 * manipular, extraer y cargar los datos.
 * - Construir una clase LinearRegression, que permita
 * los calculos de la función de costo, gradiente descendiente
 * entre otras. */

#include "Extraccion/extractiondata.h"
#include "Regression/linearregresion.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <list>
#include <vector>
#include <fstream>

int main(int argc, char* argv[])
{
    std::cout<<"**** REGRESIÓN LINEAL PARA PREDECIR PRECIOS DE PC EN C++ ****"<<std::endl;
    /* Se crea un objeto tipo Extraccion */
    ExtractionData ExData(argv[1], argv[2], argv[3]);

    /* Se instancia la clase de regression lineal en un objeto */
    LinearREgresion modeloLR;

    /* Se crea un vector de vectores del tipo String para cargar objeto ExData lectura */
    std::vector<std::vector<std::string>> dataframe = ExData.LeerCSV();

    /* Cantidad de filas y columnas */
    int filas = dataframe.size() + 1;
    int columnas = dataframe[0].size();

    std::cout << "Filas: " << filas << std::endl;
    std::cout << "Columnas: " << columnas << std::endl;

    /* Se aplica el método getDummies para la conversión de variables categóricas */
    dataframe = ExData.GetDummies(dataframe, filas, columnas);

    /* Se crea una matriz Eigen, para ingresar los valores de esa matriz */
    Eigen::MatrixXd matData = ExData.CSVtoEigen(dataframe, filas, columnas);

    // A continuación se modificará la matriz de datos para que los precios queden al final

    Eigen::VectorXd aux = matData.col(9).array();
    matData.col(9)= matData.col(0).array();
    matData.col(0) = aux;

    /*Se normaliza la matriz de los datos */
    Eigen::MatrixXd matNorm = ExData.Norm(matData);

    /*Se divide en datos de entrenamiento y datos de prueba*/
    Eigen::MatrixXd X_train, y_train, X_test, y_test;

    std::tuple<Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd> div_datos = ExData.TrainTestSplit(matNorm, 0.8);
    /*Se descomprime la tupla en 4 conjuntos */

    std::tie(X_train,y_train,X_test,y_test) = div_datos;


    std::cout<<"Matriz de entrenamiento, número " << X_train.rows() << " de Filas"<<std::endl;
    std::cout<<"Matriz de prueba, número " << X_test.rows() << " de Filas"<<std::endl;
    std::cout<<"Matriz total, número " << matNorm.rows() << " de Filas"<<std::endl;

    /* Se crean vectores auxiliares para prueba y entrenamiento inicializando en 1 */
    Eigen::MatrixXd V_train = Eigen::VectorXd::Ones(X_train.rows());
    Eigen::MatrixXd V_test = Eigen::VectorXd::Ones(X_test.rows());

    /* Se redimensiona la matriz de entrenamiento y de prueba para ser
     * ajustadas a los vectores auxiliares anteriores */
    X_train.conservativeResize(X_train.rows(), X_train.cols()+1);
    X_train.col(X_train.cols()-1) = V_train;

    X_test.conservativeResize(X_test.rows(), X_test.cols()+1);
    X_test.col(X_test.cols()-1) = V_test;

    /* Se crea el vector de coeficientes theta */
    Eigen::VectorXd theta = Eigen::VectorXd::Zero(X_train.cols());

    //std::cout<<"THETA INICIAL\n\n"<<theta;

    /* Se establece el alpha como ratio de aprendizaje de tipo flotante */
    float alpha = 0.01;
    int num_iter = 1000;

    /* Se crea un vector para almacenar la theta de salida (Parametros m y d) */
    Eigen::VectorXd theta_out;

    /* Se crea un vector sencillo (std) de flotantes
     * para almacenar los valores del costo */
    std::vector<float> costo;

    /* Se calcula el gradiente descendiente */
    std::tuple<Eigen::VectorXd, std::vector<float>> g_descendiente = modeloLR.GradientDescent(X_train,
                                                                                              y_train,
                                                                                              theta,
                                                                                              alpha,
                                                                                              num_iter);
    /* Se desempaqueta la gradiente descendiente */
    std::tie(theta_out, costo) = g_descendiente;

    /* Se almacena los valores de thetas y costos en un fichero
     * para posteriormente ser visualizados */
    ExData.VectorToFile(costo, "../LinealRegresion/Archivos/costosPC.txt");
    ExData.EigenToFile(theta_out, "../LinealRegresion/Archivos/thetasPC.txt");

    /* Se extrae el promedio de la matriz de entrada */
    auto prom_data = ExData.Promedio(matData);
    /* Se extraen los valores de las variables independientes */
    auto var_prom_independientes = prom_data(0,9);

    /* Se escalan los datos */
    auto datos_escalados = matData.rowwise() - matData.colwise().mean();

    /* Se extrae la desviación estandar de los datos escalados */
    auto desv_stand = ExData.DevStand(datos_escalados);

    //std::cout << "Desviación con C++: " << desv_stand << std::endl;

    /* Se extraen los valores de la variable independiente */
    auto var_desv_independientes = desv_stand(0, 9);

    //std::cout<<X_train<<"\n\n\n";
    //std::cout<<theta_out<<"\n\n\n";
    /* Se crea una matriz para almacenar los valores estimados de entrenamiento */
    Eigen::MatrixXd y_train_hat = (X_train * theta_out * var_desv_independientes).array() + var_prom_independientes;
    Eigen::MatrixXd y_test_hat = (X_test * theta_out * var_desv_independientes).array() + var_prom_independientes;
    /* Matriz para los valores reales de Y */
    Eigen::MatrixXd y_train_real = matData.col(9).topRows(5007);
    Eigen::MatrixXd y_test_real = matData.col(9).bottomRows(1252);

    ExData.EigenToFile(y_train_hat, "../LinealRegresion/Archivos/predicciones_train.txt");
    ExData.EigenToFile(y_test_hat, "../LinealRegresion/Archivos/predicciones_test.txt");

    /* Se revisa que tan bueno fue el modelo a traves de la metrica de rendimiento */
    float metrica_R2 = modeloLR.R2_Score(y_train_real, y_train_hat);
    std::cout << "Metrica R2 con C++: " << metrica_R2 << std::endl;

    float metrica_R2_test = modeloLR.R2_Score(y_test_real, y_test_hat);
    std::cout<<"R2 con test: "<<metrica_R2_test<<std::endl;
    return EXIT_SUCCESS;
}
