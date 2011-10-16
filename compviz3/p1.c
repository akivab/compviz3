#include"vision_utilities.h"
#include<stdio.h>
#include<stdlib.h>

int del2[9] = {1, 4, 1, 4, -20, 4, 1, 4, 1};
int sobeldx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
int sobeldy[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

int main(int nargin, char** argv){
  if(nargin != 3){
    printf("Usage: p1 <img> <output>");
    return -1;
  }
  
  Image* im = (Image*) malloc(sizeof(Image));
  Image* final = (Image*) malloc(sizeof(Image));

  readImage(im, argv[1]);
  readImage(final, argv[1]);

  int i,j,dx,dy, del2sum, sxsum, sysum, mag;
  for(i=0; i < getNRows(im); i++)
    for(j=0; j < getNCols(im); j++){
      del2sum = sxsum = sysum = 0;
      for(dx=0; dx<=2; dx++)
	for(dy=0; dy<=2; dy++){
	  // we don't deal with laplacian (can't give us magnitude)
	  // but we calculate it below, along with sobel
	  // operator's dI/dx and dI/dy
	  del2sum+=del2[dy+3*dx]*getPixel(im,i-dx,j-dy);
	  sxsum+=sobeldx[dy+3*dx]*getPixel(im,i-dx,j-dy);
	  sysum+=sobeldy[dy+3*dx]*getPixel(im,i-dx,j-dy);
	}
      mag = sqrt(sxsum*sxsum + sysum*sysum);
      setPixel(final,i,j, mag);
    }
  
  writeImage(final, argv[2]);
  free(im);
  free(final);
  return 0;
}
