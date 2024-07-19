#ifndef GEN_NUM_H
#define GEN_NUM_H

/**
 * @brief size 9 Bytes, 8 bytes aligned
 *
 */
typedef struct
{
    unsigned char data[9];
} int72_t __attribute__((aligned(8)));

/**
 * @brief 1 byte alignment
 */
#pragma pack(1)

/**
 * @brief 72bit struct
 *
 */
typedef union
{
    int72_t total_data;
    struct
    {
        unsigned long long lo : 32;
        unsigned long long lo_h : 4;
        unsigned long long hi : 32;
        unsigned long long hi_h : 4;
    } detail_data;
} TEST_72BIT;

/**
 * @brief 64bit struct
 *
 */
typedef union
{
    unsigned long long total_data;
    struct
    {
        unsigned long long lo : 32;
        unsigned long long hi : 32;
    } detail_data;
} TEST_64BIT;
#pragma pack()

/**
 * @brief 生成9bit的随机dat
 * 
 * @param filename 
 * @param count 
 */
void generate_random_dat_72bit(char *filename, int count);

void generate_random_bin_72bit(char *filename, int count);

void generate_random_dat_64bit(char *filename, int count);

void generate_random_bin_64bit(char *filename, int count);

void generate_sequential_dat_72bit(char *filename, int count);

void generate_sequential_bin_72bit(char *filename, int count);

void generate_sequential_dat_64bit(char *filename, int count);

void generate_sequential_bin_64bit(char *filename, int count);

void print_help();

#endif /* GEN_NUM_H */