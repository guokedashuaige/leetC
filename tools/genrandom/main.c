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

typedef union {
    unsigned long long total_data;
    struct {
        unsigned long long lo : 32;
        unsigned long long hi : 32;
    } detail_data;
} TEST_64BIT;
#pragma pack()

void generate_random_dat_72bit(char *filename, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        // 生成两个36位的随机数
        unsigned long long hi = rand() & 0xFFFFFFFF;
        unsigned long long hi_h = rand() & 0xF;
        unsigned long long lo = rand() & 0xFFFFFFFF;
        unsigned long long lo_h = rand() & 0xF;

        // 打印成16进制格式
         fprintf(fp, "0x%01llx%08llx\n0x%01llx%08llx\n", hi_h, hi, lo_h, lo);
    }

    fclose(fp);
}

void generate_random_bin_72bit(char *filename, int count) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    TEST_72BIT test_72bit = {0};
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        // 生成两个36位的随机数
        test_72bit.detail_data.hi = rand() & 0xFFFFFFFF;
        test_72bit.detail_data.hi_h = rand() & 0xF;
        test_72bit.detail_data.lo = rand() & 0xFFFFFFFF;
        test_72bit.detail_data.lo_h = rand() & 0xF;

        fwrite(&test_72bit, sizeof(test_72bit), 1, fp);
    }

    fclose(fp);
}

void generate_random_dat_64bit(char *filename, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        // 生成两个32位的随机数
        unsigned long long hi = rand() & 0xFFFFFFFF;
        unsigned long long lo = rand() & 0xFFFFFFFF;

        // 打印成16进制格式
         fprintf(fp, "0x%08llx\n0x%08llx\n", hi, lo);
    }

    fclose(fp);
}

void generate_random_bin_64bit(char *filename, int count) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    TEST_64BIT test_64bit = {0};
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        // 生成两个32位的随机数
        test_64bit.detail_data.hi = rand() & 0xFFFFFFFF;
        test_64bit.detail_data.lo = rand() & 0xFFFFFFFF;

        fwrite(&test_64bit, sizeof(test_64bit), 1, fp);
    }

    fclose(fp);
}

void generate_sequential_dat_72bit(char *filename, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (unsigned long long i = 0; i < count; i++) {
        unsigned long long hi = i & 0xFFFFFFFF;
        unsigned long long hi_h = (i >> 32) & 0xF;
        unsigned long long lo = (i >> 36) & 0xFFFFFFFF;
        unsigned long long lo_h = 0; // 68位移出范围，应为0

        fprintf(fp, "0x%01llx%08llx\n0x%01llx%08llx\n", hi_h, hi, lo_h, lo);
    }

    fclose(fp);
}

void generate_sequential_bin_72bit(char *filename, int count) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    TEST_72BIT test_72bit = {0};
    for (unsigned long long i = 0; i < count; i++) {
        test_72bit.detail_data.hi = i & 0xFFFFFFFF;
        test_72bit.detail_data.hi_h = (i >> 32) & 0xF;
        test_72bit.detail_data.lo = (i >> 36) & 0xFFFFFFFF;
        test_72bit.detail_data.lo_h = 0; // 68位移出范围，应为0

        fwrite(&test_72bit, sizeof(test_72bit), 1, fp);
    }

    fclose(fp);
}

void generate_sequential_dat_64bit(char *filename, int count) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (unsigned long long i = 0; i < count; i++) {
        unsigned long long hi = i & 0xFFFFFFFF;
        unsigned long long lo = (i >> 32) & 0xFFFFFFFF;

        fprintf(fp, "0x%08llx\n0x%08llx\n", hi, lo);
    }

    fclose(fp);
}

void generate_sequential_bin_64bit(char *filename, int count) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    TEST_64BIT test_64bit = {0};
    for (unsigned long long i = 0; i < count; i++) {
        test_64bit.detail_data.hi = i & 0xFFFFFFFF;
        test_64bit.detail_data.lo = (i >> 32) & 0xFFFFFFFF;

        fwrite(&test_64bit, sizeof(test_64bit), 1, fp);
    }

    fclose(fp);
}

void print_help() {
    printf("Usage: program <mode> <output_file> [count]\n");
    printf("mode: 1 for 72-bit random dat, 2 for 72-bit random bin, 3 for 64-bit random dat, 4 for 64-bit random bin\n");
    printf("      5 for 72-bit sequential dat, 6 for 72-bit sequential bin, 7 for 64-bit sequential dat, 8 for 64-bit sequential bin\n");
    printf("output_file: The file to write the generated numbers\n");
    printf("count: The number of numbers to generate (default is 100)\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help();
        exit(EXIT_FAILURE);
    }

    if (argc < 3) {
        fprintf(stderr, "Missing required arguments.\n");
        print_help();
        exit(EXIT_FAILURE);
    }

    int mode = atoi(argv[1]);
    char *output_file = argv[2];
    int count = (argc >= 4) ? atoi(argv[3]) : 100; // 默认生成100个随机数或顺序数

    struct timeval t_start = {0}, t_end = {0};

    gettimeofday(&t_start, NULL);

    switch (mode) {
        case 1:
            generate_random_dat_72bit(output_file, count);
            break;
        case 2:
            generate_random_bin_72bit(output_file, count);
            break;
        case 3:
            generate_random_dat_64bit(output_file, count);
            break;
        case 4:
            generate_random_bin_64bit(output_file, count);
            break;
        case 5:
            generate_sequential_dat_72bit(output_file, count);
            break;
        case 6:
            generate_sequential_bin_72bit(output_file, count);
            break;
        case 7:
            generate_sequential_dat_64bit(output_file, count);
            break;
        case 8:
            generate_sequential_bin_64bit(output_file, count);
            break;
        default:
            fprintf(stderr, "Invalid mode.\n");
            print_help();
            exit(EXIT_FAILURE);
    }

    gettimeofday(&t_end, NULL);
    printf("time cost: %ld ms\n", (t_end.tv_sec - t_start.tv_sec) * 1000 + (t_end.tv_usec - t_start.tv_usec) / 1000);
    printf("finished\n");

    return 0;
}