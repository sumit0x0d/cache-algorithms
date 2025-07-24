#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <stddef.h>

typedef struct lru_cache LruCache;
typedef struct lru_cache_create_info LruCacheCreateInfo;

typedef size_t (*LruCacheHash)(const void *data, const size_t dSize, void *uData);
typedef int (*LruCacheCompare)(const void *data1, const void *data2, void *uData);

struct lru_cache_create_info {
     size_t data_size;
     size_t capacity;
     LruCacheHash hash;
     LruCacheCompare compare;
     void *user_data;
};

LruCache *LruCache_Create(LruCacheCreateInfo *lccInfo);
void LruCache_Destroy(LruCache *lCache);

void LruCache_Insert(LruCache *lCache, void *data);
void *LruCache_Search(LruCache *lCache, void *data);

#endif
