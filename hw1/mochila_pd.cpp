/*
** Universidade Federal do Rio de Janeiro
** Programa de Engenharia de Sistemas e Computa√√o
** Author: Guilherme Iecker Ricardo
*/

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void sort_array(double*, int*, int);

int main(int argc, char** argv) {
	ifstream in;
    	in.open ("mochila.in");
	if(!in.is_open()) {
		cout << "ERROR: could not open file mochila_in" << endl;
		return 0;
	}

	double b, current_size, z;
	int n, index;
	double *c, *a, *custo_beneficio, *x;
	int *indices;

	in >> n >> b;
	
	if(n < 4) {
		cout << "ERROR: not enough elements (n must be greater than 3)" << endl;
		return 0;
	}

	if(n > 99999) {
		cout << "ERROR: too many elements (n must be less than 100000)" << endl;
		return 0;
	}

	c = new double[n];
	a = new double[n];
	
	for(int i = 0; i < n; i++) in >> c[i];
	for(int i = 0; i < n; i++) in >> a[i];

	in.close();

	custo_beneficio = new double[n];
	indices = new int[n];
        for(int i = 0; i < n; i++) {
		if (c[i] <= 0) {
			cout << "ERROR: invalid objective function coefficient" << endl;
			return 0;
		}
		if ((a[i] <= 0) || (a[i] > b)) {
			cout << "ERROR: invalid constraint coefficient" << endl;
			return 0;
		}
		custo_beneficio[i] = c[i] / a[i];
		indices[i] = i;
	}

	sort_array(custo_beneficio, indices, n);
	
	x = new double[n];
	//memset(x, 0.0, sizeof(x));
	current_size = b;
	z = 0.0;
	for (int i = 0; i < n; i++) {
		index = indices[i];
		if (a[index] <= current_size) {
			x[index] = 1.0;
			current_size = current_size - a[index];
			z = z + c[index];
		} else {
			x[index] = current_size / a[index];
			z = z + x[index] * c[index];
			break;
		}
	}

	ofstream out("mochila_frac.out");
	if(!out.is_open()) {
                cout << "ERROR: could not open file mochila_in" << endl;
                return 0;
        }

	out << z << endl;
	for (int i = 0; i < n; i++) out << x[i] << "\t";
	out << endl;

	return 0;
}

void sort_array(double* v, int* u, int n) {
	//bubble sorting...
	double aux_value;
	int aux_index;
	int k = n - 1;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < k; j++) {
			if(v[j] < v[j+1]) {
				aux_value = v[j];
				v[j] = v[j+1];
				v[j+1] = aux_value;
				aux_index = u[j];
				u[j] = u[j+1];
				u[j+1] = aux_index;
			}
		}
		k--;
	}
}
