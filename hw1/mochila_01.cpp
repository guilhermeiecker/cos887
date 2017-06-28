/*
** Universidade Federal do Rio de Janeiro
** Programa de Engenharia de Sistemas e Computação
** Author: Guilherme Iecker Ricardo
*/

#include <iostream>
#include <fstream>
#include "gurobi_c++.h"

using namespace std;

int main(int argc, char** argv) {
	ifstream in("mochila.in");
	if(!in.is_open()) {
		cout << "ERROR: could not open file mochila_in" << endl;
		return 0;
	}

	double b;
	int n;

	in >> n >> b;
	
	if(n < 4) {
		cout << "ERROR: not enough elements (n must be greater than 3)" << endl;
		in.close();
		return 0;
	}

	if(n > 99999) {
		cout << "ERROR: too many elements (n must be less than 100000)" << endl;
		in.close();
		return 0;
	}

	double* c = new double[n];
	double* a = new double[n];

	for (int i = 0; i < n; i++) {
		in >> c[i];
		if (c[i] <= 0) {
			cout << "ERROR: invalid objective function coefficient" << endl;
			in.close();
                        return 0;
                }
	}

        for (int i = 0; i < n; i++) {
		in >> a[i];
		if ((a[i] <= 0) || (a[i] > b)) {
                	cout << "ERROR: invalid constraint coefficient" << endl;
			in.close();
                        return 0;
                }
	}

	in.close();
	
	try {
		GRBEnv env = GRBEnv();
		GRBModel model = GRBModel(env);
	
		GRBLinExpr obj = 0.0;
		GRBLinExpr ctr = 0.0;

		GRBVar* x = new GRBVar[n];
		for(int i = 0; i < n; i++) {
			x[i] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY);
			obj += c[i] * x[i];
			ctr += a[i] * x[i];
		}

		model.setObjective(obj, GRB_MAXIMIZE);
		model.addConstr(ctr, GRB_LESS_EQUAL, b);

		model.optimize();

		ofstream out("mochila_01.out");
		if(!out.is_open()) {
                	cout << "ERROR: could not open file mochila.out" << endl;
                	return 0;
        	}

		out << model.get(GRB_DoubleAttr_ObjVal) << endl;
		for (int i = 0; i < n; i++) out << x[i].get(GRB_DoubleAttr_X) << "\t";

		out.close();

	} catch(GRBException e) {
                cout << "Error code = " << e.getErrorCode() << endl;
                return 0;
        } catch(...) {
                cout << "Exception during optimization" << endl;
                return 0;
        }

	return 0;
}
