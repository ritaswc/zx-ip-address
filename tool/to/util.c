#include "util.h"
#include <stdint.h>

//intn
const uint64_t i_mask[] = {0,
                   0x1,                0x3,                0x7,                0xF,
                  0x1F,               0x3F,               0x7F,               0xFF,
                 0x1FF,              0x3FF,              0x7FF,              0xFFF,
                0x1FFF,             0x3FFF,             0x7FFF,             0xFFFF,
               0x1FFFF,            0x3FFFF,            0x7FFFF,            0xFFFFF,
              0x1FFFFF,           0x3FFFFF,           0x7FFFFF,           0xFFFFFF,
             0x1FFFFFF,          0x3FFFFFF,          0x7FFFFFF,          0xFFFFFFF,
            0x1FFFFFFF,         0x3FFFFFFF,         0x7FFFFFFF,         0xFFFFFFFF,
           0x1FFFFFFFF,        0x3FFFFFFFF,        0x7FFFFFFFF,        0xFFFFFFFFF,
          0x1FFFFFFFFF,       0x3FFFFFFFFF,       0x7FFFFFFFFF,       0xFFFFFFFFFF,
         0x1FFFFFFFFFF,      0x3FFFFFFFFFF,      0x7FFFFFFFFFF,      0xFFFFFFFFFFF,
        0x1FFFFFFFFFFF,     0x3FFFFFFFFFFF,     0x7FFFFFFFFFFF,     0xFFFFFFFFFFFF,
       0x1FFFFFFFFFFFF,    0x3FFFFFFFFFFFF,    0x7FFFFFFFFFFFF,    0xFFFFFFFFFFFFF,
      0x1FFFFFFFFFFFFF,   0x3FFFFFFFFFFFFF,   0x7FFFFFFFFFFFFF,   0xFFFFFFFFFFFFFF,
     0x1FFFFFFFFFFFFFF,  0x3FFFFFFFFFFFFFF,  0x7FFFFFFFFFFFFFF,  0xFFFFFFFFFFFFFFF,
    0x1FFFFFFFFFFFFFFF, 0x3FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF
};

int64_t intn(void *p, int n){
	if (n >= 8)
		return *(int64_t *)p;
	else
		return (*(int64_t *)p) & i_mask[8 * n];
}

uint64_t uintn(void *p, int n){
	if (n >= 8)
		return *(uint64_t *)p;
	else
		return (*(uint64_t *)p) & i_mask[8 * n];
}

