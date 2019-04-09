#ifndef _BMPSTATICANALYSIS_H_
#define _BMPSTATICANALYSIS_H_

#include <iostream>
#include <Windows.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

template<typename T> using matrix = vector<vector<T>>;


class BMPStaticAnalysis {
private:
	matrix<double> R;
	matrix<double> G;
	matrix<double> B;
	matrix<double> Y;
	matrix<double> Cb;
	matrix<double> Cr;
	
public:
	BMPStaticAnalysis(const char* filename);
	BMPStaticAnalysis(BMPStaticAnalysis& copy);
	void readFile(const char* filename);
	void writeFileForRGB();
	void writeFileForYCbCr();
	void writeFullColorFile(const char* filename);
	double expected(matrix<double> component, int H, int W);
	double sigma(matrix<double> component, int H, int W);
	double correlation_coefficient(matrix<double> A, matrix<double> B, int H, int W);
	double clipping(double value);
	void RGBToYCbCr();
	void YCbCrToRGB();
	double PSNR(matrix<double> original, matrix<double> recovery);
	matrix<double> decimation8a(matrix<double> C, string component_name);
	matrix<double> decimation8b(matrix<double> C, string component_name);
	matrix<double> recovering(matrix<double> C);
	void frequencyHistogram(string filename, matrix<double> component);
	double entropy(matrix<double> component);
	matrix<double> DArray(matrix<double> component, int rule_number, string component_name);
	void rotate();
	matrix<double> shifting(matrix<double> &component);
	void shifting();
	matrix<double> getR();
	matrix<double> getG();
	matrix<double> getB();
	matrix<double> getY();
	matrix<double> getCb();
	matrix<double> getCr();
	void setR(matrix<double> R);
	void setG(matrix<double> G);
	void setB(matrix<double> B);
	void setY(matrix<double> Y);
	void setCb(matrix<double> Cb);
	void setCr(matrix<double> Cr);
};

#endif // !_BMPSTATICANALYSIS_H_
