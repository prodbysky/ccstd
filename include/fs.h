#ifndef CCSTD_FS_H_
#define CCSTD_FS_H_

#include <prelude.h>
#include <stdint.h>
typedef struct {
    const char* name;
    uint64_t len;
    CCS_FILE_HANDLE file;
} File;

File File_open(const char* name);
#endif
