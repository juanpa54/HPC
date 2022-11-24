#include "extractiondata.h"
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <boost/algorithm/string.hpp>
#include <list>
#include <vector>
#include <fstream>

/* Primera función miembro:
 * Lectura del fichero csv.
 * Se almacena en un vector de vectores del tipo string */

std::vector<std::vector<std::string>> ExtractionData::LeerCSV(){
    /* En primer lugar se abre y se almacena el
     * fichero en un buffer o variable temporal "archivo" */
    std::fstream archivo(dataset);
    /* Se crea un vector de vectores del tipo string */
    std::vector<std::vector<std::string>> datoString;

    /* Idea: recorrer cada linea del fichero y
     * enviarla como vector al vector de vectores del tipo string */
    std::string linea = "";
    while(getline(archivo,linea)){
        std::vector<std::string> vector;
        /* Se identifica cada elemento que compone el vector */
        // Se divide o se segmenta cada elemento con boost
        boost::algorithm::split(vector, linea, boost::is_any_of(delimitador));
        /* Finalmente se ingresa al buffer temporal */
        datoString.push_back(vector);
    }
    /* Se cierra el fichero CSV */
    archivo.close();
    /* Se retoma el vector de vectores */
    return datoString;
}

/* Función extra cuyo objetivo es convertir las
 * variables categóricas de yes/no a 0s y 1s */

std::vector<std::vector<std::string>> ExtractionData::GetDummies(std::vector<std::vector<std::string>> dataset,
                                                                 int filas,
                                                                 int columnas){
    std::vector<std::vector<std::string>> datasetModificado;
    /* Se revisa si tiene o no cabecera */
    if(header == true){
        filas = filas - 1;
    }
    /* Se busca los valores con yes/no */
    for(int i=0; i<filas; i++){
        for(int j=1; j<columnas; j++){
            /* Se modifica el valor yes->1  no->0*/
            if(dataset[i][j]=="\"yes\""){
                dataset[i][j]="1";
            }
            if(dataset[i][j]=="\"no\""){
                dataset[i][j]="0";
            }
        }
    }
    /* Se retorna el dataset resultante */
    return dataset;
}

/* Segunda función miembro:
 * Pasar el vector de vectores del tipo string
 * a un objeto del tipo Eigen: para las
 * correspondientes operaciones */
Eigen::MatrixXd ExtractionData::CSVtoEigen(std::vector<std::vector<std::string>> dataset,
                                           int filas,
                                           int columnas){
    /* Se revisa si tiene o no cabecera */
    if(header == true){
        filas = filas - 1;
    }
    Eigen::MatrixXd matriz(columnas-1, filas);
    /* Se llena la matriz  con los datos del dataSet */
    for(int i=0; i<filas; i++){
        for(int j=1; j<columnas; j++){
            /* Se pasa de flotante a string */
            matriz(j-1,i) = atof(dataset[i][j].c_str());
        }
    }
    /* Se retorna la matriz transpuesta */
    return matriz.transpose();

}

/* Función para normalizar:
 * Cuando el programador no conce el tipo de dato para utilizar en la función
 * utiliza la función auto para autodetectar. No estoy seguro que voy retornar
 * utilizo auto y el nombre de la variable */
auto ExtractionData::Promedio(Eigen::MatrixXd datos) -> decltype(datos.colwise().mean()){

  return datos.colwise().mean();

}

/*Función para extraer la desviación estandar*/

auto ExtractionData::DevStand(Eigen::MatrixXd datos) -> decltype(((datos.array().square().colwise().sum())/ (datos.rows()-1)).sqrt()){

   return ((datos.array().square().colwise().sum())/ (datos.rows()-1)).sqrt();

}

/*Función de normalización de los datos
    Se retorna la matris de datos normalizada y la función como argumeto
    la matriz de datos
    */

Eigen::MatrixXd ExtractionData:: Norm(Eigen::MatrixXd datos){

    /*Se escalan los datos X_i - mean */
    Eigen::MatrixXd mat_escalado = datos.rowwise() - Promedio(datos);
    /*Se calcular la desviaciópn estandar de los datos */


    /*Se calcular la normalización */

    Eigen::MatrixXd mat_normal = mat_escalado.array().rowwise()/DevStand(mat_escalado);

    return mat_normal;

}

/* Función para dividir en 4 grandes grupos:
 * X_train
 * y_train
 * X_test
 * y_test */

std::tuple<Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd> ExtractionData::TrainTestSplit(Eigen::MatrixXd datos, float size_train){

    /*Cantidad de filas totales */
    int filas_totales = datos.rows();
    /*Cantidad de filas para entrenamiento*/
    int filas_train = round(filas_totales*size_train);
    /*CAntidad de filas para prueba*/
    int filas_test = filas_totales - filas_train;

    /**/
    Eigen::MatrixXd Train = datos.topRows(filas_train);

    /*Se desprenden para independientes e independietnes*/
    Eigen::MatrixXd X_train = Train.rightCols(datos.cols()-1);
    Eigen::MatrixXd y_train = Train.leftCols(1);

    //std::cout<<y_train<<std::endl;
    Eigen::MatrixXd Test = datos.bottomRows(filas_test);

    /*Se desprenden para independientes e independietnes*/
    Eigen::MatrixXd X_test = Test.rightCols(datos.cols()-1);
    Eigen::MatrixXd y_test = Test.leftCols(1);

    /*Se compacta la tupla y se retorna*/

    return std::make_tuple(X_train,y_train, X_test, y_test);


}

/* Para efectos de visualización se creara la función
 * vector a fichero */

void ExtractionData::VectorToFile(std::vector<float> vector, std::string file_name){
    std::ofstream file_salida(file_name);

    /* Se crea un iterador para almacenar la salida del vector */
    std::ostream_iterator<float> salida_iterador(file_salida, "\n");

    /* Se copia cada valor desde el inicio hasta el fin
     * del iterador en el fichero*/
    std::copy(vector.begin(), vector.end(), salida_iterador);

}

/* Para efectos de manipulación y visualización se
 * crea la función matriz Eigen a fichero */
void ExtractionData::EigenToFile(Eigen::MatrixXd matriz, std::string file_name){

    std::ofstream file_salida(file_name);
    if(file_salida.is_open()){
        file_salida << matriz << "\n";
    }
}




