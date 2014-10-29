#include "Volumen.h"
#include <string>
#include "cstring"

#include <algorithm>

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
    {
        s[i++] = n % 10 + '0';
    }
    while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


vector<Imagen2D>* Volumen::getImagenes()
{
    return imagenes;
}
Volumen::Volumen()
{

}

Volumen::Volumen(char *nombreBase, int total)
{
    imagenes= new  vector<Imagen2D>(total);
    setTamanio(total);
    int total1=0;
    for(int i=1; i<=total; i++)
    {


        if(i<10)
        {

            char* variable= new char[100];
            itoa(i,variable);

            char* nombreCompleto= new char[100];
            strcpy(nombreCompleto,"");
            strcat(nombreCompleto, nombreBase);
            strcat(nombreCompleto, "0");
            strcat(nombreCompleto, variable);
            char *copia= new char[100];
            strcpy(copia,nombreCompleto);
            strcat(copia,".pgm");
            fstream archivo(copia);
            if(archivo)
            {
                archivo.close();

                Imagen2D agrego(nombreCompleto);
                (*(imagenes))[i-1]=agrego;
                total1++;
            }

        }
        else
        {
            char* variable= new char[100];

            itoa(i,variable);
            char* nombreCompleto= new char[100];
            strcpy(nombreCompleto,"");
            strcat(nombreCompleto, nombreBase);
            strcat(nombreCompleto, variable);


            // ahh ya se jumm
            char *copia= new char[100];
            strcpy(copia,nombreCompleto);
            strcat(copia,".pgm");
            fstream archivo(copia);
            if(archivo)
            {
                archivo.close();

                Imagen2D agrego(nombreCompleto);
                (*(imagenes))[i-1]=agrego;
                total1++;
            }


        }


    }
    setTamanio(total1);
}

void inicializarVector(vector< vector<int > >* promedio)
{
    for(int i=0; i<(*(promedio)).size(); i++)
    {
        for(int j=0; j<(*(promedio))[i].size(); j++)
        {

            (*(promedio))[i][j]=0;
        }
    }
}
void promedioVector(vector< vector<int > >* promedio,int cant)
{
    int  temp;
    for(int i=0; i<(*(promedio)).size(); i++)
    {
        for(int j=0; j<(*(promedio))[i].size(); j++)
        {

            temp=(*(promedio))[i][j]/cant;
            (*(promedio))[i][j]=temp;
        }
    }
}


Imagen2D* Volumen::proyeccionZPromedio()
{

    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* promedio= new vector< vector<int > > (ima.getFila(), vector<int> (ima.getColumna()));
    inicializarVector(promedio);
    for(int k=0; k<tamanio; k++)
    {
        Imagen2D temporal=(*(imagenes))[k];
        for(int i=0; i<ima.getFila(); i++)
        {
            vector<int> temporal2=(*(temporal.getImagen()))[i];
            for(int j=0; j<ima.getColumna(); j++)
            {
                (*(promedio))[i][j]+=temporal2[j];
            }
        }
    }
    promedioVector(promedio,tamanio);
    proyeccion->setImagen(promedio);
    proyeccion->setFila(ima.getFila());
    proyeccion->setColumna(ima.getColumna());
    return (proyeccion);

}



int Volumen::getTamanio()
{
    return tamanio;
}
void Volumen::setTamanio(int tam)
{
    tamanio=tam;
}



Imagen2D* Volumen::proyeccionYPromedio()
{

    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* promedio= new vector< vector<int > > ((tamanio), vector<int> (ima.getFila()));
    inicializarVector(promedio);
    for(int j=0; j<ima.getColumna(); j++)
    {


        for(int i=0; i<ima.getFila(); i++)
        {





            for(int k=0; k<tamanio; k++)
            {

                (*(promedio))[k][i]+=((*(*(imagenes))[k].getImagen())[i][j]);

            }
        }

    }
    promedioVector(promedio,ima.getColumna());
    proyeccion->setImagen(promedio);
    proyeccion->setFila(ima.getFila());
    proyeccion->setColumna(tamanio);

    return (proyeccion);

}


