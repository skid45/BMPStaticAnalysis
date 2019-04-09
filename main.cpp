#include "BMPStaticAnalysis.h"

int main() {
	BMPStaticAnalysis original("BoatsColor.bmp");
	BMPStaticAnalysis q(original);
	q.writeFileForRGB();

	cout << "r(R,G): " << original.correlation_coefficient(original.getR(), original.getG(), 0, 0) << endl;
	cout << "r(R,B): " << original.correlation_coefficient(original.getR(), original.getB(), 0, 0) << endl;
	cout << "r(B,G): " << original.correlation_coefficient(original.getB(), original.getG(), 0, 0) << endl;

	//original.shifting();

	original.writeFileForYCbCr();

	cout << "r(Y,Cb): " << original.correlation_coefficient(original.getY(), original.getCb(), 0, 0) << endl;
	cout << "r(Y, Cr): " << original.correlation_coefficient(original.getY(), original.getCr(), 0, 0) << endl;
	cout << "r(Cr, Cb): " << original.correlation_coefficient(original.getCr(), original.getCb(), 0, 0) << endl;

	q.YCbCrToRGB();
	q.writeFullColorFile("recovering.bmp");
	cout << "PSNR component R: " << original.PSNR(original.getR(), q.getR()) << endl;
	cout << "PSNR component G: " << original.PSNR(original.getG(), q.getG()) << endl;
	cout << "PSNR component B: " << original.PSNR(original.getB(), q.getB()) << endl;
	
	cout << "decimation 2 times in H and 2 times in W" << endl;
	q.setCb(q.recovering(q.decimation8a(original.getCb(), "Cb")));
	q.setCr(q.recovering(q.decimation8a(original.getCr(), "Cr")));
	q.YCbCrToRGB();
	cout << "PSNR component R(8a): " << original.PSNR(original.getR(), q.getR()) << endl;
	cout << "PSNR component G(8a): " << original.PSNR(original.getG(), q.getG()) << endl;
	cout << "PSNR component B(8a): " << original.PSNR(original.getB(), q.getB()) << endl;
	cout << "PSNR component Cb(8a): " << original.PSNR(original.getCb(), q.getCb()) << endl;
	cout << "PSNR component Cr(8a): " << original.PSNR(original.getCr(), q.getCr()) << endl;


	q.setCb(q.recovering(q.decimation8b(original.getCb(), "Cb")));
	q.setCr(q.recovering(q.decimation8b(original.getCr(), "Cr")));
	q.YCbCrToRGB();
	cout << "PSNR component R(8b): " << original.PSNR(original.getR(), q.getR()) << endl;
	cout << "PSNR component G(8b): " << original.PSNR(original.getG(), q.getG()) << endl;
	cout << "PSNR component B(8b): " << original.PSNR(original.getB(), q.getB()) << endl;
	cout << "PSNR component Cb(8b): " << original.PSNR(original.getCb(), q.getCb()) << endl;
	cout << "PSNR component Cr(8b): " << original.PSNR(original.getCr(), q.getCr()) << endl;


	cout << "decimation 4 times in H and 4 times in W" << endl;
	q.setCb(q.recovering(q.recovering(q.decimation8a(q.decimation8a(original.getCb(), ""), "Cb"))));
	q.setCr(q.recovering(q.recovering(q.decimation8a(q.decimation8a(original.getCr(), ""), "Cr"))));
	q.YCbCrToRGB();
	cout << "PSNR component R(11-8a): " << original.PSNR(original.getR(), q.getR()) << endl;
	cout << "PSNR component G(11-8a): " << original.PSNR(original.getG(), q.getG()) << endl;
	cout << "PSNR component B(11-8a): " << original.PSNR(original.getB(), q.getB()) << endl;
	cout << "PSNR component Cb(11-8a): " << original.PSNR(original.getCb(), q.getCb()) << endl;
	cout << "PSNR component Cr(11-8a): " << original.PSNR(original.getCr(), q.getCr()) << endl;

	q.setCb(q.recovering(q.recovering(q.decimation8b(q.decimation8b(original.getCb(), ""), "Cb"))));
	q.setCr(q.recovering(q.recovering(q.decimation8b(q.decimation8b(original.getCr(), ""), "Cr"))));
	q.YCbCrToRGB();
	cout << "PSNR component R(11-8b): " << original.PSNR(original.getR(), q.getR()) << endl;
	cout << "PSNR component G(11-8b): " << original.PSNR(original.getG(), q.getG()) << endl;
	cout << "PSNR component B(11-8b): " << original.PSNR(original.getB(), q.getB()) << endl;
	cout << "PSNR component Cb(11-8b): " << original.PSNR(original.getCb(), q.getCb()) << endl;
	cout << "PSNR component Cr(11-8b): " << original.PSNR(original.getCr(), q.getCr()) << endl;

	/*
	original.frequencyHistogram("histogramR", original.getR());
	original.frequencyHistogram("histogramG", original.getG());
	original.frequencyHistogram("histogramB", original.getB());
	original.frequencyHistogram("histogramY", original.getY());
	original.frequencyHistogram("histogramCb", original.getCb());
	original.frequencyHistogram("histogramCr", original.getCr());
	*/
	cout << "entropy R component: " << original.entropy(original.getR()) << endl;
	cout << "entropy G component: " << original.entropy(original.getG()) << endl;
	cout << "entropy B component: " << original.entropy(original.getB()) << endl;
	cout << "entropy Y component: " << original.entropy(original.getY()) << endl;
	cout << "entropy Cb component: " << original.entropy(original.getCb()) << endl;
	cout << "entropy Cr component: " << original.entropy(original.getCr()) << endl;
	
	for (int i = 1; i <= 4; i++) {
		original.DArray(original.getR(), i, "DR");
		original.DArray(original.getG(), i, "DG");
		original.DArray(original.getB(), i, "DB");
		original.DArray(original.getY(), i, "DY");
		original.DArray(original.getCb(), i, "DCb");
		original.DArray(original.getCr(), i, "DCr");
	}

	original.rotate();
	//original.writeFullColorFile();
	
	//system("py graphics.py");
	system("pause");
	return 0;
}