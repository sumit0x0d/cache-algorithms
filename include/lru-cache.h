#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <stddef.h>

#include <doubly-linked-list.h>
#include <hash-table.h>

typedef struct lru_cache LruCache;
typedef struct LruCacheCreateInfo LruCacheCreateInfo;

struct LruCacheCreateInfo {
     size_t data_size;
     size_t capacity;
     HashTableHashCallback hash_callback;
     HashTableCompareCallback compare_callback;
};

LruCache *LruCache_Create(LruCacheCreateInfo *create_info);
void LruCache_Destroy(LruCache *lru_cache);

void LruCache_Insert(LruCache *lru_cache, void *data);
void *LruCache_Search(LruCache *lru_cache, void *data);

#endif