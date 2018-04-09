#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, cinza, saida, histG, histE;
  VideoCapture cap;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  int histw = nbins, histh = nbins/2;
  Mat histGimg(histh, histw, CV_BGR2GRAY, Scalar(0));
  Mat histEimg(histh, histw, CV_BGR2GRAY, Scalar(0));

  cap.open(0);

  if(!cap.isOpened()){
    cout << "Erro ao abrir camera.";
    return -1;
  }

  while(1){
    //captura a imagem
    cap >> image;
    //transforma para escala de cinza
    cvtColor( image, cinza, CV_BGR2GRAY );
    //equaliza o histograma
    equalizeHist( cinza, saida );

    calcHist(&cinza, 1, 0, Mat(), histG, 1, &nbins, &histrange, uniform, acummulate);

    calcHist(&saida, 1, 0, Mat(), histE, 1, &nbins, &histrange, uniform, acummulate);

    normalize(histG, histG, 0, histGimg.rows, NORM_MINMAX, -1, Mat());
    normalize(histE, histE, 0, histEimg.rows, NORM_MINMAX, -1, Mat());

    histGimg.setTo(Scalar(0));
    histEimg.setTo(Scalar(0));

    for(int i=0; i<nbins; i++){
      line(histGimg,
           Point(i, histh),
           Point(i, histh-cvRound(histG.at<float>(i))),
           Scalar(255), 1, 8, 0);
      line(histEimg,
           Point(i, histh),
           Point(i, histh-cvRound(histE.at<float>(i))),
           Scalar(255), 1, 8, 0);
    }

    histGimg.copyTo(cinza(Rect(0, 0,nbins, histh)));
    histEimg.copyTo(saida(Rect(0, 0,nbins, histh)));

    imshow("saida", saida);
    imshow("cinza", cinza);

  }

  return 0;
}
