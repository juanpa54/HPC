/**************************************************
 * Fecha: 21 de agosto 2022
 * Autor: Juan Pablo Blanco Márquez
 * Tema: Taller Eigen
 * Asignatura: Introducción a HPC
 * ************************************************/

#include<iostream>
#include<eigen3/Eigen/Dense>

/* La mayoría de ejercicios contienen matrices 2X2 por lo que
 * se creará un objeto tipo matriz Eigen con esta forma */

/* Tipo de dato matriz 2*2 float */
Eigen::Matrix2f A, B, C;
Eigen::MatrixXf X;
/* Tipo de dato matriz 3x3 float */
Eigen::Matrix3f Mat_A, Mat_B;

void imprimirMenu(){
    std::cout<<"----- OPERACIONES MATRICIALES ---------"<<std::endl;
    std::cout<<"Recuerde que _T significa transpuesta "<<std::endl;
    std::cout<<"Recuerde que _I significa inversa "<<std::endl;
    std::cout<<"a) X = 3A-4B"<<std::endl;
    std::cout<<"b) 2X+4A=3BA"<<std::endl;
    std::cout<<"c) AXB_T=C"<<std::endl;
    std::cout<<"d) XA=B"<<std::endl;
    std::cout<<"e) X=2(AB+C)"<<std::endl;
    std::cout<<"f) X=A+3B"<<std::endl;
    std::cout<<"g) XA=B"<<std::endl;
    std::cout<<"h) AX=B"<<std::endl;
    std::cout<<"i) X=A_TA-2A"<<std::endl;
    std::cout<<"j) X=A³"<<std::endl;
    std::cout<<"k) A_TXB=C"<<std::endl;
    std::cout<<"l) X=AA_T-2AB"<<std::endl;
    std::cout<<"m) X=ABC"<<std::endl;
    std::cout<<"n) A_TX=B"<<std::endl;
    std::cout<<"o) XA=B"<<std::endl;
    std::cout<<"p) AX=B"<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"Seleccione una opción (0 para salir): "<<std::endl;
}

void puntoA(){
    A << 4, -2, 1, -7;
    B << -1, 2, 6, -5;
    std::cout<<"\nMATRIZ A \n"<<A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<B<<std::endl;
    X = 3*A - 4*B;
    std::cout<<"\nMATRIZ X (3A - 4B)\n"<<X<<std::endl;
}

void puntoB(){
    A << 0, -1, 2, 1;
    B << 1, 2, 3, 4;
    X = (3*B*A - 4*A) / 2;
    std::cout<<"\nMATRIZ A \n"<<A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<B<<std::endl;
    std::cout<<"\nMATRIZ X (3*B*A - 4*A) / 2\n"<<X<<std::endl;
}

void puntoC(){
    A << -3, -2, 3, 3;
    B << 5, 3, 9, 4;
    C << 1, 1, 0, 0;
    X = C*A.inverse()*B.transpose().inverse();
    std::cout<<"\nMATRIZ A \n"<<A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<B<<std::endl;
    std::cout<<"\nMATRIZ C \n"<<C<<std::endl;
    std::cout<<"\nMATRIZ X (C*A_-1*B_T_-1) \n"<<X<<std::endl;
}

void puntoD(){
    A<< 2, 1 , -4, -3;
    B<< 2, 2, 6, 4;
    X = B*A.inverse();
    std::cout<<"\nMATRIZ A \n"<<A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<B<<std::endl;
    std::cout<<"\nMATRIZ C \n"<<C<<std::endl;
    std::cout<<"\nMATRIZ X (B*A_-1) \n"<<X<<std::endl;
}

void puntoE(){
    /*
    Eigen::MatrixXf mat_A(3,2), mat_B(2,3);
    mat_A<< 3, 0, -1, 0, 2, 1;
    mat_B<< 1, 2, 1, 0, 0, 6;
    C<< -2, 0, -2, -5;
    X = 2*(mat_A*mat_B + C);
    std::cout<<"\nMATRIZ A \n"<<mat_A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<mat_B<<std::endl;
    std::cout<<"\nMATRIZ C \n"<<C<<std::endl;
    std::cout<<"\nMATRIZ X (2*(A*B + C)) \n"<<X<<std::endl;
    */
    std::cout<<"NO DISPONIBLE"<<std::endl;
}

void puntoF(){
    Mat_A<< 1, 5, -1, -1, 2, 2, 0, -3, 3;
    Mat_B<< -1, -4, 3, 1, -2, -2, -3, 3, -5;
    X = Mat_A + 3*Mat_B;
    std::cout<<"\nMATRIZ A \n"<<Mat_A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<Mat_B<<std::endl;
    std::cout<<"\nMATRIZ X (A + 3*B) \n"<<X<<std::endl;
}

