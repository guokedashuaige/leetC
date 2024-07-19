#include "gennum.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

long parse_count(const char *str) {
    char *endptr;
    errno = 0; // To distinguish success/failure after call
    long val = strtol(str, &endptr, 0);

    // Check for various possible errors
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) ||
        (errno != 0 && val == 0)) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == str) {
        fprintf(stderr, "No digits were found in count\n");
        exit(EXIT_FAILURE);
    }

    // If we end up here, strtol() successfully parsed a number
    return val;
}

int main(int argc, char *argv[]) {
    // Check if the user wants help
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_help();
        exit(EXIT_SUCCESS);
    }

    if (argc < 3) {
        fprintf(stderr, "Missing required arguments.\n");
        print_help();
        exit(EXIT_FAILURE);
    }

    // Get mode from arguments
    int mode = (int)strtol(argv[1], NULL, 10);
    if (mode < 1 || mode > 8) {
        fprintf(stderr, "Invalid mode selected. Please choose between 1 and 8.\n");
        exit(EXIT_FAILURE);
    }

    // Get output file from arguments
    char *output_file = strdup(argv[2]);
    if (!output_file) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Get count from arguments or default to 100
    long count = (argc > 3) ? parse_count(argv[3]) : 100;

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
            free(output_file);
            exit(EXIT_FAILURE);
    }

    gettimeofday(&t_end, NULL);
    printf("time cost: %ld ms\n", (t_end.tv_sec - t_start.tv_sec) * 1000 +
                                      (t_end.tv_usec - t_start.tv_usec) / 1000);

    printf("Mode: %d\n", mode);
    printf("Output file: %s\n", output_file);
    printf("Count: %ld\n", count);

    free(output_file);
    printf("finished\n");

    return 0;
}