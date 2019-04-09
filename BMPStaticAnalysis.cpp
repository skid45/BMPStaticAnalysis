#include "BMPStaticAnalysis.h"


BMPStaticAnalysis::BMPStaticAnalysis(const char* filename) {
	readFile(filename);
	RGBToYCbCr();
}

BMPStaticAnalysis::BMPStaticAnalysis(BMPStaticAnalysis& copy) {
	this->R = copy.R;
	this->G = copy.G;
	this->B = copy.B;
	this->Y = copy.Y;
	this->Cb = copy.Cb;
	this->Cr = copy.Cr;
}

void BMPStaticAnalysis::readFile(const char* filename) {
	FILE* image;
	fopen_s(&image, filename, "rb");

	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;

	fread(&file_header, sizeof(file_header), 1, image);
	fread(&info_header, sizeof(info_header), 1, image);
	DWORD padding = ((4 - (info_header.biWidth * 3) % 4) & 3);
	RGBTRIPLE **triple = new RGBTRIPLE *[info_header.biHeight];
	for (int i = 0; i < info_header.biHeight; i++) {
		triple[i] = new RGBTRIPLE[info_header.biWidth];
		fread(&triple[i][0], sizeof(RGBTRIPLE), info_header.biWidth, image);
		if (padding != 0) {
			fread(&triple[i][0], padding, 1, image);
		}
	}
	fclose(image);

	cout << "Padding: " << padding << endl;

	for (int i = 0; i < info_header.biHeight; i++) {
		std::vector<double> Rvec;
		std::vector<double> Gvec;
		std::vector<double> Bvec;
		for (int j = 0; j < info_header.biWidth; j++) {
			Rvec.push_back(static_cast<double>(triple[i][j].rgbtRed));
			Gvec.push_back(static_cast<double>(triple[i][j].rgbtGreen));
			Bvec.push_back(static_cast<double>(triple[i][j].rgbtBlue));
		}
		R.push_back(Rvec);
		G.push_back(Gvec);
		B.push_back(Bvec);
	}


	for (int i = 0; i < info_header.biHeight; i++) {
		delete[] triple[i];
	}
	delete[] triple;
}

void BMPStaticAnalysis::writeFileForRGB() {
	DWORD padding = ((4 - (R[0].size() * 3) % 4) & 3);
	DWORD size = 3 * static_cast<DWORD>(R.size()) * static_cast<DWORD>(R[0].size())
		+ static_cast<DWORD>(padding) * static_cast<DWORD>(R.size());

	BITMAPFILEHEADER file_header = { 19778, size + 54, 0, 0, 54 };
	BITMAPINFOHEADER info_header = { 40, static_cast<LONG>(R[0].size()), static_cast<LONG>(R.size()),
		1, 24, 0, size, 0, 0, 0, 0 };

	FILE *R_file, *G_file, *B_file;
	fopen_s(&R_file, "outR.bmp", "wb");
	fopen_s(&G_file, "outG.bmp", "wb");
	fopen_s(&B_file, "outB.bmp", "wb");
	fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, R_file);
	fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, R_file);
	fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, G_file);
	fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, G_file);
	fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, B_file);
	fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, B_file);

	RGBTRIPLE **R_component = new RGBTRIPLE *[info_header.biHeight];
	RGBTRIPLE **G_component = new RGBTRIPLE *[info_header.biHeight];
	RGBTRIPLE **B_component = new RGBTRIPLE *[info_header.biHeight];
	for (int i = 0; i < info_header.biHeight; i++) {
		R_component[i] = new RGBTRIPLE[info_header.biWidth];
		G_component[i] = new RGBTRIPLE[info_header.biWidth];
		B_component[i] = new RGBTRIPLE[info_header.biWidth];
		for (int j = 0; j < info_header.biWidth; j++) {
			R_component[i][j].rgbtRed = static_cast<BYTE>(R[i][j]);
			R_component[i][j].rgbtGreen = 0x00;
			R_component[i][j].rgbtBlue = 0x00;
			fwrite(&R_component[i][j], sizeof(RGBTRIPLE), 1, R_file);

			G_component[i][j].rgbtRed = 0x00;
			G_component[i][j].rgbtGreen = static_cast<BYTE>(G[i][j]);
			G_component[i][j].rgbtBlue = 0x00;
			fwrite(&G_component[i][j], sizeof(RGBTRIPLE), 1, G_file);

			B_component[i][j].rgbtRed = 0x00;
			B_component[i][j].rgbtGreen = 0x00;
			B_component[i][j].rgbtBlue = static_cast<BYTE>(B[i][j]);
			fwrite(&B_component[i][j], sizeof(RGBTRIPLE), 1, B_file);
		}
		if (padding != 0) {
			fwrite(&R_component[i][0], padding, 1, R_file);
			fwrite(&G_component[i][0], padding, 1, G_file);
			fwrite(&B_component[i][0], padding, 1, B_file);
		}
	}
	fclose(R_file);
	fclose(G_file);
	fclose(B_file);

	for (int i = 0; i < info_header.biHeight; i++) {
		delete[] R_component[i];
		delete[] G_component[i];
		delete[] B_component[i];
	}
	delete[] R_component;
	delete[] G_component;
	delete[] B_component;
}

