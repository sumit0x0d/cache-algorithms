#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <lru-cache.h>

int _compare_int(const void *data1, const void *data2, void *uData);
size_t _hash_int(const void *data, const size_t bCount, void *uData);

int main(void)
{
     srand((int)time(NULL));
     int x = 10;
     LruCacheCreateInfo lccInfo = {
          .data_size = sizeof(int),
          .capacity = 100,
          .hash = _hash_int,
          .compare = _compare_int
     };   
     LruCache *lCache = LruCache_Create(&lccInfo);
     LruCache_Insert(lCache, &x);
     return 0;
}

int _compare_int(const void *data1, const void *data2, void *uData)
{
     (void)uData;
     if (*(int *)data1 < *(int *)data2) {
          return -1;
     } else if (*(int *)data1 > *(int *)data2) {
          return 1;
     }
     return 0;
}

size_t _hash_int(const void *data, size_t bCount, void *uData)
{
     (void)uData;
     return *(int *)data % bCount;
}
