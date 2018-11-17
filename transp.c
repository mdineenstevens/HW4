#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  float *out_matrix = (float *)malloc(m_width * m_width * sizeof(float));
  printf("\n");
  // print_matrix(out_matrix, m_width);

  free(in_matrix);
  free(out_matrix);
  return 0;
}
