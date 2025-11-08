#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <lru-cache.h>

HashTableCompare _CompareInt(const void *data1, const void *data2, void *user_data);
size_t _HashInt(const void *data, const size_t bucket_count, void *user_data);

int main(void)
{
     srand((int)time(NULL));
     int x = 10;
     LruCacheCreateInfo lccInfo = {
          .data_size = sizeof(int),
          .capacity = 100,
          .hash_callback = {
               .function = _HashInt,
               .user_data = NULL
          },
          .compare_callback = {
               .function = _CompareInt,
               .user_data = NULL
          }
     };
     LruCache *lCache = LruCache_Create(&lccInfo);
     LruCache_Insert(lCache, &x);
     return 0;
}

int _CompareInt(const void *data1, const void *data2, void *user_data)
{
     (void)user_data;
     if (*(int *)data1 < *(int *)data2) {
          return -1;
     } else if (*(int *)data1 > *(int *)data2) {
          return 1;
     }
     return 0;
}

size_t _HashInt(const void *data, size_t bucket_count, void *user_data)
{
     (void)user_data;
     return *(int *)data % bucket_count;
}