void BMPStaticAnalysis::writeFileForYCbCr() {
	DWORD padding = ((4 - (Y[0].size() * 3) % 4) & 3);
	DWORD size = 3 * static_cast<DWORD>(Y.size()) * static_cast<DWORD>(Y[0].size())
		+ static_cast<DWORD>(padding) * static_cast<DWORD>(Y.size());

	BITMAPFILEHEADER file_header = { 19778, size + 54, 0, 0, 54 };
	BITMAPINFOHEADER info_header = { 40, static_cast<LONG>(Y[0].size()), static_cast<LONG>(Y.size()),
		1, 24, 0, size, 0, 0, 0, 0 };

	FILE *Y_file, *Cb_file, *Cr_file;
	fopen_s(&Y_file, "outY.bmp", "wb");
	fopen_s(&Cb_file, "outCb.bmp", "wb");
	fopen_s(&Cr_file, "outCr.bmp", "wb");
	fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, Y_file);
	fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, Y_file);

	fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, Cb_file);
	fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, Cb_file);

	fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, Cr_file);
	fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, Cr_file);

	RGBTRIPLE **Y_component = new RGBTRIPLE *[info_header.biHeight];
	RGBTRIPLE **Cb_component = new RGBTRIPLE *[info_header.biHeight];
	RGBTRIPLE **Cr_component = new RGBTRIPLE *[info_header.biHeight];
	for (int i = 0; i < info_header.biHeight; i++) {
		Y_component[i] = new RGBTRIPLE[info_header.biWidth];
		Cb_component[i] = new RGBTRIPLE[info_header.biWidth];
		Cr_component[i] = new RGBTRIPLE[info_header.biWidth];
		for (int j = 0; j < info_header.biWidth; j++) {
			Y_component[i][j].rgbtRed = static_cast<BYTE>(Y[i][j]);
			Y_component[i][j].rgbtGreen = static_cast<BYTE>(Y[i][j]);
			Y_component[i][j].rgbtBlue = static_cast<BYTE>(Y[i][j]);
			fwrite(&Y_component[i][j], sizeof(RGBTRIPLE), 1, Y_file);

			Cb_component[i][j].rgbtRed = static_cast<BYTE>(Cb[i][j]);
			Cb_component[i][j].rgbtGreen = static_cast<BYTE>(Cb[i][j]);
			Cb_component[i][j].rgbtBlue = static_cast<BYTE>(Cb[i][j]);
			fwrite(&Cb_component[i][j], sizeof(RGBTRIPLE), 1, Cb_file);

			Cr_component[i][j].rgbtRed = static_cast<BYTE>(Cr[i][j]);
			Cr_component[i][j].rgbtGreen = static_cast<BYTE>(Cr[i][j]);
			Cr_component[i][j].rgbtBlue = static_cast<BYTE>(Cr[i][j]);
			fwrite(&Cr_component[i][j], sizeof(RGBTRIPLE), 1, Cr_file);
		}
		if (padding != 0) {
			fwrite(&Y_component[i][0], padding, 1, Y_file);
			fwrite(&Cb_component[i][0], padding, 1, Cb_file);
			fwrite(&Cr_component[i][0], padding, 1, Cr_file);
		}
	}
	fclose(Y_file);
	fclose(Cb_file);
	fclose(Cr_file);

	for (int i = 0; i < info_header.biHeight; i++) {
		delete[] Y_component[i];
		delete[] Cb_component[i];
		delete[] Cr_component[i];
	}
	delete[] Y_component;
	delete[] Cb_component;
	delete[] Cr_component;
}

