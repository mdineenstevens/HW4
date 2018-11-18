#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void initialize_matrix(float *matrix, int width, int height) {
  float a = 100;
  srand((unsigned int)time(NULL));

  for (int row = 0; row < height; row++)
    for (int column = 0; column < width; column++)
      matrix[row * width + column] = (float)rand() / (float)(RAND_MAX / a);
}
void print_matrix(float *matrix, int width, int height) {
  int row, columns;
  for (int row = 0; row < height; row++) {
    for (int columns = 0; columns < width; columns++) {
      printf("%*.*f ", 5, 2, matrix[row * width + columns]);
    }
    printf("\n\n");
  }
}
void print_transpose(float *matrix, int width, int height) {
  int row, columns;
  for (int row = 0; row < width; row++) {
    for (int columns = 0; columns < height; columns++) {
      printf("%*.*f ", 5, 2, matrix[row * width + columns]);
    }
    printf("\n\n");
  }
}
void trans(float *matrix, float *out_matrix, int width, int height, int block) {
  for (int i = 0; i < height; i += block) {
    for (int j = 0; j < width; j += block) {
      if ((i + block <= height) && (j + block <= width)) {
        for (int x = i; x < i + block; ++x) {
          for (int y = j; y < j + block; ++y) {
            out_matrix[x + y * width] = matrix[y + x * width];
          }
        }
      } else {
        for (int x = i; x < height; ++x) {
          for (int y = j; y < width; ++y) {
            out_matrix[x + y * width] = matrix[y + x * width];
          }
        }
      }
    }
  }
}
int main(int argc, char *argv[]) {

  struct timeval start, end;

  if (argc != 4) {
    fprintf(stderr, "Usage: <width>  <height>  <blocksize>  \n");
    return 1;
  }
  int m_width = atoi(argv[1]);
  int m_height = atoi(argv[2]);
  int blocksize = atoi(argv[3]);

  if (m_width < blocksize) {
    fprintf(stderr, "Usage: <width> should be greater than <block> \n");
    return 1;
  }

  float *in_matrix = (float *)malloc(m_width * m_height * sizeof(float));
  initialize_matrix(in_matrix, m_width, m_height);
  // print_matrix(in_matrix, m_width, m_height);
  float *out_matrix = (float *)malloc(m_width * m_height * sizeof(float));
  gettimeofday(&start, NULL);
  trans(in_matrix, out_matrix, m_width, m_height, blocksize);
  gettimeofday(&end, NULL);
  printf("Total time = %f seconds\n",
         (double)(end.tv_usec - start.tv_usec) / 1000000 +
             (double)(end.tv_sec - start.tv_sec));
  // printf("\n");
  // print_transpose(out_matrix, m_width, m_height);

  free(in_matrix);
  free(out_matrix);
  return 0;
}
