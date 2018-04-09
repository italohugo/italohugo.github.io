#include <iostream>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <stdlib.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

int main(int, char**){
  Mat img, aux1, aux2, img2;

  img= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!img.data)
    cout << "Erro ao biel.png!" << endl;

  namedWindow("Resultado",WINDOW_AUTOSIZE);

//Salvando quadrantes
  Mat Q1(img, Rect(0,0,(img.size().width/2),(img.size().height/2)));
  Mat Q2(img, Rect((img.size().height/2),0,(img.size().width/2),(img.size().height/2)));
  Mat Q3(img, Rect(0,(img.size().height/2),(img.size().width/2),(img.size().height/2)));
  Mat Q4(img, Rect((img.size().height/2),(img.size().height/2),(img.size().width/2),(img.size().height/2)));

//Concatenando quadrantes
  hconcat(Q4, Q3, aux1);
  hconcat(Q2, Q1, aux2);
  vconcat(aux1, aux2, img2);

  imshow("Resultado", img2);
  imwrite("result.png", img2);
  waitKey();
  return 0;
}
