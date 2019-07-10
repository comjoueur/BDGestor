#include "Funciones.h"
#include <direct.h>

void recuperarMeta(ifstream & f,vector<columna>&vec,long long &filas,long long &campos);
//tabla de la metadata, vector para recuperar la metadata,actualizar filas, numero de campos

void recuperarMeta(ifstream & f,vector<columna>&vec,vector<indice>&ind,long long &filas,long long &campos,long long &indices);
//tabla de la metadata, vector para recuperar la metadata,actualizar filas, numero de campos,indices

void createTable(string nombre,vector<columna>&vec);
//nombre de la tabla a crear, vector donde se devuelve la metadata

void createTable(string nombre,vector<columna>&vec,vector<indice>&ind);
//nombre de la tabla a crear, vector donde se devuelve la metadata

void numfilas(ofstream &f,long long &filas);
//tabla de la metadata, valor de la fila


void insertar(ofstream & f,vector<string>&vec,vector<columna> &info,long long &filas);
//tabla donde se inserta, valores a insertar de una fila,metadata, actualizacion filas

void insertar(string nombre,vector<string>&valores);
//insertar pero en Indices y tabla sin indice tambien al mismo tiempo

void eliminar(ifstream &g,ofstream & f, vector<comp>&vec,vector<columna> & info,vector<char>&operador, long long &filas);
//tabla de donde se lee,tabla de donde se escribe, vector de condiciones, metadata, operadores logicos entre condiciones, actualizacion filas

void eliminar(string nombre,vector<comp>&vec,vector<char>&operador, string IND,string valor);
//eliminar con indices

void select(ifstream &g,vector<long long>&parametro,vector<comp>&vec,vector<columna> & info,vector<char>&operador, long long filas);
//tabla donde se lee,numero de columna a mostrar, vector de condiciones, metadata,operadores logicos entre condiciones, actualizacion filas

void select(string nombre,vector<long long>&parametro,vector<comp>&vec,vector<char>&operador, string IND,string valor);
//select con indice en IND con valor valor

void update(ifstream &g,ofstream &f,vector<long long>&parametro,vector<string>&valor,vector<comp>&vec,vector<columna> & info,vector<char>&operador, long long filas);
//tabla donde se lee,tabla donde se escribe,numero de columna a mostrar,vector de valores a actualizat, vector de condiciones, metadata,operadores logicos entre condiciones, actualizacion filas



