#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#define block 1024
using namespace std;
struct menor{
    inline bool operator()(long long a,long long b){
        return a<b;
    }
};
struct mayor{
    inline bool operator()(long long a,long long b){
        return a>b;
    }
};
struct igual{
    inline bool operator()(long long a,long long b){
        return a==b;
    }
};
struct comp{
	long long colum;
	string op;
	string valor;
	comp(long long _colum,string _op,string _valor){
		colum=_colum;
		op=_op;
		valor=_valor;
	}
};
struct columna{
	string nombre;
	string tipo;
	long long tam;
	columna(string _nombre,string _tipo,long long _tam){
		nombre=_nombre;
		tipo=_tipo;
		tam=_tam;
	}
};
struct indice{
	string nombre;
	long long tam;
	indice(string _nombre,long long _tam){
		nombre=_nombre;
		tam=_tam;
	}
};
string numberString(long long);
long long stringNumber(string);
void insertarstr(string &,string ,long long);
void limpiar(string &);
void insertarstr(char *,string,long long);
void renovar(char *);
string limpiar(char *);
void parsear(string&,vector<string>&,char);
string extraer(char *,long long,long long);