Imagen2D* Volumen::proyeccionXPromedio()
{
    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* promedio= new vector< vector<int > > ((tamanio), vector<int> (ima.getColumna()));
    inicializarVector(promedio);

    for(int i=0; i<ima.getFila(); i++)
    {

        for(int j=0; j<ima.getColumna(); j++)
        {


            for(int k=0; k<tamanio; k++)
            {

                (*(promedio))[k][j]+=((*(*(imagenes))[k].getImagen())[i][j]);


            }
        }
    }
    promedioVector(promedio,ima.getFila());
    proyeccion->setImagen(promedio);
    proyeccion->setFila(ima.getColumna());
    proyeccion->setColumna(tamanio);
    return (proyeccion);

}

Imagen2D* Volumen:: proyeccionZMediana()
{

    Imagen2D* proyeccion= new Imagen2D();

    Imagen2D ima=(*(imagenes))[0];

    vector< vector<int > >* mediana= new vector< vector<int > > (ima.getColumna(), vector<int> (ima.getFila()));


    inicializarVector(mediana);


    for(int i=0; i<ima.getFila(); i++)
    {

        for(int j=0; j<ima.getColumna(); j++)
        {

            vector<int> *temp=new vector<int>(tamanio);
            for(int k=0; k<tamanio; k++)
            {
                (*(temp))[k]=((*(*(imagenes))[k].getImagen())[i][j]);
            }

            sort ((*(temp)).begin(),(*(temp)).end());

            if(tamanio%2!=0)
            {

                (*(mediana))[j][i]=(*(temp))[tamanio/2];
            }
            else
            {

                (*(mediana))[j][i]=  ((*(temp))[tamanio/2]+(*(temp))[(tamanio/2)-1])/2;
            }

            delete temp;

        }
    }

    proyeccion->setImagen(mediana);
    proyeccion->setFila(ima.getFila());
    proyeccion->setColumna(ima.getColumna());
    return (proyeccion);

}

Imagen2D* Volumen:: proyeccionYMediana()
{
    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* mediana= new vector< vector<int > > (tamanio,vector<int> (ima.getFila()));
    inicializarVector(mediana);

    for(int i=0; i<ima.getFila(); i++)
    {

        for(int k=0; k<tamanio; k++)
        {

            vector<int> temp(ima.getColumna());
            for(int j=0; j<ima.getColumna(); j++)
            {

                temp[j]=((*(*(imagenes))[k].getImagen())[i][j]);


            }
            sort (temp.begin(),temp.end());
            if(ima.getColumna()%2!=0)
            {
                (*(mediana))[k][i]=temp[ima.getColumna()/2];
            }
            else
            {
                (*(mediana))[k][i]=(temp[ima.getColumna()/2]+temp[(ima.getColumna()/2)-1])/2;
            }

        }
    }

    proyeccion->setImagen(mediana);
    proyeccion->setFila(ima.getFila());
    proyeccion->setColumna(tamanio);

    return (proyeccion);

}


Imagen2D* Volumen:: proyeccionXMediana()
{
    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* mediana= new vector< vector<int > > ((tamanio), vector<int> (ima.getColumna()));
    inicializarVector(mediana);

    for(int j=0; j<ima.getColumna(); j++)
    {

        for(int k=0; k<tamanio; k++)
        {

            vector<int> temp(ima.getFila());
            for(int i=0; i<ima.getFila(); i++)
            {

                temp[i]=((*(*(imagenes))[k].getImagen())[i][j]);


            }
            sort (temp.begin(),temp.end());
            if(ima.getFila()%2!=0)
            {
                (*(mediana))[k][j]=temp[ima.getFila()/2];
            }
            else
            {
                (*(mediana))[k][j]=(temp[ima.getFila()/2]+temp[(ima.getFila()/2)-1])/2;
            }
        }
    }

    proyeccion->setImagen(mediana);
    proyeccion->setFila(ima.getColumna());
    proyeccion->setColumna(tamanio);
    return (proyeccion);

}

Imagen2D* Volumen:: proyeccionZMaximo()
{
    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* mediana= new vector< vector<int > > (ima.getFila(), vector<int> (ima.getColumna()));
    inicializarVector(mediana);

    for(int i=0; i<ima.getFila(); i++)
    {

        for(int j=0; j<ima.getColumna(); j++)
        {

            vector<int> temp(tamanio);
            for(int k=0; k<tamanio; k++)
            {

                temp[k]=((*(*(imagenes))[k].getImagen())[i][j]);

            }
            sort (temp.begin(),temp.end());
            (*(mediana))[i][j]=temp[tamanio-1];
        }
    }

    proyeccion->setImagen(mediana);
    proyeccion->setFila(ima.getFila());
    proyeccion->setColumna(ima.getColumna());
    return (proyeccion);


}

