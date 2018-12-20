#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;


int main(){
	namedWindow("Normal", WINDOW_AUTOSIZE);
	namedWindow("Cinza", WINDOW_AUTOSIZE);
	namedWindow("Bordas", WINDOW_AUTOSIZE);

	VideoCapture cap(0); //Abre a camera

	//Verifica se conseguiu abrir a camera
	if (!cap.isOpened()){
		cout << "Não foi possivel abrir a captura." << endl;
		return -1;
	}

	Mat captura, cinza, bordas;
	for (;;){
		cap >> captura;
		if (captura.empty()) break;
		imshow("Normal", captura);
		cvtColor(captura, cinza, COLOR_BGR2GRAY);
		imshow("Cinza", cinza);
		Canny(cinza, bordas, 50, 100, 3, true);
		imshow("Bordas", bordas);

		//Aguarda ESC para escerar a execução
		char c = waitKey(10);
		if(c == 27) break;
	}
	//Encerra os videos e a captura
	cap.release();

	return 0;
}
