#include"vision_utilities.h"
#include<stdio.h>
#include<stdlib.h>

#define VIZ(X) (!X || (random()/(0.1+RAND_MAX) < X))

Image* getHoughTransform(Image* im, int w /*num columns*/, int h /*num rows*/){
  Image* toReturn = (Image*) malloc(sizeof(Image));
  int x, y, p, t;
  int P_MAX = (int) sqrt(w*w+h*h);
  int T_MAX = 180;
  
  int max = 0;
  int NBT = 1, NBP = 1;
  float _t;

  int** counts = (int**) malloc(sizeof(int*) * P_MAX / NBP);
  for(p = 0; p < P_MAX / NBP; p++)
    counts[p] = (int*) calloc(sizeof(int), sizeof(int) * T_MAX / NBT);
  
  for(x = 0; x < w; x++)
    for(y = 0; y < h; y++)
      if(VIZ(0) && getPixel(im, y, x) > 0){
	for(t = -T_MAX; t < 0; t++){
	  _t = t;
	  _t = - x* sin(_t / 180 * PI) + y * cos(_t / 180 * PI);
	  
	  p = (int) _t;
	  
	  if(p < P_MAX && p >= 0){
	    counts[p / NBP][(t+T_MAX)/NBT]++;
	    max = MAX(counts[p / NBP][(t+T_MAX)/NBT], max);
	  }
	}
      }
  
  setSize(toReturn, P_MAX / NBP, T_MAX / NBT);
  setColors(toReturn, 256);
  for(t = 0; t < T_MAX / NBT; t++)
    for(p = 0; p < P_MAX / NBP; p++){
      float v = (counts[p][t] * (1.0 / max));
      setPixel(toReturn, p, t, (int) (v*256));
    }
  for(p = 0; p < P_MAX / NBP; p++)
    free(counts[p]);
  free(counts);

  return toReturn;
}

int main(int nargin, char** argv){
  if(nargin != 5){
    printf("Usage: p1 <img> <thresh> <output thresh> <output hough>\n");
    return -1;
  }
  
  Image* im = (Image*) malloc(sizeof(Image));
  
  readImage(im, argv[1]);
  int thresh = atoi(argv[2]);
  int i,j, nR, nC;
  nR = getNRows(im);
  nC = getNCols(im);
  
  for(i=0; i < nR; i++)
    for(j=0; j < nC; j++)
      if(getPixel(im,i,j) < thresh)
	setPixel(im,i,j,0);
  writeImage(im, argv[3]);
  
  
  /*  Image* test1 = (Image*) calloc(sizeof(Image), sizeof(Image));
  setSize(test1, 10, 10);
  setColors(test1,2);
  for(i = 0; i < 10; i++)
    for(j = 0; j < 10; j++)
      setPixel(test1,i,j,0);
  for(i = 0; i < 10; i++)
    {
      setPixel(test1,i,i,1);
      setPixel(test1,10-i,i,1);
      }
      free(test1);*/
  
  Image* houghim = getHoughTransform(im,nC,nR); 
  writeImage(houghim, argv[4]);
  

  free(houghim);
  free(im);
  return 0;
}
