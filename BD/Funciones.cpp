#include "Funciones.h"

string numberString(long long number){
	string p;
	if(number==0)return "0";
	while(number!=0){
		p+=('0'+(number%10));
		number/=10;
	}
	reverse(p.begin(),p.end());
	return p;
}
long long stringNumber(string stri){
	long long x=0;
	for(long long i=0;i<stri.size();++i){
		x=x*10+(stri[i]-'0');
	}
	return x;
}
void insertarstr(string &p,string q,long long a){
	for(long long i=a;i-a<q.size();++i){
		p[i]=q[i-a];
	}
}
void insertarstr(char *p,string q,long long a){
	for(long long i=a;i-a<q.size();++i){
		p[i]=q[i-a];
	}
}
void limpiar(string &p){
	long long j=p.size()-1;
	while(p[j]==' '){--j;}
	string q;
	for(long long i=0;i<j+1;++i){
		q+=p[i];
	}
	p=q;
}
string limpiar(char *p){
	long long j=block-1;
	while(p[j]==' '){--j;}
	string q;
	for(long long i=0;i<j+1;++i){
		q+=p[i];
	}
	return q;
}
void renovar(char *p){
	for(long long i=0;i<block;++i)p[i]=' ';
}
void parsear(string& p,vector<string> & vec, char c){
	string q;
	for(long long i=0;i<p.size();i++){
		if(p[i]==c){
			vec.push_back(q);
			q="";
		}
		else{
			q+=p[i];
		}
	}
}
string extraer(char *p,long long a,long long b){
	string q;
	for(long long i=a;i<b;i++){
		q+=p[i];
	}
	return q;
}