#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

// 定义一个对齐为8字节，大小为9字节的自定义类型
typedef struct {
    unsigned char data[9];
} int72_t __attribute__((aligned(8)));

#pragma pack(1)
// 1字节对齐
typedef union {
    int72_t total_data;
    struct {
        unsigned long long lo : 32;
        unsigned long long lo_h : 4;
        unsigned long long hi : 32;
        unsigned long long hi_h : 4;
    } detail_data;
} TEST_72BIT;
#pragma pack()

void generate_random_txt(char *filename, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        double random_value = (double)rand() / RAND_MAX * 1000; // 生成0到1000之间的随机数
        fprintf(fp, "%lf\n", random_value);
    }

    fclose(fp);
}

void generate_random_bin(char *filename, int count) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    TEST_72BIT test_72bit = {0};
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        double tmp = (double)rand() / RAND_MAX * 1000; // 生成0到1000之间的随机数
        unsigned long long int *p_long_tmp = (unsigned long long int *)&tmp;

        test_72bit.detail_data.hi_h = 0;
        test_72bit.detail_data.lo_h = 0;

        if (tmp < 1e-15) {
            test_72bit.detail_data.lo = 0;
            test_72bit.detail_data.hi = 0x7cc00000;
            test_72bit.detail_data.hi_h = 0x1;
        } else {
            test_72bit.detail_data.lo = (*p_long_tmp) & 0xFFFFFFFF;
            test_72bit.detail_data.hi = (*p_long_tmp) >> 32 & 0xFFFFFFFF;
        }

        fwrite(&test_72bit, sizeof(test_72bit), 1, fp);
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <mode> <output_file> [count]\n", argv[0]);
        fprintf(stderr, "mode: 1 for txt, 2 for bin\n");
        exit(EXIT_FAILURE);
    }

    int mode = atoi(argv[1]);
    char *output_file = argv[2];
    int count = (argc >= 4) ? atoi(argv[3]) : 100; // 默认生成100个随机数

    struct timeval t_start = {0}, t_end = {0};

    gettimeofday(&t_start, NULL);

    if (mode == 1) {
        generate_random_txt(output_file, count);
    } else if (mode == 2) {
        generate_random_bin(output_file, count);
    } else {
        fprintf(stderr, "Invalid mode. Use 1 for txt and 2 for bin.\n");
        exit(EXIT_FAILURE);
    }

    gettimeofday(&t_end, NULL);
    printf("time cost: %ld ms\n", (t_end.tv_sec - t_start.tv_sec) * 1000 + (t_end.tv_usec - t_start.tv_usec) / 1000);
    printf("finished\n");

    return 0;
}