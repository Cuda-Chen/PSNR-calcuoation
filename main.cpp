#include <iostream>
#include <fstream>
#include <cmath> // log10

#include "array.h"
#include "bmp.h"

using namespace std;

// functions of calculating image quality
pair<double, double> calculatePSNR(unsigned char* in, unsigned char* out, int nr, int nc);

int main(int argc, char **argv)
{
	// check input param counts
	if(argc != 3)
	{
		cout << "Error! Usage: ./PSNRCalculation [originalFile] [processedFile]" << endl;
		return 1;
	}

	unsigned char *ima; // originalFile
	unsigned char *bima; // processedFile
	int nr = 0; // originalFile image width
	int nc = 0; // originalFile image height
	int depth = 0; // originalFile image depth
	int nrNew = 0; // processedFile image width
	int ncNew = 0; // processedFile image height
	int depthNew = 0; //processedFile image depth

	// read originalFile
	ima = Read_BMP_To_1D(argv[1], &nr, &nc, &depth);
	if(ima == NULL)
	{
		cerr << "cannot read file: " << argv[1] << endl;
		return -1;
	}

	// read processedFile
	bima = Read_BMP_To_1D(argv[2], &nrNew, &ncNew, &depthNew);
	if(bima == NULL)
	{
		cerr << "cannot read file: " << argv[2] << endl;
		return -1;
	}

	pair<double, double> retvalData = calculatePSNR(ima, bima, nr, nc);

	cout << "MSE: " << retvalData.first << endl
		<< "PSNR: " << retvalData.second << endl;

	// write MSE and PSNR to csv file
	/*ofstream output;
	output.open("mse_psnr.csv", ofstream::out | ofstream::app);
	if(!output.is_open())
	{
		cerr << "Error opening mse_psnr.csv" << endl;
		return -1;
	}
	output << argv[2] << "," << retvalData.first << "," << retvalData.second  << endl;
	output.close();*/

	free(ima);
	free(bima);

	return 0;
}

pair<double, double> calculatePSNR(unsigned char* in, unsigned char* out, int nr, int nc){
        int i, j;
        int max = 0;
        int sum;
        double MSE;
        double PSNR;

        sum = max = 0;
        for(i = 0;i < nr;i++){
                for(j = 0;j < nc;j++){
                        if(in[(i * nc) + j] > max) max = in[(i * nc) + j];
                        int diff = (in[(i * nc) + j] - out[(i * nc) + j]);
                        sum += diff * diff;
                }
        }
        //MSE = (double)sum / (nr * nc);
	MSE = abs((double)sum / (nr * nc));
        PSNR = 10.0f * log10((double)max * max / MSE);

        return make_pair(MSE, PSNR);
}

