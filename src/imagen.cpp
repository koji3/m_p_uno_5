#include"imagen.h"
#include"pgm.h"
#include"byte.h"
#include<iostream>
#include <cstring> 

using namespace std;

Imagen::Imagen(){
    ncolumnas=0;
    nfilas=0;
    datos=0;
}

Imagen::Imagen(int filas, int columnas){
    crear(filas,columnas);
}

Imagen::~Imagen(){
	if(datos!=0){ delete [] datos; }
	ncolumnas=0;
	nfilas=0;
}

int Imagen::filas(){
    return nfilas;
}

int Imagen::columnas(){
    return ncolumnas;
}

void Imagen::set(int y, int x, byte v){
    datos[(y*ncolumnas)+x]=v;
}

byte Imagen::get(int y, int x){
    return datos[(y*ncolumnas)+x];
}

void Imagen::setPos(int i, byte v){
    datos[i]=v;
}

byte Imagen::getPos(int i){
    return datos[i];
}

void Imagen::crear(int filas, int columnas){
    this->nfilas = filas;
    this->ncolumnas = columnas;
    cerr << "Creando" <<endl;
    if(datos!=0){ delete [] datos; }
    datos=new byte[filas*columnas];
    for(int i=0;i<filas*columnas;i++){ 
        datos[i] = 0;
    }
}

 bool Imagen::leerImagen(const char nombreFichero[]){
     TipoImagen tipo = infoPGM(nombreFichero,this->nfilas,this->ncolumnas);
     if(infoPGM(nombreFichero,this->nfilas,this->ncolumnas)==IMG_PGM_BINARIO){
         leerPGMBinario(nombreFichero,datos,this->nfilas,this->ncolumnas);
         return true;
     }else if(infoPGM(nombreFichero,this->nfilas,this->ncolumnas)==IMG_PGM_TEXTO){
         leerPGMTexto(nombreFichero,datos,this->nfilas,this->ncolumnas);
         return true;
     }
     else
         return false;
 }
 
bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario){
	if(esBinario){
    	return escribirPGMBinario(nombreFichero, datos, nfilas, ncolumnas);
    }else{
    	return escribirPGMTexto(nombreFichero, datos, nfilas, ncolumnas);
    }
}

Imagen Imagen::plano ( int k ){
    Imagen aux(nfilas,ncolumnas);
    for(int y=0; y<nfilas*ncolumnas; y++){
    	bytaso::byte nuevo;
    	bytaso::apagar(nuevo);
        if(bytaso::get(getPos(y),k)){
            bytaso::on(nuevo,7);
            
        }
        aux.setPos(y,nuevo);

    }
    return aux;
}

bool Imagen::aArteASCII(const char grises[], char arteASCII[], int maxlong){
	bool exito=false;
	if(ncolumnas*nfilas < maxlong){
		int ncaracteres=strlen(grises);
		int indice=0;
		for(int y=0; y<nfilas; y++){
			for(int x=0; x<ncolumnas; x++){
				arteASCII[indice]=grises[(datos[(y*ncolumnas)+x]*ncaracteres)/256];
				indice++;
			}
			arteASCII[indice]='\n';
			indice++;
		}
		exito=true;
	}
	
	return exito;
}

