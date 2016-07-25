/*
 * main.cpp
 *
 *  Created on: Jul 20, 2016
 *      Author: mason
 */


#include <iostream>
#include <cstdio>
#include "N3L.h"

#include "Eigen/Dense"

using namespace Eigen;

using namespace std;


void func2( MatrixXd x, MatrixXd y, MatrixXd f(const MatrixXd&, const MatrixXd&) = equal_deri){

	MatrixXd z = f(x, y);

	cout << "z: " <<  endl << z << endl;

}

void func1(MatrixXd x, MatrixXd f(const MatrixXd&) = equal ){

	MatrixXd z = f(x);

	cout << "z: " <<  endl << z << endl;
}


class Test{

public:
	MatrixXd (*f)(const MatrixXd&, const MatrixXd&);

public:
	inline void run(const MatrixXd& x, const MatrixXd& y){
		MatrixXd z = f(x, y);
		cout << "z: " <<  endl << z << endl;
	}

	inline void set(MatrixXd (*c)(const MatrixXd&, const MatrixXd&)){
		f = c;
	}

public:

};

int main(void){

	MatrixXd m, n, b;

	m.setConstant(3, 2, 0.2);

	n.setConstant(2, 4, 5);

	cout << m.rows() << " " << m.cols() << endl;

	MatrixXd z =  m*n;

	cout << "before add z: " << endl << z << endl;

	b.setConstant(3, 1, 1);


	for(int idx = 0; idx < z.cols(); idx++){
		z.col(idx) += b.col(0);
	}


	cout << "after add z: " << endl << z << endl;

	func1(m);

	func1(m, tanh);

	func2(n, m);

	func2(n, m, tanh_deri);

	Test a;
	a.set(&equal_deri);
	a.run(n, m);

	a.set(&tanh_deri);
	a.run(n, m);


}

