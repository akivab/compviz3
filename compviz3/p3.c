#include"vision_utilities.h"
#include<stdio.h>
#include<stdlib.h>


int main(int nargin, char** argv){
  if(nargin != 3){
    printf("Usage: p1 <img> <hough img> <hough thresh> <line-detected output>");
    return -1;
  }
  
  Image* im = (Image*) malloc(sizeof(Image));
  Image* hough = (Image*) malloc(sizeof(Image));

  readImage(im, argv[1]);
  readImage(hough, argv[2]);

  int i, j, nR, nC;
  nR = getNRows(im);
  nC = getNCols(im);
  
  int thresh = atoi(argv[3]);
  int p = 0;
  
  for(i=0; i < getNRows(hough); i++)
    for(j=0; j < getNCols(hough); j++){
      p = getPixel(hough, i, j);
      
    }
  
  writeImage(final, argv[2]);
  free(im);
  free(final);
  return 0;
}
