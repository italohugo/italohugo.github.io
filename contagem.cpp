#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height;

  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

  if(!image.data){
    std::cout << "Erro ao abrir imagem!\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;

//Resolvendo o problema das bordas
  for(int i=0; i<height; i++){
    if(image.at<uchar>(0,i) == 255){
	p.x=0;
	p.y=i;
	floodFill(image,p,0);
    }
  }
  for(int i=0; i<height; i++){
    if(image.at<uchar>(i,width-1) == 255){
	p.x=width-1;
	p.y=i;
	floodFill(image,p,0);
    }
  }
  for(int j=0; j<width; j++){
    if(image.at<uchar>(0,j) == 255){
	p.x=j;
	p.y=0;
	floodFill(image,p,0);
    }
  }
  for(int j=0; j<width; j++){
    if(image.at<uchar>(height-1,j) == 255){
	p.x=j;
	p.y=height-1;
	floodFill(image,p,0);
    }
  }

//mudando cor do background
  p.x=0;
  p.y=0;
  floodFill(image,p,155);

//Contando as bolhas
  int numb = 0;
  int numf = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      //Achou uma bolha
      if(image.at<uchar>(i,j) == 255){
        numb++;
        p.x=j;
        p.y=i;
        floodFill(image,p,40);
      }
      //pinta o burado da bolha
      if(image.at<uchar>(i,j) == 0){
        p.x=j;
        p.y=i-1;
        floodFill(image,p,200);
        p.x=j;
        p.y=i;
        floodFill(image,p,200);
      }
    }
  }
  //Contando as bolhas com buraco e pintando elas na cor normal
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 200){
        numf++;
        p.x=j;
        p.y=i;
        floodFill(image,p,40);
      }
    }
  }

  cout << numb << " bolhas foram encontradas." << endl;
  cout << numf << " bolhas com furos foram encontradas." << endl;

  imshow("Resultado", image);
  imwrite("resultado.png", image);
  waitKey();
  return 0;
}
