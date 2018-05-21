#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace cv;

int main( int argc, char** argv ){
  int nClusters = 6;
  Mat rotulos;
  int nRodadas = 1;
  Mat centros;


  Mat img = imread( "gash.jpg", CV_LOAD_IMAGE_COLOR);
  Mat samples(img.rows * img.cols, 3, CV_32F);
    for (int i = 0; i < 10; i++)
    {
      for( int y = 0; y < img.rows; y++ ){
        for( int x = 0; x < img.cols; x++ ){
          for( int z = 0; z < 3; z++){
            samples.at<float>(y + x*img.rows, z) = img.at<Vec3b>(y,x)[z];
          }
        }
      }


  kmeans(samples,
		 nClusters,
		 rotulos,
		 TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001),
		 nRodadas,
		 KMEANS_PP_CENTERS,
		 centros );


  Mat rotulada( img.size(), img.type() );
  for( int y = 0; y < img.rows; y++ ){
    for( int x = 0; x < img.cols; x++ ){
	  int indice = rotulos.at<int>(y + x*img.rows,0);
	  rotulada.at<Vec3b>(y,x)[0] = (uchar) centros.at<float>(indice, 0);
	  rotulada.at<Vec3b>(y,x)[1] = (uchar) centros.at<float>(indice, 1);
	  rotulada.at<Vec3b>(y,x)[2] = (uchar) centros.at<float>(indice, 2);
	}
  }
  //salvando as imagens
		if (i == 0) {
			imshow("clustered image", rotulada);
			imwrite("k1.jpg", rotulada);
		}
		if (i == 1) {
			imshow("clustered image", rotulada);
			imwrite("k2.jpg", rotulada);
		}
		if (i == 2) {
			imshow("clustered image", rotulada);
			imwrite("k3.jpg", rotulada);
		}
		if (i == 3) {
			imshow("clustered image", rotulada);
			imwrite("k4.jpg", rotulada);
		}
		if (i == 4) {
			imshow("clustered image", rotulada);
			imwrite("k5.jpg", rotulada);
		}
		if (i == 5) {
			imshow("clustered image", rotulada);
			imwrite("k6.jpg", rotulada);
		}
		if (i == 6) {
			imshow("clustered image", rotulada);
			imwrite("k7.jpg", rotulada);
		}
		if (i == 7) {
			imshow("clustered image", rotulada);
			imwrite("k8.jpg", rotulada);
		}
		if (i == 8) {
			imshow("clustered image", rotulada);
			imwrite("k9.jpg", rotulada);
		}
		if (i == 9) {
			imshow("clustered image", rotulada);
			imwrite("k10.jpg", rotulada);
		}
  }
  return 0;
}
