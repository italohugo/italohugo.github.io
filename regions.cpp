#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int, char**){
  Mat image;
  int x1, y1, x2, y2;


  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "Imagem não encontrada" << endl;

  namedWindow("Exercicio 1",WINDOW_AUTOSIZE);

  cout << "Ponto 1:\nValor de X: ";
  cin >> x1;
  cout << "Valor de Y: ";
  cin >> y1;
  cout << "Ponto 2:\nValor de X: ";
  cin >> x2;
  cout << "Valor de Y: ";
  cin >> y2;

  //Negativação
  for(int i=x1;i<x2;i++){
    for(int j=y1;j<y2;j++){
      image.at<uchar>(i,j)=255-image.at<uchar>(i,j);
    }
  }

  imshow("Exercicio 1", image);
  imwrite("negativo.png", image);
  waitKey();
  return 0;
}
