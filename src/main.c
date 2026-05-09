#include <stdio.h>

#include <stdint.h>

#include <math.h>

const uint32_t expml_table_size = 12;
#define feature_num 3
#define class_num 2

typedef enum entity {
  CAT,
  DOG
}
Entitys;

typedef float features[feature_num]; //bark, meows, purrs

typedef struct {
  Entitys e;
  features f; //bark, meows, purrs
}
Table;

int main() {

  Table expml_table[] = {
    {CAT, 0, 1, 1},
    {CAT, 0, 0, 0},
    {CAT, 0, 1, 0},
    {DOG, 1, 0, 0},
    {DOG, 1, 0, 0},
    {DOG, 1, 0, 1},
    {DOG, 1, 0, 0},
    {DOG, 0, 0, 0},
    {DOG, 1, 0, 0},
    {CAT, 0, 1, 1},
    {CAT, 0, 0, 1},
    {CAT, 0, 1, 0}
  };

  features multi_data[class_num] = {
    {
      0.0f
    },
    {
      0.0f
    }
  };
  float class_count[class_num] = {
    0
  };

  for (uint32_t i = 0; i < expml_table_size; i++) {
    class_count[expml_table[i].e]++;
    for (int j = 0; j < feature_num; j++) {
      multi_data[expml_table[i].e][j] += expml_table[i].f[j];
    }
  }

  for (int i = 0; i < class_num; i++) {
    for (int j = 0; j < feature_num; j++) {
      multi_data[i][j] /= expml_table_size;
    }
    class_count[i] /= expml_table_size;
  }

  features testf = {
    1,
    0,
    0
  };
  float classpred[class_num] = {
    0
  };

  for (int i = 0; i < class_num; i++) {
    for (int j = 0; j < feature_num; j++) {
      float res = multi_data[i][j];
      if (testf[j] == 0)
        res = class_count[i] - multi_data[i][j];
      if (res < 1e-12)
        res = 1e-12;
      classpred[i] += log(res);
    }
  }
  for (int i = 0; i < class_num; i++) {
    classpred[i] -= (feature_num - 1) * log(class_count[i]);
  }

  for (int i = 0; i < class_num; i++) {
    classpred[i] = exp(classpred[i]);
  }

  printf("CAT do %f \n", classpred[0]);
  printf("DOG do %f \n", classpred[1]);

}