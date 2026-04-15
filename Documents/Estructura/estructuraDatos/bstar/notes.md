Un Arbol B* es una variante del arbol B utilizado en los sistemas de ficheros HFS y Reiser4, que requiere que los nodos no raiz esten por lo menos a 2/3 de ocupacion en lugar de 1/2. 

Para mantener esto, los nodos en lugar de generar inmediatamente un nodo cuando se llenan, comparten sus claves con el nodo adyacente. 

Cuando ambos estan llenos, entonces los dos nodos se transforman en tres. 

Tambien requiere que la clave mas a la izquierda no sea usada nunca.

No se debe confundir con el arbol B+ donde en el los nodos hoja del arbol estan conectados entre si a traves de una lista enlazada, aumentando el coste de insercion para mejorar la eficiencia en la busqueda.

- Todos los nodos guardan datos.
- Los nodos tienen que estar 2/3 llenos. (con el proposito de usar espacio de manera eficiente)
- Cuando un nodo esta lleno, intenta redistribuir con un nodo hermano y si eso no es posible, se crea un split de 3.
- Esta variante es mas eficiente en terminos de uso de espacio y generalmente son mas pequeños en altura que un arbol B.

# Que es un Arbol B*

- Un arbol B* es una variante del arbol B, diseñado para mejorar la eficiencia en la insercion y busqueda en bases de datos y sistemas de archivos.
- Mejora la utilizacion de espacio y reduce la cantidad de veces que un nodo debe ser dividido.

# Estructura de un Arbol B*

- Un arbol B* de orden $m$:
  - Puede tener hasta $m$ hijos por nodo.
  - Requiere que los nodos no raiz esten por lo menos a 2/3 de ocupacion en lugar de 1/2.
  - Cuando un nodo se llena, comparte sus claves con el nodo adyacente.


