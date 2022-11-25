#ifndef EXTRACTIONDATA_H
#define EXTRACTIONDATA_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <list>
#include <vector>
#include <fstream>

/**
 * Clase extraccion de datos:
 * - Leer un fichero CSV
 * - Entrar con argumentos a la clase:
 *  - Lugar del dataset(csv)
 *  - Tipo de separador
 *  - Si tiene cabecera o no
 * - Pasar a un vector de vectores de tipo string
 * - Pasar el vector de vectores String a Eigen
 * - Funcion para sacar el promedio
 * - Funcion para sacar Desviación
 * - Función para normalización
 * - Matricas
 */

class ExtractionData
{
    /** Argumentos de entrada a la clase **/
        std::string dataset;        /*Ruta del dataset*/
        std::string delimitador;    /*Separador entre datos*/
        bool header;                /*Cabecera*/
public:
    /*Se crea el constructor con los argumentos de entrada*/
    // Vectr de vectores de tipo string
    ExtractionData(std::string data,
                   std::string separador,
                   bool cabecera):
    dataset(data), delimitador(separador), header(cabecera){

    }

    /* Prototipo de metodos y funciones */
    std::vector<std::vector<std::string>> LeerCSV();
    std::vector<std::vector<std::string>> GetDummies(std::vector<std::vector<std::string>> dataset,
                                                                     int filas,
                                                                     int columnas);
    Eigen::MatrixXd CSVtoEigen(std::vector<std::vector<std::string>> dataset,
                               int filas,
                               int columnas);

    auto Promedio(Eigen::MatrixXd datos) -> decltype(datos.colwise().mean());
    auto DevStand(Eigen::MatrixXd datos) -> decltype(((datos.array().square().colwise().sum())/ (datos.rows()-1)).sqrt());
    Eigen::MatrixXd Norm(Eigen::MatrixXd datos);
    std::tuple<Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd> TrainTestSplit(Eigen::MatrixXd datos, float size_train);
    void VectorToFile(std::vector<float> vector, std::string file_name);
    void EigenToFile(Eigen::MatrixXd matriz, std::string file_name);
};

#endif // EXTRACTIONDATA_H