void BMPStaticAnalysis::writeFullColorFile(const char* filename) {

	DWORD padding = ((4 - (R[0].size() * 3) % 4) & 3);
	DWORD size = 3 * static_cast<DWORD>(R.size()) * static_cast<DWORD>(R[0].size())
		+ static_cast<DWORD>(padding) * static_cast<DWORD>(R.size());

	BITMAPFILEHEADER file_header = { 19778, size + 54, 0, 0, 54 };
	BITMAPINFOHEADER info_header = { 40, static_cast<LONG>(R[0].size()), static_cast<LONG>(R.size()),
		1, 24, 0, size, 0, 0, 0, 0 };

	FILE *file;
	fopen_s(&file, filename, "wb");
	fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, file);
	fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, file);

	RGBTRIPLE **triple = new RGBTRIPLE *[info_header.biHeight];
	for (int i = 0; i < info_header.biHeight; i++) {
		triple[i] = new RGBTRIPLE[info_header.biWidth];
		for (int j = 0; j < info_header.biWidth; j++) {
			triple[i][j].rgbtRed = static_cast<BYTE>(R[i][j]);
			triple[i][j].rgbtGreen = static_cast<BYTE>(G[i][j]);
			triple[i][j].rgbtBlue = static_cast<BYTE>(B[i][j]);

			fwrite(&triple[i][j], sizeof(RGBTRIPLE), 1, file);
		}
		if (padding != 0) {
			fwrite(&triple[i][0], padding, 1, file);
		}
	}
	fclose(file);

	for (int i = 0; i < info_header.biHeight; i++) {
		delete[] triple[i];
	}
	delete[] triple;
}

double BMPStaticAnalysis::expected(matrix<double> component, int H, int W) {
	double expected_value = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			expected_value += component[i][j];
		}
	}
	expected_value /= (H * W);
	return expected_value;
}

double BMPStaticAnalysis::sigma(matrix<double> component, int H, int W) {
	double component_expected = expected(component, H, W);

	double sigma_value = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			sigma_value += (component[i][j] - component_expected) * (component[i][j] - component_expected);
		}
	}

	return sqrt(sigma_value / (H * W - 1));
}

double BMPStaticAnalysis::correlation_coefficient(matrix<double> A, matrix<double> B, int H, int W) {
	if (H == 0) {
		H = static_cast<int>(A.size());
		W = static_cast<int>(A[0].size());
	}
	double Aexpected = expected(A, H, W);
	double Bexpected = expected(B, H, W);

	matrix<double> common_array;
	for (int i = 0; i < H; i++) {
		vector<double> tmp_vector;
		for (int j = 0; j < W; j++) {
			tmp_vector.push_back((A[i][j] - Aexpected) * (B[i][j] - Bexpected));
		}
		common_array.push_back(tmp_vector);
	}

	double expected_value = expected(common_array, H, W);
	double sigmaA = sigma(A, H, W);
	double sigmaB = sigma(B, H, W);
	expected_value /= (sigmaA * sigmaB);
	return expected_value;
}

double BMPStaticAnalysis::clipping(double value) {
	if (value > 255) return 255;
	else if (value < 0) return 0;
	return value;
}

void BMPStaticAnalysis::RGBToYCbCr() {
	for (int i = 0; i < static_cast<int>(R.size()); i++) {
		vector<double> Yvec;
		vector<double> Cbvec;
		vector<double> Crvec;
		for (int j = 0; j < static_cast<int>(R[0].size()); j++) {
			double tmpY = round(clipping((0.299 * R[i][j]) + (0.587 * G[i][j]) + (0.114 * B[i][j])));
			Yvec.push_back(tmpY);
			Cbvec.push_back(round(clipping((0.5643 * (B[i][j] - tmpY)) + 128.0)));
			Crvec.push_back(round(clipping((0.7132 * (R[i][j] - tmpY)) + 128.0)));
		}
		Y.push_back(Yvec);
		Cb.push_back(Cbvec);
		Cr.push_back(Crvec);
	}
}

void BMPStaticAnalysis::YCbCrToRGB() {
	for (int i = 0; i < static_cast<int>(Y.size()); i++) {
		for (int j = 0; j < static_cast<int>(Y[0].size()); j++) {
			R[i][j] = round(clipping(Y[i][j] + (1.402 * (Cr[i][j] - 128.0))));
			G[i][j] = round(clipping(Y[i][j] - (0.714 * (Cr[i][j] - 128.0)) - (0.334 * (Cb[i][j] - 128.0))));
			B[i][j] = round(clipping(Y[i][j] + (1.772 * (Cb[i][j] - 128.0))));
		}
	}
}

