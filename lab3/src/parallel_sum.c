#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>

struct SumArgs {
  int *array;
  int begin;
  int end;
};

int part = 0;
  uint32_t threads_num = -1; 
  uint32_t array_size = -1;

  int gran = 0;
  int prt;
  int modus;

  int f = 1;

int Sum(const struct SumArgs *args) {
  int sum = 0;
  // TODO: your code here 
   int i = args->begin;
 printf("i:%d beg:%d end:%d\n", i, args->begin, args->end);
    for (; i < args->end; i++) 
        sum += args->array[i]; 
  return sum;
}

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  prt = array_size / threads_num;
    if (f) {
        modus = array_size % threads_num;
        f = 0;
    }
      sum_args->begin = gran;
      sum_args->end = gran + prt + modus;
      gran = sum_args->end;
      modus = 0;
  return (void *)(size_t)Sum(sum_args);
}

int main(int argc, char **argv) {

uint32_t seed = -1;
  uint32_t i;

  while (1) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"nt", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;

    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;
    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            seed = atoi(optarg);

            if (seed <= 0) {
            printf("seed is a positive number\n");
            return 1;
            }
            break;
          case 1:
            array_size = atoi(optarg);

            if (array_size <= 0) {
            printf("array_size is a positive number\n");
            return 1;
            }
            break;
          case 2:
            threads_num = atoi(optarg);

            if (threads_num < 1) {
            printf("at least 1 thread should be started\n");
            return 1;
            }
            break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || threads_num == -1) {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --nt \"num\"\n",
           argv[0]);
    return 1;
  }

  pthread_t threads[threads_num];

  int *array = malloc(sizeof(int) * array_size);


  srand(seed);
	 i = 0;
	while (i < array_size) {
   		array[i] = rand() % 10;
		i++;
  	}


  i = 0;
  for (; i< array_size; i++) {
      printf("%d ", array[i]);
  }
  printf("\n");

  struct SumArgs args[threads_num];
  
  args->array = array;
  for ( i = 0; i < threads_num; i++) {
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args)) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for ( i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    printf("%d - sum:%d\n", i, sum);
    total_sum += sum;
  }

  free(array);
  printf("Total: %d\n", total_sum);
  return 0;
}
