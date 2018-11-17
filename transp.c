#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void initialize_matrix(float *matrix, int width) {
  float a = 100;
  srand((unsigned int)time(NULL));

  for (int row = 0; row < width; row++)
    for (int column = 0; column < width; column++)
      matrix[row * width + column] = (float)rand() / (float)(RAND_MAX / a);
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Usage: <width>  <block> \n");
    return 1;
  }
  int m_width = atoi(argv[1]);
  int blocksize = atoi(argv[2]);

  if (m_width < blocksize) {
    fprintf(stderr, "Usage: <width> should be greater than <block> \n");
    return 1;
  }

  float *in_matrix = (float *)malloc(m_width * m_width * sizeof(float));
  initialize_matrix(in_matrix, m_width);
  float *out_matrix = (float *)malloc(m_width * m_width * sizeof(float));
  printf("\n");

  free(in_matrix);
  free(out_matrix);
  return 0;
}