void puntoG(){
    Mat_A<< 2, 7, 3, 3, 9, 4, 1, 5, 3;
    Mat_B<< 1, 0, 2, 0, 1, 0, 0, 0, 1;
    X = Mat_B*Mat_A.inverse();
    std::cout<<"\nMATRIZ A \n"<<Mat_A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<Mat_B<<std::endl;
    std::cout<<"\nMATRIZ X (B*A_inv) \n"<<X<<std::endl;
}

void puntoH(){
    Mat_A<< 1, 1, 1, 6, 5, 4, 13, 10, 8;
    Mat_B<< 0, 1, 2, 1, 0, 2, 1, 2, 0;
    X = Mat_A.inverse()*Mat_B;
    std::cout<<"\nMATRIZ A \n"<<Mat_A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<Mat_B<<std::endl;
    std::cout<<"\nMATRIZ X (A_inv*B) \n"<<X<<std::endl;
}

void puntoI(){
    A<< 3, -1, 0, 2;
    X = A.transpose() * A - 2*A;
    std::cout<<"\nMATRIZ A \n"<<A<<std::endl;
    std::cout<<"\nMATRIZ X (A_T * A - 2*A) \n"<<X<<std::endl;
}

void puntoJ(){
    A<< 4, 2, -1, 0;
    X = A*A*A;
    std::cout<<"\nMATRIZ A \n"<<A<<std::endl;
    std::cout<<"\nMATRIZ X (A³) \n"<<X<<std::endl;
}

void puntoK(){
    A<< 2, 4, 3, 2;
    B<< 1, 0, 2, 1;
    C<< 7, 5, 6, 1;
    X = C * A.transpose().inverse() * B.inverse();
    std::cout<<"\nMATRIZ A \n"<<A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<B<<std::endl;
    std::cout<<"\nMATRIZ C \n"<<C<<std::endl;
    std::cout<<"\nMATRIZ X (C * A_T_I *  B_T) \n"<<X<<std::endl;
}

void puntoL(){
    std::cout<<"no disponible"<<std::endl;
}

void puntoM(){
    std::cout<<"no disponible"<<std::endl;
}

void puntoN(){
    Mat_A<< 3, 4, 1, -1, -3, 3, 2, 3, 0;
    Mat_B<< 3, 9, 7, 1, 11, 7, 7, 5, 7;
    X = Mat_B * Mat_A.transpose().inverse();
    std::cout<<"\nMATRIZ A \n"<<Mat_A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<Mat_B<<std::endl;
    std::cout<<"\nMATRIZ X (B * A_T_I) \n"<<X<<std::endl;
}

void puntoO(){
    Mat_A<< 2, 5, 7, 6, 3, 4, 5, -2, -3;
    Mat_B<< -1, 1, 0, 0, 1, 1, 1, 0, -1;
    X = Mat_B * Mat_A.inverse();
    std::cout<<"\nMATRIZ A \n"<<Mat_A<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<Mat_B<<std::endl;
    std::cout<<"\nMATRIZ X (B *A_I) \n"<<X<<std::endl;
}

void puntoP(){
    Eigen::Matrix4f MatrizA, MatrizB;
    MatrizA<< 1, 1, 1, 1, 1, 1, -1, -1, 1, -1, 1, -1, 1, -1, -1, 1;1, 0, 1,
    MatrizB<< 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1;
    X = B*A.inverse();
    std::cout<<"\nMATRIZ A \n"<<MatrizA<<std::endl;
    std::cout<<"\nMATRIZ B \n"<<MatrizB<<std::endl;
    std::cout<<"\nMATRIZ X (B *A_I) \n"<<X<<std::endl;
}


int main(int argc, char *argv[])
{
    char opc = '0';
    do{
        imprimirMenu();


        std::cin >> opc;

        switch(opc){
            case 'a':
            puntoA();
            break;

            case 'b':
            puntoB();
            break;

            case 'c':
            puntoC();
            break;

            case 'd':
            puntoD();
            break;

            case 'e':
            puntoE();
            break;

            case 'f':
            puntoF();
            break;

            case 'g':
            puntoG();
            break;

            case 'h':
            puntoH();
            break;

            case 'i':
            puntoI();
            break;

            case 'j':
            puntoJ();
            break;

            case 'k':
            puntoK();
            break;

            case 'l':
            puntoL();
            break;

            case 'm':
            puntoM();
            break;

            case 'n':
            puntoN();
            break;

            case 'o':
            puntoO();
            break;

            case 'p':
            puntoP();
            break;
        }


    }while(opc!='0');

}