double BMPStaticAnalysis::PSNR(matrix<double> original, matrix<double> recovery) {
	double numerator = static_cast<double>(original.size()) * static_cast<double>(original[0].size());
	numerator *= 65025.0;
	double denominator = 0;

	for (int i = 0; i < static_cast<int>(original.size()); i++) {
		for (int j = 0; j < static_cast<int>(original[0].size()); j++) {
			denominator += ((original[i][j] - recovery[i][j]) * (original[i][j] - recovery[i][j]));
		}
	}

	return 10.0 * log10(numerator / denominator);
}

matrix<double> BMPStaticAnalysis::decimation8a(matrix<double> C, string component_name) {
	matrix<double> result;
	for (int i = 1; i < static_cast<int>(C.size()); i += 2) {
		vector<double> CI;
		for (int j = 1; j < static_cast<int>(C[0].size()); j += 2) {
			CI.push_back(C[i][j]);
		}
		result.push_back(CI);
	}
	if (component_name != "") {
		cout << "Size " << component_name << " after decimation(8a) - H: " << result.size() << " W: " << result[0].size() << endl;
	}
	return result;
}

matrix<double> BMPStaticAnalysis::decimation8b(matrix<double> C, string component_name) {
	matrix<double> result;
	for (int i = 0; i < static_cast<int>(C.size()); i += 2) {
		vector<double> CI;
		for (int j = 0; j < static_cast<int>(C[0].size()); j += 2) {
			if (i + 1 < static_cast<int>(C.size())) {
				CI.push_back((C[i][j] + C[i + 1][j] + C[i][j + 1] + C[i + 1][j + 1]) / 4);
			}
			else {
				CI.push_back((C[i][j] + C[i][j + 1]) / 2);
			}
		}
		result.push_back(CI);
	}

	if (component_name != "") {
		cout << "Size " << component_name << " after decimation(8b) - H: " << result.size() << " W: " << result[0].size() << endl;
	}
	return result;
}

matrix<double> BMPStaticAnalysis::recovering(matrix<double> C) {
	matrix<double> result;
	for (int i = 0; i < static_cast<int>(C.size()); i++) {
		vector<double> CIFirst;
		vector<double> CISecond;
		for (int j = 0; j < static_cast<int>(C[0].size()); j++) {
			CIFirst.push_back(C[i][j]);
			CISecond.push_back(C[i][j]);

			if (i == 0 && j == 0) {
				CIFirst.push_back(C[i][j]);
				CISecond.push_back(C[i][j]);
			}
			else if (i == 0) {
				CIFirst.push_back(C[i][j - 1]);
				CISecond.push_back((C[i][j - 1] + CISecond.back()) / 2);
			}
			else if (j == 0) {
				CIFirst.push_back(C[i - 1][j]);
				CISecond.push_back(C[i - 1][j]);
			}
			else {
				CIFirst.push_back((C[i][j - 1] + C[i - 1][j]) / 2);
				CISecond.push_back((CIFirst.back() + CISecond.back()) / 2);
			}

		}
		result.push_back(CIFirst);
		result.push_back(CISecond);
	}
	return result;
}

void BMPStaticAnalysis::frequencyHistogram(string filename, matrix<double> component) {
	ofstream file(filename, ios_base::out | ios_base::binary);
	for (const auto &vector : component)
		for (const auto &pixel : vector)
			file << static_cast<int>(pixel) << ' ';

	file.close();
}

double BMPStaticAnalysis::entropy(matrix<double> component) {
	std::vector<double> p(513);

	for (const auto &vec : component)
		for (const auto &num : vec)
			p[static_cast<int> (num) + 256]++;

	double size = component.size() * component[0].size();
	for (auto &num : p)
		num /= size;

	double entropy = 0;

	for (const auto &num : p)
		if (num != 0)
			entropy += num * log2(num);

	return -entropy;
}

matrix<double> BMPStaticAnalysis::DArray(matrix<double> component, int rule_number, string component_name) {
	matrix<double> result;

	for (int i = 1; i < static_cast<double>(component.size()); i++) {
		vector<double> resI;
		for (int j = 1; j < static_cast<double>(component[0].size()); j++) {
			double f = 0;
			if (rule_number == 1) f = component[i][j - 1];
			else if (rule_number == 2) f = component[i - 1][j];
			else if (rule_number == 3) f = component[i - 1][j - 1];
			else if (rule_number == 4) f = ((component[i][j - 1] + component[i - 1][j] + component[i - 1][j - 1]) / 3);
			resI.push_back(component[i][j] - f);
		}
		result.push_back(resI);
	}
	string q = component_name + to_string(rule_number);
	frequencyHistogram(q, result);
	cout << "entropy " << component_name << " rule "<< rule_number << ": " << entropy(result) << endl;
	return result;
}

