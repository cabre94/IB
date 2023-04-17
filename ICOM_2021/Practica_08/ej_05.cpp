int *getPtr(){
    int a = 4;
    return &a; 
}
/*
El problema es que estas retorna la direccion de memoria de una variable local.
Esa variable local se destruye cuando la llamada a la funcion termina, con lo
cual lo que retornas termina apuntando a basura
*/

// Con amor, Cabre.