Imagen2D* Volumen:: proyeccionYMaximo()
{
    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* mediana= new vector< vector<int > > ( (tamanio), vector<int>(ima.getFila()));
    inicializarVector(mediana);

    for(int i=0; i<ima.getFila(); i++)
    {

        for(int k=0; k<tamanio; k++)
        {

            vector<int> temp(ima.getColumna());
            for(int j=0; j<ima.getColumna(); j++)
            {

                temp[j]=((*(*(imagenes))[k].getImagen())[i][j]);


            }
            sort (temp.begin(),temp.end());
            (*(mediana))[k][i]=temp[ima.getColumna()-1];
        }
    }

    proyeccion->setImagen(mediana);
    proyeccion->setFila(ima.getFila());
    proyeccion->setColumna(tamanio);
    return (proyeccion);

}

Imagen2D* Volumen:: proyeccionXMaximo()
{
    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* mediana= new vector< vector<int > > ( (tamanio), vector<int>(ima.getColumna()));
    inicializarVector(mediana);

    for(int j=0; j<ima.getColumna(); j++)
    {

        for(int k=0; k<tamanio; k++)
        {

            vector<int> temp(ima.getFila());
            for(int i=0; i<ima.getFila(); i++)
            {

                temp[i]=((*(*(imagenes))[k].getImagen())[i][j]);


            }
            sort (temp.begin(),temp.end());
            (*(mediana))[k][j]=temp[ima.getFila()-1];
        }
    }

    proyeccion->setImagen(mediana);
    proyeccion->setFila(ima.getColumna());
    proyeccion->setColumna(tamanio);
    return (proyeccion);

}

Imagen2D* Volumen:: proyeccionZMinimo()
{
    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* mediana= new vector< vector<int > > (ima.getFila(), vector<int> (ima.getColumna()));
    inicializarVector(mediana);

    for(int i=0; i<ima.getFila(); i++)
    {

        for(int j=0; j<ima.getColumna(); j++)
        {

            vector<int> temp(tamanio);
            for(int k=0; k<tamanio; k++)
            {

                temp[k]=((*(*(imagenes))[k].getImagen())[i][j]);

            }
            sort (temp.begin(),temp.end());
            (*(mediana))[i][j]=temp[0];
        }
    }

    proyeccion->setImagen(mediana);
    proyeccion->setFila(ima.getFila());
    proyeccion->setColumna(ima.getColumna());
    return (proyeccion);


}

Imagen2D* Volumen:: proyeccionYMinimo()
{
    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* mediana= new vector< vector<int > > ((tamanio), vector<int> (ima.getFila()));
    inicializarVector(mediana);

    for(int i=0; i<ima.getFila(); i++)
    {

        for(int k=0; k<tamanio; k++)
        {

            vector<int> temp(ima.getColumna());
            for(int j=0; j<ima.getColumna(); j++)
            {

                temp[j]=((*(*(imagenes))[k].getImagen())[i][j]);


            }
            sort (temp.begin(),temp.end());
            (*(mediana))[k][i]=temp[0];
        }
    }

    proyeccion->setImagen(mediana);
    proyeccion->setFila(ima.getFila());
    proyeccion->setColumna(tamanio);
    return (proyeccion);

}

Imagen2D* Volumen:: proyeccionXMinimo()
{
    Imagen2D* proyeccion= new Imagen2D();
    Imagen2D ima=(*(imagenes))[0];
    vector< vector<int > >* mediana= new vector< vector<int > > ((tamanio), vector<int> (ima.getColumna()) );
    inicializarVector(mediana);

    for(int j=0; j<ima.getColumna(); j++)
    {

        for(int k=0; k<tamanio; k++)
        {

            vector<int> temp(ima.getFila());
            for(int i=0; i<ima.getFila(); i++)
            {

                temp[i]=((*(*(imagenes))[k].getImagen())[i][j]);


            }
            sort (temp.begin(),temp.end());
            (*(mediana))[k][j]=temp[0];
        }
    }

    proyeccion->setImagen(mediana);
    proyeccion->setFila(ima.getColumna());
    proyeccion->setColumna(tamanio);
    return (proyeccion);

}

