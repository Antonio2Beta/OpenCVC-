/*

	Disciplina: Programação Estruturada	
	Projeto: Detecção de Faces
	Biblioteca: OpenCV
	Autores:Antonio Vicente
			Francisco Marcos
			Joyce Claine
			Willyam Stepham

*/
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include <iostream>

using namespace std;
using namespace cv;


int main(){
	
	String df_name = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
	CascadeClassifier df;

	if( !df.load( df_name ) ){ printf("(!)Erro ao carregar XLM haarcascade\n"); return -1; };
	
	VideoCapture cap(0);

	if (!cap.isOpened()){
		cout << "Não foi possivel abrir a captura." << endl;
		return -1;
	}

	Mat captura, cinza, cinza_temp;
	for (;;){
		cap >> captura;
		if (captura.empty()) break;
		
		cvtColor(captura, cinza, COLOR_BGR2GRAY);
		
		vector< Rect_<int> > faces;
		df.detectMultiScale(cinza,faces,1.1,3,CASCADE_SCALE_IMAGE,Size(20,20));
		cinza_temp = captura.clone();
		
		int lar = captura.cols;
		int alt = captura.rows;

		for (int i=0; i<faces.size();i++){
			Rect face_i = faces[i];
			Mat face = cinza(face_i);
	 	
			Mat face_redmi;
			resize(face, face_redmi, Size(lar, alt), 1.0, 1.0, INTER_CUBIC);
			rectangle(captura, face_i, CV_RGB(0, 255,0), 1);
		}
	
	String n_faces = "Faces encontradas: "+to_string(faces.size());	
	
	putText(captura,n_faces,Point(15,65),FONT_HERSHEY_SIMPLEX,1,(255,255,255),2,LINE_AA);
	
	
	namedWindow("Detecção", WINDOW_AUTOSIZE);
	imshow("Detecção", captura);
	
	char c = waitKey(10);
	if(c == 27) break;
	}
	
	cap.release();
	destroyAllWindows();

	return 0;
}
