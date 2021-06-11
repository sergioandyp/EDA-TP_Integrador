#ifndef _FULL_COMPLETE_TREE_H_
#define _FULL_COMPLETE_TREE_H_

#include <cmath>
#include <vector>

// Clase para implementar un arbol binario lleno y completo que se puede
// acceder a tráves de la altura e índice de un nodo.
// Se crea a partir del número de hojas, y su tamaño no se puede modificar
// Se accede a una referencia a los nodos a partir del
// operador [h][i] donde se indica altura h e indice i
template <typename T> class FullCompleteTree {
public:

	// Crea un arbol vacío
	FullCompleteTree() : height(0), tree()
	{
	}

	// Crea un arbol completo y lleno con nOfLeafs hojas y todos sus nodos con valor defaultVal
	// Si nOfLeafs no es un número par, se toma el numero par inmediatamente superior
	FullCompleteTree(unsigned int nOfLeafs, T defaultVal = T()) :
		height((unsigned int)ceil(log2(nOfLeafs))), tree(height+1)
	{
		if (height > 0) {
			for (unsigned int i = 0; i < height; i++) {
				tree[i].resize((unsigned int)exp2(i), defaultVal);
			}

			tree[height].resize(nOfLeafs, defaultVal);
		}
	}

	// Devuelve la altura total del arbol
	unsigned int getHeight() {
		return height;
	}


	// Esta clase se usa para sobrecargar el operador[] y poder acceder y modificar nodos a través de tree[][]
	class TreeRow {
	public:
		TreeRow(FullCompleteTree& tree_, unsigned int height_) : row(tree_.tree[height_])
		{
		}

		// Devuelve la cantidad de nodos a profundidad height_
		unsigned int size() {
			return row.size();
		}

		T& operator[](unsigned int index) {
			return row[index];
		}

	private:
		std::vector<T>& row;
	};

	// Devuelve un TreeRow, que es un vector de nodos a la altura height que solo se puede acceder.
	// De esta forma, se puede obtener una referencia a un nodo a altura h y posicion i mediante: tree[h][i]
	// Si se intenta acceder fuera de rango, se comporta al igual que un std::vector
	TreeRow operator[](unsigned int height) {
		return TreeRow(*this, height);
	}

private:
	// Altura del arbol. Es fija ya que no se pueden agregar ni eliminar nodos.
	unsigned int height;	// Declarar este primero para poder usarlo para construir tree

	// Estructura del arbol como vector de pisos
	// Donde cada piso es un vector de nodos que estan a la misma altura
	std::vector<std::vector<T>> tree;
};

#endif //_FULL_COMPLETE_TREE_H_