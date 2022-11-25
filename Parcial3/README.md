# Parcial Final Introducción a HPC
# Por: Juan Pablo Blanco
# Universidad Sergio Arboleda 2022

El presente proyecto tiene como objetivo realizar una comparativa en predicciones de precios de computadores por medio de un modelo de regresión lineal implementado tanto con python como con c++. Para un correcto despliegue del proyecto en Qt se recomienda ejecutar los siguientes comandos (créditos al docente Jhon Corredor):
```
sudo apt install libeigen3-dev
ln -sf  /usr/include/eigen3/Eigen Eigen
ln -sf  /usr/include/eigen3/unsupported unsupported
sudo apt-get install libboost-all-dev
ln -sf /usr/include/boost boost
sudo apt install cmake
```


En el repositorio se encontrará un notebook .ipynb que muestra todo el documento sobre la elaboración del parcial, también se encuentra adjunto el dataset utilizado, una carpeta **Images** con pantallazos de algunos fragmentos clave del código en c++, la carpeta donde se encuentra alojado el modelo de Regresión lineal implementado con c++, en ella también se encuentra una carpeta denominada **Archivos** donde están los ficheros creados por el programa. Por último recuerde que a la hora de ejecutar se debe colocar como argumentos de entrada la siguiente información: `../LinealRegresion/Dataset/Computers.csv "," false`.


...Espero que disfrute el proyecto, cualquier comentario escribir a [juan.blancomarquez54@gmail.com] o a [juan.blanco01@usa.edu.co] 😊
