#include "FunGestor.h"

void recuperarMeta(ifstream & f,vector<columna>&vec,long long &filas,long long &campos){
	f.seekg(0);
	char buffer[block];
	f.read(buffer,block);
	filas=stringNumber(limpiar((char*)buffer));
	f.read(buffer,block);
	campos=stringNumber(limpiar((char*)buffer));
	for(long long i=0;i<campos;++i){
		f.read(buffer,block);
		string s=limpiar((char *)buffer);
		vector<string>dato;
		parsear(s,dato,'/');
		vec.push_back(columna(dato[0],dato[1],stringNumber(dato[2])));
	}
}
void recuperarMeta(ifstream & f,vector<columna>&vec,vector<indice>&ind,long long &filas,long long &campos,long long &indices){
	f.seekg(0);
	char buffer[block];
	f.read(buffer,block);
	filas=stringNumber(limpiar((char*)buffer));
	f.read(buffer,block);
	campos=stringNumber(limpiar((char*)buffer));
	for(long long i=0;i<campos;++i){
		f.read(buffer,block);
		string s=limpiar((char *)buffer);
		vector<string>dato;
		parsear(s,dato,'/');
		vec.push_back(columna(dato[0],dato[1],stringNumber(dato[2])));
	}
	f.read(buffer,block);
	indices=stringNumber(limpiar((char*)buffer));
	for(long long i=0;i<indices;++i){
		f.read(buffer,block);
		string s=limpiar((char *)buffer);
		vector<string>dato;
		parsear(s,dato,'/');
		ind.push_back(indice(dato[0],stringNumber(dato[1])));
	}
}

void createTable(string nombre,vector<columna>&vec){
	string archivo=nombre+"Meta.txt";
	const char *Arc=archivo.c_str();
	ofstream metadata(Arc);
	archivo=nombre+".txt";
	const char *arc=archivo.c_str();
	ofstream tabla(arc);
	long long j=0;
	char *buffer[block];
	renovar((char*)buffer);
	insertarstr((char*)buffer,numberString(j),0);
	metadata.write((char*)buffer,block);
	j=vec.size();
	renovar((char*)buffer);
	insertarstr((char*)buffer,numberString(j),0);
	metadata.write((char*)buffer,block);
	for(long long i=0;i<vec.size();++i){
		renovar((char*)buffer);
		string q=vec[i].nombre+"/";
		q+=vec[i].tipo+"/";
		q+=numberString(vec[i].tam)+"/";
		insertarstr((char*)buffer,q,0);
		metadata.write((char*)buffer,block);
	}
	metadata.close();
}

void createTable(string nombre,vector<columna>&vec,vector<indice>&ind){
    string archivo=nombre+"Meta.txt";
    const char *Arc=archivo.c_str();
    ofstream metadata(Arc);
    archivo=nombre+".txt";
    const char *arc=archivo.c_str();
    ofstream tabla(arc);
    long long j=0;
    char *buffer[block];
    renovar((char*)buffer);
    insertarstr((char*)buffer,numberString(j),0);
    metadata.write((char*)buffer,block);
    j=vec.size();
    renovar((char*)buffer);
    insertarstr((char*)buffer,numberString(j),0);
    metadata.write((char*)buffer,block);
    for(long long i=0;i<vec.size();++i){
        renovar((char*)buffer);
        string q=vec[i].nombre+"/";
        q+=vec[i].tipo+"/";
        q+=numberString(vec[i].tam)+"/";
        insertarstr((char*)buffer,q,0);
        metadata.write((char*)buffer,block);
    }
    j=ind.size();
    renovar((char*)buffer);
    insertarstr((char*)buffer,numberString(j),0);
    metadata.write((char*)buffer,block);
    for(long long i=0;i<ind.size();++i){
        renovar((char*)buffer);
        string q=ind[i].nombre+"/";
        q+=numberString(ind[i].tam)+"/";
        insertarstr((char*)buffer,q,0);
        metadata.write((char*)buffer,block);
    }
    for(long long i=0;i<ind.size();++i) {
    	string Hash=nombre+ind[i].nombre;
    	const char *_Hash=Hash.c_str();
		mkdir(_Hash);
		Hash+= '/' ;
		for(long long j=0;j<ind[i].tam;++j){
			string HashArchive=Hash+numberString(j);
			createTable(HashArchive,vec);
		}
	}
    metadata.close();
}

