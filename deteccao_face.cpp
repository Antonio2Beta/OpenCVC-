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
	
	//Localização do arquivo XML utilizado para a detecção de faces
	String df_name = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
	CascadeClassifier df;
	
	//Teste de carregamento do arquivo XML
	if( !df.load( df_name ) ){ printf("(!)Erro ao carregar XLM haarcascade\n"); return -1; };
	
	//Abre a camera
	VideoCapture cap(0);

	//Verifica se conseguiu abrir a camera
	if (!cap.isOpened()){
		cout << "Não foi possivel abrir a captura." << endl;
		return -1;
	}

	Mat captura, cinza, cinza_temp;
	for (;;){
		cap >> captura;
		if (captura.empty()) break;
		
		//Converte a imagem para cinza
		cvtColor(captura, cinza, COLOR_BGR2GRAY);
		
		//Executa a detecção de face
		vector< Rect_<int> > faces;
		df.detectMultiScale(cinza,faces,1.1,3,CASCADE_SCALE_IMAGE,Size(20,20));
		cinza_temp = captura.clone();
		
		//Pega o número de linhas e colunas da Matriz captura
		int lar = captura.cols;
		int alt = captura.rows;

		//Desenha o retangulo verde na face encontrada
		for (int i=0; i<faces.size();i++){
			Rect face_i = faces[i];
			Mat face = cinza(face_i);
	 	
			Mat face_redmi;
			resize(face, face_redmi, Size(lar, alt), 1.0, 1.0, INTER_CUBIC);
			rectangle(captura, face_i, CV_RGB(0, 255,0), 1);
		}
	
	//Texto que será mostrado
	String n_faces = "Faces encontradas: "+to_string(faces.size());	
	
	//Mostra a quatidade de Faces encontradas
	putText(captura,n_faces,Point(15,65),FONT_HERSHEY_SIMPLEX,1,(255,255,255),2,LINE_AA);
	
	
	namedWindow("Detecção", WINDOW_AUTOSIZE);
	imshow("Detecção", captura);
	
	//Aguarda a tecla ESC para encerrar a execução
	char c = waitKey(10);
	if(c == 27) break;
	}
	
	//Encerra os videos e a captura
	cap.release();
	destroyAllWindows();

	return 0;
}
