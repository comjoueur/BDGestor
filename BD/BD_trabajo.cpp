#include"FunGestor.h"
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <cstdlib>
#include<stdlib.h>
#include<time.h>

using namespace std;

string Aleatorio(string &tipo){
	string x="str";
	long long y=((rand()%10000)+10000)%10000;
	string u=numberString(y);
	if(tipo=="varchar"){
		x+=u;
		return x;
	}
	return u;
}

int main(){
	srand(time(NULL));
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	vector<pair<string ,vector<pair<string,long long> > > > idColumna;
	//CREATE TABLE
	string consulta;
	bool estado=true;
	
	while(estado){
		getline(cin, consulta);
		
		//COMPARACION DEL CREATE TABLE
		regex verificarTable("^CREATE_TABLE(\\s+)([[:w:]]+)");
    	smatch compVerificarTable;
    	bool compVerficarTableBool=regex_search(consulta,compVerificarTable,verificarTable);
	
		//COMPARACION DEL SELECT
		regex verificarSelect("^SELECT(\\s+)(.*)(\\s+)FROM(\\s+)([[:w:]]+)(\\s*)");
		smatch compVerifcarSelect;
		bool verificarSelectbool=regex_search(consulta,compVerifcarSelect,verificarSelect);
		
		//COMPARACION DEL INSERT
		regex verificarInsert("INSERT(\\s+)(.*)(\\s+)INTO(\\s+)([[:w:]]+)(\\s+)VALUES(\\s+)([[:w:]]+)(\\s*)");
		smatch compVerificarInsert;
		bool verificarInsertbool=regex_search(consulta,compVerificarInsert,verificarInsert);
		
		//COMPARACION DEL DELETE
		regex verificarDelete("^DELETE(\\s+)FROM(\\s+)([[:w:]]+)(\\s*)");
		smatch compVerifcarDelete;
		bool verificarDeletebool=regex_search(consulta,compVerifcarDelete,verificarDelete);
		
		//COMPARACION DE UPDATE
		regex verificarUpdate("^UPDATE(\\s+)(.*)(\\s+)FROM(\\s+)([[:w:]]+)(\\s*)");
		smatch compVerificarUpdate;
		bool verificarUpdatebool=regex_search(consulta,compVerificarUpdate,verificarUpdate);
		
		//COMPARACION DE Mostrar Metadata
		regex verificarMeta("(\\s*)META(\\s+)([[:w:]]+)(\\s*)");
		smatch compVerifcarMeta;
		bool verificarMetabool=regex_search(consulta,compVerifcarMeta,verificarMeta);
		
		//COMPARACION DE ALEATORIO
		regex verificarRand("(\\s*)ALEATORIO(\\s+)([[:w:]]+)(\\s*)");
		smatch compVerifcarRand;
		bool verificarRandbool=regex_search(consulta,compVerifcarRand,verificarRand);
		
		
		pair<string, long long> poner;
		vector<pair<string, long long>> idtabla;
		
		//FUNCION CREAR TABLA
		if(compVerficarTableBool){
			sregex_iterator posverificarTable(consulta.begin(),consulta.end(),verificarTable);
    		sregex_iterator endverificarTable;
			vector<columna>vec;
			regex valoresTabla("([[:w:]]+)(\\s*),(\\s*)([[:w:]]+)");
			sregex_iterator posValoresTabla(consulta.begin(),consulta.end(),valoresTabla);
			sregex_iterator endValoresTabla;
			string tipoDato="";
			long long j=0;
			for( ;posValoresTabla!=endValoresTabla; posValoresTabla++){    
				string aux1="";
				int aux2;
				string numero(posValoresTabla->str(4));
				for(int i = 0; i < numero.size(); i++)
				{    
					if(numero[i]=='I'){
						i++;
						while(numero[i]!='I'){
							aux1+=numero[i];
							i++;
						}
						aux2=atoi (aux1.c_str());	
						tipoDato="varchar";	
					}else{
						aux2=7;
						tipoDato="integer";
					}
				}
				poner=make_pair(posValoresTabla->str(1),j);
				idtabla.push_back(poner);
				vec.push_back(columna(posValoresTabla->str(1),tipoDato,aux2));
				j++;
			}
			pair<string ,vector<pair<string,long long> > >tablacompleta(posverificarTable->str(2),idtabla);
			idColumna.push_back(tablacompleta);
			createTable(posverificarTable->str(2),vec);		
		
		}else if(verificarSelectbool){//FUNCION SELECT
			sregex_iterator posverificarSelect(consulta.begin(),consulta.end(),verificarSelect);
			sregex_iterator endverificarSelect;
			long long filas,campos;
			vector<columna>info;
			string tabla=posverificarSelect->str(5);
			string metatabla=tabla+"Meta.txt";
			const char *_metatabla=metatabla.c_str();
			ifstream metaTabla(_metatabla);
			recuperarMeta(metaTabla,info,filas,campos);
			tabla+=".txt";
			const char* _tabla=tabla.c_str();
			ifstream TablaR(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			ofstream TablaW(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			
			regex Selectcolumnas("([[:w:]]+)(\\s*),");
			sregex_iterator poselectcolumnas(consulta.begin(),consulta.end(),Selectcolumnas);
			sregex_iterator endselectcolumnas;
			
			vector<long long>eje;
			for( ;poselectcolumnas!=endselectcolumnas; poselectcolumnas++)
			{   
				if(poselectcolumnas->str(1)=="ALL"){
					for(int i=0;i<info.size();++i){
						eje.push_back(i);
					}
					break;
				}
				for(int i = 0; i < info.size(); i++)
				{
					if(info[i].nombre==poselectcolumnas->str(1)){
							eje.push_back(i);
					}
				}
			}

			regex Selectcomparadores("(\\s+)([[:w:]]+)(\\s*)(=|<|>)(\\s*)([[:w:]]+)(\\s*)");
			sregex_iterator poselectcomparadores(consulta.begin(),consulta.end(),Selectcomparadores);
			sregex_iterator endselectcomparadores;
			vector<comp>ejemplo;

			for( ;poselectcomparadores!=endselectcomparadores; poselectcomparadores++)
			{
				long long tam;	
				for(int i = 0; i < info.size(); i++)
				{
					if(info[i].nombre==poselectcomparadores->str(2)){
						tam=i;
					}
				}
				if(poselectcomparadores->str(4)=="="){
					ejemplo.push_back(comp(tam,"igual",poselectcomparadores->str(6)));	
				}else if(poselectcomparadores->str(4)==">"){
					ejemplo.push_back(comp(tam,"mayor",poselectcomparadores->str(6)));	
				}else if(poselectcomparadores->str(4)=="<"){
					ejemplo.push_back(comp(tam,"menor",poselectcomparadores->str(6)));	
				}
			}

			regex Selectoperadores("(\\s*)(AND|OR)(\\s*)");
			sregex_iterator poselectoperadores(consulta.begin(),consulta.end(),Selectoperadores);
			sregex_iterator endselectoperadores;
			vector<char>operador;

			for( ;poselectoperadores!=endselectoperadores; poselectoperadores++)
			{
				if(poselectoperadores->str(2)=="OR"){
					operador.push_back('|');
				}else if(poselectoperadores->str(2)=="AND") {
					operador.push_back('&');
				}
			}
			select(TablaR,eje,ejemplo,info,operador,filas);
			ofstream MetaTabla(_metatabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			numfilas(MetaTabla,filas);
		}
		else if(verificarInsertbool){//FUNCION INSERT
			sregex_iterator posverificarInsert(consulta.begin(),consulta.end(),verificarInsert);
			sregex_iterator endverificarInsert;
			long long filas,campos;
			vector<columna>info;
			string tabla=posverificarInsert->str(5);
			string metatabla=tabla+"Meta.txt";
			const char *_metatabla=metatabla.c_str();
			ifstream metaTabla(_metatabla);
			recuperarMeta(metaTabla,info,filas,campos);
			tabla+=".txt";
			const char* _tabla=tabla.c_str();
			ifstream TablaR(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			ofstream TablaW(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			
			regex Insertcolumnas("(\\s*)([[:w:]]+)(\\s*),");
			sregex_iterator poinsertcolumnas(consulta.begin(),consulta.end(),Insertcolumnas);
			sregex_iterator endinsertcolumnas;
			vector<string>valores;
			
			for( ;poinsertcolumnas!=endinsertcolumnas; poinsertcolumnas++){
				valores.push_back(poinsertcolumnas->str(2));
			}
			insertar(TablaW,valores,info,filas);
			ofstream MetaTabla(_metatabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			numfilas(MetaTabla,filas);
		}
		else if(verificarDeletebool){//FUNCION DELETE
		    sregex_iterator posverificarDelete(consulta.begin(),consulta.end(),verificarDelete);
			sregex_iterator endverificarDelete;
			long long filas,campos;
			vector<columna>info;
			string tabla=posverificarDelete->str(3);
			string metatabla=tabla+"Meta.txt";
			const char *_metatabla=metatabla.c_str();
			ifstream metaTabla(_metatabla);
			recuperarMeta(metaTabla,info,filas,campos);
			tabla+=".txt";
			const char* _tabla=tabla.c_str();
			ifstream TablaR(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);//De donde leer
			ofstream TablaW(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);//Donde Escribir
			regex Deletecomparadores("(\\s+)([[:w:]]+)(\\s*)(=|<|>)(\\s*)([[:w:]]+)(\\s*)");
			sregex_iterator posDeletecomparadores(consulta.begin(),consulta.end(),Deletecomparadores);
			sregex_iterator endDeletecomparadores;
			vector<comp>ejemplo;

			for( ;posDeletecomparadores!=endDeletecomparadores; posDeletecomparadores++)
			{
				long long tam;
				for(int i = 0; i < info.size(); i++)
				{
					if(info[i].nombre==posDeletecomparadores->str(2)){
						tam=i;
					}
				}
				if(posDeletecomparadores->str(4)=="="){
					ejemplo.push_back(comp(tam,"igual",posDeletecomparadores->str(6)));
				}else if(posDeletecomparadores->str(4)==">"){
					ejemplo.push_back(comp(tam,"mayor",posDeletecomparadores->str(6)));
				}else if(posDeletecomparadores->str(4)=="<"){
					ejemplo.push_back(comp(tam,"menor",posDeletecomparadores->str(6)));
				}
			}
			regex Deleteoperadores("(\\s*)(AND|OR)(\\s*)");
			sregex_iterator posDeleteoperadores(consulta.begin(),consulta.end(),Deleteoperadores);
			sregex_iterator endDeleteoperadores;
			vector<char>operador;
			for( ;posDeleteoperadores!=endDeleteoperadores; posDeleteoperadores++)
			{
				if(posDeleteoperadores->str(2)=="OR"){
					operador.push_back('|');
				}else if(posDeleteoperadores->str(2)=="AND") {
					operador.push_back('&');
				}
			}
			eliminar(TablaR,TablaW,ejemplo,info,operador,filas);
			ofstream MetaTabla(_metatabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			numfilas(MetaTabla,filas);
        }
		else if(verificarMetabool){
			sregex_iterator posverificarMeta(consulta.begin(),consulta.end(),verificarMeta);
			sregex_iterator endverificarMeta;
			long long filas,campos;
			vector<columna>info;
			string tabla=posverificarMeta->str(3);
			string metatabla=tabla+"Meta.txt";
			const char *_metatabla=metatabla.c_str();
			ifstream metaTabla(_metatabla);
			recuperarMeta(metaTabla,info,filas,campos);
			cout<<"El numero de filas es: "<<filas<<endl;
			cout<<"El numero de columnas es "<<campos<<endl;
			for(int i=0;i<info.size();i++){
				cout<<"Nombre: "<<info[i].nombre<<endl;
				cout<<"Tipo: "<<info[i].tipo<<endl;
				cout<<"Tamano: "<<info[i].tam<<endl<<endl;
			}
		}
		else if(verificarUpdatebool){
			sregex_iterator posupdatecomparadores0(consulta.begin(),consulta.end(),verificarUpdate);
			sregex_iterator endupdatecomparadores0;
			vector<comp>ejemplo;
			long long filas,campos;
			vector<columna>info;
			string tabla=posupdatecomparadores0->str(5);
			string metatabla=tabla+"Meta.txt";
			const char *_metatabla=metatabla.c_str();
			ifstream metaTabla(_metatabla);
			recuperarMeta(metaTabla,info,filas,campos);
			tabla+=".txt";
			const char* _tabla=tabla.c_str();
			ifstream TablaR(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			ofstream TablaW(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			
			vector<long long>parametro;
			vector<string>valor;

			regex Updatecomparadores("(\\s+)([[:w:]]+)(\\s*)=(\\s*)([[:w:]]+)(\\s*);");
			sregex_iterator posupdatecomparadores(consulta.begin(),consulta.end(),Updatecomparadores);
			sregex_iterator endupdatecomparadores;

			for( ;posupdatecomparadores!=endupdatecomparadores; posupdatecomparadores++)
			{
				long long tam;	
				for(int i = 0; i < info.size(); i++)
				{
					if(info[i].nombre==posupdatecomparadores->str(2)){
						tam=i;
					}
				}
				valor.push_back(posupdatecomparadores->str(5));
				parametro.push_back(tam);
			}

			regex Updatecomparadores2("(\\s+)([[:w:]]+)(\\s*)(=|<|>)(\\s*)([[:w:]]+)(\\s*),");
			sregex_iterator posupdatecomparadores2(consulta.begin(),consulta.end(),Updatecomparadores2);
			sregex_iterator endselectcomparadores2;

			vector<comp>vec;
			for( ;posupdatecomparadores2!=endselectcomparadores2; posupdatecomparadores2++)
			{	
				long long tam;
				for(int i = 0; i < info.size(); i++)
				{
					if(info[i].nombre==posupdatecomparadores2->str(2)){
						tam=i;
					}
				}
				
				if(posupdatecomparadores2->str(4)=="="){
					vec.push_back(comp(tam,"igual",posupdatecomparadores2->str(6)));	
				}else if(posupdatecomparadores2->str(4)==">"){
					vec.push_back(comp(tam,"mayor",posupdatecomparadores2->str(6)));	
				}else if(posupdatecomparadores2->str(4)=="<"){
					vec.push_back(comp(tam,"menor",posupdatecomparadores2->str(6)));
				}
			}


			regex Updateoperadores("(\\s*)(AND|OR)(\\s*)");
			sregex_iterator posupdateoperadores(consulta.begin(),consulta.end(),Updateoperadores);
			sregex_iterator endselectoperadores;
			vector<char>operador;

			for( ;posupdateoperadores!=endselectoperadores; posupdateoperadores++)
			{
				if(posupdateoperadores->str(2)=="OR"){
					operador.push_back('|');
				}else if(posupdateoperadores->str(2)=="AND") {
					operador.push_back('&');
				}
			}
			update(TablaR,TablaW,parametro,valor,vec,info,operador,filas);
			ofstream MetaTabla(_metatabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			numfilas(MetaTabla,filas);
		}
		else if(verificarRandbool){
			sregex_iterator posverificarRand(consulta.begin(),consulta.end(),verificarRand);
			sregex_iterator endverificarRand;
			long long filas,campos;
			vector<columna>info;
			string tabla=posverificarRand->str(3);
			string metatabla=tabla+"Meta.txt";
			const char *_metatabla=metatabla.c_str();
			ifstream metaTabla(_metatabla);
			recuperarMeta(metaTabla,info,filas,campos);
			tabla+=".txt";
			const char* _tabla=tabla.c_str();
			ifstream TablaR(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			ofstream TablaW(_tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			for(long long i=0;i<200000;++i){
				vector<string>ejemplo(info.size());
				for(long long j=0;j<info.size();++j){
					ejemplo[j]=Aleatorio(info[j].tipo);
				}
				insertar(TablaW,ejemplo,info,filas);
			}
			ofstream MetaTabla(_metatabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
			numfilas(MetaTabla,filas);
		}
	}
}