void numfilas(ofstream &f,long long &filas){
	char buffer[block];
	renovar(buffer);
	insertarstr(buffer,numberString(filas),0);
	f.seekp(0);
	f.write(buffer,block);
}

void insertar(ofstream & f,vector<string>&vec,vector<columna> &info,long long &filas){
	f.seekp(0);
	char buffer[block];
	renovar((char*)buffer);
	long long j=0;
	for(long long i=0;i<vec.size();++i){
		string p(info[i].tam,' ');
		insertarstr(p,vec[i],0);
		insertarstr((char*)buffer,p,j);
		j+=info[i].tam;
	}
	f.seekp(filas*block);
	++filas;
	f.write(buffer,block);
}
void insertar(string nombre,vector<string>&valores){
	string p=nombre+"Meta.txt";
	ifstream InMeta (p);
	ofstream OutMeta (p, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	vector<columna>columnas;
	vector<indice>ind;
	long long filas=0,campos=0,indices=0;
	recuperarMeta(InMeta,columnas,ind,filas,campos,indices);
	string y=nombre+".txt";
	ofstream TWrite(y, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	insertar(TWrite,valores,columnas,filas);
	numfilas(OutMeta,filas);
	for(long long i=0;i<ind.size();i++){
		long long x=0;
		for(long long j=0;j<columnas.size();j++)
			if(ind[i].nombre==columnas[j].nombre)
				x=j;
		string hash=numberString(((stringNumber(valores[x])%ind[i].tam)+ind[i].tam)%ind[i].tam);
		string hashing=nombre;
		hashing+=columnas[x].nombre;
		hashing+="/";
		hashing+=hash;
		string META=hashing;
		META+="Meta.txt";
		hashing+=".txt";
		vector<columna>col;
		long long filas1=0,campos1=0;
		ifstream InMetaindi(META);
		ofstream OutMetaindi(META, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
		recuperarMeta(InMetaindi,col,filas1,campos1);
		ofstream Hash(hashing, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
		insertar(Hash,valores,col,filas1);
		numfilas(OutMetaindi,filas1);
		InMetaindi.close();
		OutMetaindi.close();
		Hash.close();
	}
	InMeta.close();
	OutMeta.close();
	TWrite.close();
}

void eliminar(ifstream &g,ofstream & f, vector<comp>&vec,vector<columna> & info,vector<char>&operador, long long &filas){
	vector<long long>begin(vec.size());
	vector<long long>end(vec.size());
	for(long long i=0;i<vec.size();++i){
		long long x=0;
		for(long long j=0;j<vec[i].colum;++j){
			x+=info[j].tam;
		}
		begin[i]=x;
		end[i]=x+info[vec[i].colum].tam;
	}
	long long x=0;
	char buffer[block];
	long long tmp=filas;
	for(long long i=0;i<tmp;++i){
		g.seekg(x*block);
		g.read(buffer,block);
		bool b=1;
		for(long long j=0;j<vec.size();++j){
			bool cond=0;
			string p=extraer(buffer,begin[j],end[j]);
			limpiar(p);
			if(vec[j].op=="igual"){
				cond=(p==vec[j].valor);
			}
			else if(vec[j].op=="menor"){
				if(info[vec[j].colum].tipo=="varchar"){
					cond=(p<vec[j].valor);
				}
				else{
					cond=(stringNumber(p)<stringNumber(vec[j].valor));
				}
			}
			else{
				if(info[vec[j].colum].tipo=="varchar"){
					cond=(p>vec[j].valor);
				}
				else{
					cond=(stringNumber(p)>stringNumber(vec[j].valor));
				}
			}
			if(j!=0){
				if(operador[j-1] == '&'){
					b = b && cond;
				}
				else if(operador[j-1]=='|'){
					b = b || cond;
				}
			}
			else{
				b=cond;
			}
		}
		if(b){
			g.seekg((filas-1)*block);
			g.read(buffer,block);
			f.seekp(x*block);
			f.write(buffer,block);
			renovar(buffer);
			f.seekp((filas-1)*block);
			f.write(buffer,block);
			--filas;
		}
		else{
			++x;
		}
	}
}

void eliminar(string nombre,vector<comp>&vec,vector<char>&operador, string IND,string valor){
	vector<columna>columnas;
	vector<indice>ind;
	long long filas=0,campos=0,indices=0;
	string meta=nombre+"Meta.txt";
	ifstream Meta(meta);
	ofstream OutMeta(meta,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	recuperarMeta(Meta,columnas,ind,filas,campos,indices);
	string tab=nombre+".txt";
	ifstream TR(tab);
	ofstream TW(tab,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	eliminar(TR,TW,vec,columnas,operador,filas);
	long long x=0;
	for(long long i=0;i<ind.size();i++)
		if(ind[i].nombre==IND)
			x=i;
	string tabla=nombre;
	tabla+=IND;
	tabla+="/";
	tabla+=numberString(((stringNumber(valor)%ind[x].tam)+ind[x].tam)%ind[x].tam);
	vector<columna>col;
	long long filas1=0,campos1=0;
	string metas=tabla+"Meta.txt";
	ifstream MetaIndi(metas);
	ofstream MetaOutIndi(metas,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	recuperarMeta(MetaIndi,col,filas1,campos1);
	tabla+=".txt";
	ifstream TRead(tabla);
	ofstream Twrite(tabla,std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	eliminar(TRead,Twrite,vec,col,operador,filas1);
	numfilas(MetaOutIndi,filas1);
	numfilas(OutMeta,filas);
}
void select(ifstream &g,vector<long long>&parametro,vector<comp>&vec,vector<columna> & info,vector<char>&operador, long long filas){
	g.seekg(0);
	vector<long long>begin(vec.size());
	vector<long long>end(vec.size());
	for(long long i=0;i<vec.size();++i){
		long long x=0;
		for(long long j=0;j<vec[i].colum;++j){
			x+=info[j].tam;
		}
		begin[i]=x;
		end[i]=x+info[vec[i].colum].tam;
	}
	long long x=0;
	char buffer[block];
	long long tmp=filas;
	
	vector<long long>comienzo(parametro.size());
	vector<long long>fin(parametro.size());
	for(long long i=0;i<parametro.size();++i){
		long long x=0;
		for(long long j=0;j<parametro[i];++j){
			x+=info[j].tam;
		}
		comienzo[i]=x;
		fin[i]=x+info[parametro[i]].tam;
	}
	int l=0;
	cout<<"#";
	for(long long i=0;i<parametro.size();++i){
		cout<<" "<<info[parametro[i]].nombre;
	}cout<<endl;
	for(long long i=0;i<tmp;++i){
		g.seekg(x*block);
		g.read(buffer,block);
		bool b=1;
		for(long long j=0;j<vec.size();++j){
			bool cond=0;
			string p=extraer(buffer,begin[j],end[j]);
			limpiar(p);
			if(vec[j].op=="igual"){
				cond=(p==vec[j].valor);
			}
			else if(vec[j].op=="menor"){
				if(info[vec[j].colum].tipo=="varchar"){
					cond=(p<vec[j].valor);
				}
				else{
					cond=(stringNumber(p)<stringNumber(vec[j].valor));
				}
			}
			else{
				if(info[vec[j].colum].tipo=="varchar"){
					cond=(p>vec[j].valor);
				}
				else{
					cond=(stringNumber(p)>stringNumber(vec[j].valor));
				}
			}
			if(j!=0){
				if(operador[j-1] == '&'){
					b = b && cond;
				}
				else if(operador[j-1]=='|'){
					b = b || cond;
				}
			}
			else{
				b=cond;
			}
		}
		if(b){
			cout<<++l;
			for(long long j=0;j<parametro.size();++j){
				string p=extraer(buffer,comienzo[j],fin[j]);
				limpiar(p);
				cout<<" "<<p;
			}cout<<endl;
		}
		++x;
	}
}

void select(string nombre,vector<long long>&parametro,vector<comp>&vec,vector<char>&operador, string IND,string valor){
	vector<columna>columnas;
	vector<indice>ind;
	long long filas=0,campos=0,indices=0;
	string meta=nombre+"Meta.txt";
	ifstream Meta(meta);
	recuperarMeta(Meta,columnas,ind,filas,campos,indices);
	long long x=0;
	for(long long i=0;i<ind.size();i++){
		if(ind[i].nombre==IND)
			x=i;
	}
	string tabla=nombre;
	tabla+=IND;
	tabla+="/";
	tabla+=numberString(((stringNumber(valor)%ind[x].tam)+ind[x].tam)%ind[x].tam);
	vector<columna>col;
	long long filas1=0,campos1=0;
	string metas=tabla+"Meta.txt";
	ifstream MetaIndi(metas);
	recuperarMeta(MetaIndi,col,filas1,campos1);
	tabla+=".txt";
	ifstream TRead(tabla);
	select(TRead,parametro,vec,col,operador,filas1);
}

void update(ifstream &g,ofstream &f,vector<long long>&parametro,vector<string>&valor,vector<comp>&vec,vector<columna> & info,vector<char>&operador, long long filas){
	vector<long long>begin(vec.size());
	vector<long long>end(vec.size());
	for(long long i=0;i<vec.size();++i){
		long long x=0;
		for(long long j=0;j<vec[i].colum;++j){
			x+=info[j].tam;
		}
		begin[i]=x;
		end[i]=x+info[vec[i].colum].tam;
	}
	long long x=0;
	char buffer[block];
	long long tmp=filas;
	
	vector<long long>comienzo(parametro.size());
	for(long long i=0;i<parametro.size();++i){
		long long x=0;
		for(long long j=0;j<parametro[i];++j){
			x+=info[j].tam;
		}
		comienzo[i]=x;
	}
	
	for(long long i=0;i<tmp;++i){
		g.seekg(x*block);
		g.read(buffer,block);
		bool b=1;
		for(long long j=0;j<vec.size();++j){
			bool cond=0;
			string p=extraer(buffer,begin[j],end[j]);
			limpiar(p);
			if(vec[j].op=="igual"){
				cond=(p==vec[j].valor);
			}
			else if(vec[j].op=="menor"){
				if(info[vec[j].colum].tipo=="varchar"){
					cond=(p<vec[j].valor);
				}
				else{
					cond=(stringNumber(p)<stringNumber(vec[j].valor));
				}
			}
			else{
				if(info[vec[j].colum].tipo=="varchar"){
					cond=(p>vec[j].valor);
				}
				else{
					cond=(stringNumber(p)>stringNumber(vec[j].valor));
				}
			}
			if(j!=0){
				if(operador[j-1] == '&'){
					b = b && cond;
				}
				else if(operador[j-1]=='|'){
					b = b || cond;
				}
			}
			else{
				b=cond;
			}
		}
		if(b){
			for(long long j=0;j<parametro.size();++j){
				string p(info[parametro[j]].tam,' ');
				insertarstr(p,valor[j],0);
				insertarstr(buffer,p,comienzo[j]);
				f.seekp(x*block);
				f.write(buffer,block);
			}
		}
		++x;
	}
}


