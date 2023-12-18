#include <stdio.h>
#include <stdlib.h>

#ifndef __log
#define __log

#define LOGI(...) fprintf(stdout, "[INFO] "); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n")
#define LOGW(...) fprintf(stdout, "[WARN] "); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n")
#define LOGE(...) fprintf(stderr, "[ERROR] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#define LOGF(...) fprintf(stderr, "[FATAL] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); exit(1)

#endif