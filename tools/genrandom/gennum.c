#include "gennum.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

void generate_random_dat_72bit(char *filename, int count)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < count; i++)
    {
        unsigned long long hi = rand() & 0xFFFFFFFF;
        unsigned long long hi_h = rand() & 0x7; // Ensure only high 3 bits are used
        unsigned long long lo = rand() & 0xFFFFFFFF;
        unsigned long long lo_h = rand() & 0x7; // Ensure only high 3 bits are used

        fprintf(fp, "0x%01llx%08llx\n0x%01llx%08llx\n", hi_h, hi, lo_h, lo);
    }

    fclose(fp);
}

void generate_random_bin_72bit(char *filename, int count)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    TEST_72BIT test_72bit = {0};
    srand(time(NULL));
    for (int i = 0; i < count; i++)
    {
        test_72bit.detail_data.hi = rand() & 0xFFFFFFFF;
        test_72bit.detail_data.hi_h = rand() & 0x7;
        test_72bit.detail_data.lo = rand() & 0xFFFFFFFF;
        test_72bit.detail_data.lo_h = rand() & 0x7;

        fwrite(&test_72bit, sizeof(test_72bit), 1, fp);
    }

    fclose(fp);
}

void generate_random_dat_64bit(char *filename, int count)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < count; i++)
    {
        unsigned long long hi = rand() & 0xFFFFFFFF;
        unsigned long long lo = rand() & 0xFFFFFFFF;

        fprintf(fp, "0x%08llx\n0x%08llx\n", hi, lo);
    }

    fclose(fp);
}

void generate_random_bin_64bit(char *filename, int count)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    TEST_64BIT test_64bit = {0};
    srand(time(NULL));
    for (int i = 0; i < count; i++)
    {
        test_64bit.detail_data.hi = rand() & 0xFFFFFFFF;
        test_64bit.detail_data.lo = rand() & 0xFFFFFFFF;

        fwrite(&test_64bit, sizeof(test_64bit), 1, fp);
    }

    fclose(fp);
}

void generate_sequential_dat_72bit(char *filename, int count)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (unsigned long long i = 0; i < count; i++)
    {
        unsigned long long hi = i & 0xFFFFFFFF;
        unsigned long long hi_h = (i >> 32) & 0xF;
        unsigned long long lo = (i >> 36) & 0xFFFFFFFF;
        unsigned long long lo_h = 0;

        fprintf(fp, "0x%01llx%08llx\n0x%01llx%08llx\n", hi_h, hi, lo_h, lo);
    }

    fclose(fp);
}

void generate_sequential_bin_72bit(char *filename, int count)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    TEST_72BIT test_72bit = {0};
    for (unsigned long long i = 0; i < count; i++)
    {
        test_72bit.detail_data.hi = i & 0xFFFFFFFF;
        test_72bit.detail_data.hi_h = (i >> 32) & 0xF;
        test_72bit.detail_data.lo = (i >> 36) & 0xFFFFFFFF;
        test_72bit.detail_data.lo_h = 0;

        fwrite(&test_72bit, sizeof(test_72bit), 1, fp);
    }

    fclose(fp);
}

void generate_sequential_dat_64bit(char *filename, int count)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (unsigned long long i = 0; i < count; i++)
    {
        unsigned long long hi = i & 0xFFFFFFFF;
        unsigned long long lo = (i >> 32) & 0xFFFFFFFF;

        fprintf(fp, "0x%08llx\n0x%08llx\n", hi, lo);
    }

    fclose(fp);
}

void generate_sequential_bin_64bit(char *filename, int count)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    TEST_64BIT test_64bit = {0};
    for (unsigned long long i = 0; i < count; i++)
    {
        test_64bit.detail_data.hi = i & 0xFFFFFFFF;
        test_64bit.detail_data.lo = (i >> 32) & 0xFFFFFFFF;

        fwrite(&test_64bit, sizeof(test_64bit), 1, fp);
    }

    fclose(fp);
}

void print_help()
{
    printf("Usage: program_name <mode> <output_file> [count]\n");
    printf("  <mode>         : Mode of operation\n");
    printf("                   1 - Generate random numbers (72-bit, .dat)\n");
    printf("                   2 - Generate random numbers (72-bit, .bin)\n");
    printf("                   3 - Generate random numbers (64-bit, .dat)\n");
    printf("                   4 - Generate random numbers (64-bit, .bin)\n");
    printf("                   5 - Generate sequential numbers (72-bit, .dat)\n");
    printf("                   6 - Generate sequential numbers (72-bit, .bin)\n");
    printf("                   7 - Generate sequential numbers (64-bit, .dat)\n");
    printf("                   8 - Generate sequential numbers (64-bit, .bin)\n");
    printf("  <output_file>  : File to output the results\n");
    printf("  [count]        : Number of items to generate (default is 100)\n");
    printf("Options:\n");
    printf("  -h, --help     : Display this help message\n");
}