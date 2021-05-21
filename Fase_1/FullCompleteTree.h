#ifndef _FULL_COMPLETE_TREE_H_
#define _FULL_COMPLETE_TREE_H_

#include <cmath>
#include <vector>

// Altura: ceil(log2(n))
// Nodos totales: 2^ceil(log_2(n))-1+n
// Nodos internos: 2^ceil(log_2(n))-1
// Nodos a altura d (excepto d = heigth): 2^d

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
		height(ceil(log2(nOfLeafs))), tree(height)
	{

		for (unsigned int i = 0; i < height - 1; i++) {
			tree[i].resize(exp2(i), defaultVal);
		}

		tree[height - 1].resize(nOfLeafs);

	}

	// Esta clase se usa para sobrecargar el operador[] y poder acceder y modificar nodos a través de tree[][]
	class TreeRow {
	public:
		TreeRow(FullCompleteTree& tree_, unsigned int height_) : row(tree_.tree[height_])
		{
		}

		T operator[](unsigned int index) {
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
	// Estructura del arbol como vector de pisos
	// Donde cada piso es un vector de nodos que estan a la misma altura
	std::vector<std::vector<T>> tree;

	// Altura del arbol. Es fija ya que no se pueden agregar ni eliminar nodos.
	unsigned int height;

};

#endif //_FULL_COMPLETE_TREE_H_