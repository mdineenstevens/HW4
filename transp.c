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
void print_matrix(float *matrix, int width) {
  int row, columns;
  for (int row = 0; row < width; row++) {
    for (int columns = 0; columns < width; columns++) {
      printf("%*.*f ", 5, 2, matrix[row * width + columns]);
    }
    printf("\n");
  }
}
void transpose_matrix(float *matrix, float *out_matrix, int width, int block) {

  for (int i = 0; i < width; i += block) {
    for (int j = 0; j < width; j += block) {
      for (int x = i; x < i + block; ++x) {
        for (int y = j; y < j + block; ++y) {
          out_matrix[x + y * width] = matrix[y + x * width];
        }
      }
    }
  }
}
int main(int argc, char *argv[]) {
  struct timeval start, end;

  gettimeofday(&start, NULL);

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
  // print_matrix(in_matrix, m_width);
  float *out_matrix = (float *)malloc(m_width * m_width * sizeof(float));
  gettimeofday(&start, NULL);
  transpose_matrix(in_matrix, out_matrix, m_width, blocksize);
  gettimeofday(&end, NULL);
  printf("Total time = %f seconds\n",
         (double)(end.tv_usec - start.tv_usec) / 1000000 +
             (double)(end.tv_sec - start.tv_sec));
  printf("\n");
  // print_matrix(out_matrix, m_width);

  free(in_matrix);
  free(out_matrix);
  return 0;
}
