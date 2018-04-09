#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image1,  hist1, hist2;
  VideoCapture cap;
  double comp;
  double limiar = 0.99;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  vector<Mat> vet;

  cap.open(0);

  if(!cap.isOpened()){
    cout << "Não foi possvel abrir a camera";
    return -1;
  }

  //captura a primeira imagem
  cap >> image1;

  split( image1, vet );

  calcHist(&vet[1], 1, 0, Mat(), hist2, 1, &nbins, &histrange, uniform, acummulate);

  while(1){
    //Captura uma nova imagem
    cap >> image1;
    //converte para cinza
    //separa as cores RGB
    split( image1, vet );

    //Calcula o histograma de G
    calcHist(&vet[1], 1, 0, Mat(), hist1, 1, &nbins, &histrange, uniform, acummulate);

    //Compara o histograma novo com o antigo
    comp = compareHist(hist1, hist2, CV_COMP_CORREL);

    //processo de alarme
    if (comp < limiar) {
    putText(image1, "Movimento detectado!", Point(10, 40), FONT_HERSHEY_TRIPLEX, 1.0, CV_RGB(255,0,0), 2.0);
    }
    imshow("image1", image1);

    //Guarda o histograma novo na variável do antigo
    calcHist(&vet[1], 1, 0, Mat(), hist2, 1, &nbins, &histrange, uniform, acummulate);

    if(waitKey(30) >= 0) break;
  }

  return 0;
}
