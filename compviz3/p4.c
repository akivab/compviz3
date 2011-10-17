#include"vision_utilities.h"
#include<stdio.h>
#include<stdlib.h>


int main(int nargin, char** argv){
  if(nargin != 6){
    printf("Usage: p4 <img> <hough img> <thresh edge img> <hough thresh> <cropped line-detected output>\n");
    return -1;
  }
  
  Image* im = (Image*) malloc(sizeof(Image));
  Image* hough = (Image*) malloc(sizeof(Image));
  Image* edge = (Image*) malloc(sizeof(Image));
  readImage(im, argv[1]);
  readImage(hough, argv[2]);
  readImage(edge, argv[3]);

  int i, j, k, nR, nC;
  nR = getNRows(im);
  nC = getNCols(im);
  
  int thresh = atoi(argv[4]);
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
	
	// for each point from x = 0 to x = nC, we see how close we are.
	int closestDist[nC];
	int zx, zy, x, y, min = 9999;
	int win = 2;
	for(k = 0; k < nC ; k++){
	  min = 9999;
	  x = k;
	  y = m*x + b;
	  for(zx = -win; zx < win; zx++)
	    for(zy = -win; zy < win; zy++)
	      if(getPixel(edge, y+zy, x+zx) > 0)
		min = MIN(min, sqrt(zy*zy+zx*zx));
	  closestDist[k] = min;
	}
	int mean = 0;
	for(k = 0; k < nC; k++) mean += closestDist[k];
	mean /= nC;

	int first = -1, last = -1;
	for(k=0; k<nC; k++)
	  if(closestDist[k] < mean && first == -1)
	      first = k;
	  else if(closestDist[k] < mean && first !=-1)
	    last = k;
	  else if(closestDist[k] > mean && last != -1){
	    line(im, (int) (m*first+b), first, (int) (m*last+b), last, 0);
	    first = -1;
	    last = -1;
	  }
      }
    }
  
  writeImage(im, argv[5]);
  free(im);
  free(hough);
  return 0;
}
