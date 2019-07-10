#include"FunGestor.h"
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <cstdlib>
#include<stdlib.h>
#include<time.h>


using namespace std;
int main(){
    string tabla;
    cin>>tabla;
    /*
    vector<columna>columnas;
    vector<indice>indices;
    columnas.push_back(columna("Id","integer",8));
    columnas.push_back(columna("Nombre","varchar",30));
    columnas.push_back(columna("Edad","integer",7));
    indices.push_back(indice("Id",10));
    indices.push_back(indice("Edad",10));
    createTable(tabla,columnas,indices);
     */
    /*
    const char* puntero;
    for(int i=0;i<30;i++) {
        vector <string> valores;
        valores.push_back(numberString(i));
        string nombre="nombre";
        valores.push_back(nombre+numberString(abs(rand())));
        valores.push_back(numberString(abs(rand())));
        insertar(tabla,valores);
    }

     */
    /*
	vector<long long>param;
	param.push_back(0);
	param.push_back(1);
	param.push_back(2);
	vector<comp>vec;
	vec.push_back(comp(0,"igual","1"));
	vector<char>operador;
	string IND="Id";
	string valor="1";
	select (tabla,param,vec,operador,IND,valor);
     */

	vector<comp>vec;
	vec.push_back(comp(0,"igual","1"));
	//vec.push_back(comp(0,"menor","50000"));
	vector<char>operador;
	//operador.push_back('&');
	string IND="Id";
	string valor="1";
	eliminar(tabla,vec,operador,IND,valor);

}