void BMPStaticAnalysis::rotate() {
	matrix<double> rotateR;
	matrix<double> rotateG;
	matrix<double> rotateB;

	for (int j = static_cast<int>(R[0].size()) - 1; j >= 0; j--) {
		vector<double> rotateRI;
		vector<double> rotateGI;
		vector<double> rotateBI;
		for (int i = 0; i < static_cast<int>(R.size()); i++) {
			rotateRI.push_back(R[i][j]);
			rotateGI.push_back(G[i][j]);
			rotateBI.push_back(B[i][j]);
		}
		rotateR.push_back(rotateRI);
		rotateG.push_back(rotateGI);
		rotateB.push_back(rotateBI);
	}

	this->R = rotateR;
	this->G = rotateG;
	this->B = rotateB;
}

matrix<double> BMPStaticAnalysis::shifting(matrix<double> &component) {
	int H = static_cast<int>(component.size());
	int W = static_cast<int>(component[0].size());

	matrix<double> component_2;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < H; j++) {
			std::vector<double> vec;
			for (auto &k : component[j]) {
				vec.push_back(k);
			}
			component_2.push_back(vec);
		}
	}

	matrix<double> corrCoef;
	for (int y = -10; y <= 10; y += 5) {
		std::vector<double> corrCoef_vec;
		for (int x = 0; x < W / 4; x += 4) {
			matrix<double> Aij;
			matrix<double> Amn;

			for (int i = H; i < (2 * H - y); i++) {
				std::vector<double> vec;
				vec.reserve(static_cast<unsigned long>(W - x));
				for (int j = 0; j < (W - x); j++)
					vec.push_back(component_2[i][j]);
				Aij.push_back(vec);
			}

			for (int m = (H + y); m < (2 * H); m++) {
				std::vector<double> vec;
				for (int n = x; n < W; n++)
					vec.push_back(component_2[m][n]);
				Amn.push_back(vec);
			}

			corrCoef_vec.push_back(correlation_coefficient(Aij, Amn, H - y, W - x));
		}

		corrCoef.push_back(corrCoef_vec);
	}

	return corrCoef;
}

void BMPStaticAnalysis::shifting() {
	matrix<double> correlation_coef_R = shifting(R);
	matrix<double> correlation_coef_G = shifting(G);
	matrix<double> correlation_coef_B = shifting(B);

	ofstream fR("R_corr_coef", ios_base::out | ios_base::binary);
	ofstream fG("G_corr_coef", ios_base::out | ios_base::binary);
	ofstream fB("B_corr_coef", ios_base::out | ios_base::binary);

	for (const auto &vector : correlation_coef_R) {
		for (const auto &corrcoef : vector) {
			fR << corrcoef << ' ';
		}
		fR << std::endl;
	}

	for (const auto &vector : correlation_coef_G) {
		for (const auto &corrcoef : vector) {
			fG << corrcoef << ' ';
		}
		fG << std::endl;
	}

	for (const auto &vector : correlation_coef_B) {
		for (const auto &corrcoef : vector) {
			fB << corrcoef << ' ';
		}
		fB << std::endl;
	}
}

matrix<double> BMPStaticAnalysis::getR() { return this->R; }

matrix<double> BMPStaticAnalysis::getG() { return this->G; }

matrix<double> BMPStaticAnalysis::getB() { return this->B; }

matrix<double> BMPStaticAnalysis::getY() { return this->Y; }

matrix<double> BMPStaticAnalysis::getCb() { return this->Cb; }

matrix<double> BMPStaticAnalysis::getCr() { return this->Cr; }

void BMPStaticAnalysis::setR(matrix<double> R) { this->R = R; }

void BMPStaticAnalysis::setG(matrix<double> G) { this->G = G; }

void BMPStaticAnalysis::setB(matrix<double> B) { this->B = B; }

void BMPStaticAnalysis::setY(matrix<double> Y) { this->Y = Y; }

void BMPStaticAnalysis::setCb(matrix<double> Cb) { this->Cb = Cb; }

void BMPStaticAnalysis::setCr(matrix<double> Cr) { this->Cr = Cr; }