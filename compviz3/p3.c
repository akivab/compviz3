#include"vision_utilities.h"
#include<stdio.h>
#include<stdlib.h>


int main(int nargin, char** argv){
  if(nargin != 5){
    printf("Usage: p1 <img> <hough img> <hough thresh> <line-detected output>\n");
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
      p = getPixel(hough,i,j);

      if(p > thresh){
	// draw our line
	// the i'th value is our p value. j'th is theta + 90 degrees.
	// equation was: p = - x sin(t) + y cos(t)
	// now we have: y = x tan(t) + p/cos(t)
	float t = j - 180;
	float p = i;
	float m = tan(t / 180 * PI);
	float b = p / cos(t / 180 * PI);
	
	line(im, (int) (m*0+b), 0, (int) (m*nC+b), nC, 0);
      }
    }
  
  writeImage(im, argv[4]);
  free(im);
  free(hough);
  return 0;
}
