#include <iostream>
#include <string>

using namespace std;

void testTree();

int main() {


	testTree();

	return 0;
}

#include "FullCompleteTree.h"
void testTree() {

	unsigned int n;
	cin >> n;

	FullCompleteTree<string> tree(n, "A");

	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			
		}
	}

}