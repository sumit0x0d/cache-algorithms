#include <stdlib.h>
#include <string.h>

#include <lru-cache.h>

struct lru_cache {
     DoublyLinkedList *doubly_linked_list;
     HashTable *hash_table;
     size_t capacity;
};

LruCache *LruCache_Create(LruCacheCreateInfo *create_info)
{
     LruCache *cache;
     
     cache = (LruCache *)malloc(sizeof (LruCache));
     if (cache) {
          return NULL;
     }
     
     cache->doubly_linked_list = DoublyLinkedList_Create(create_info->data_size);
     cache->capacity = create_info->capacity * create_info->capacity;
     cache->hash_table = HashTable_Create(create_info->data_size, sizeof (DoublyLinkedListNode *),
          cache->capacity, create_info->hash_callback, create_info->compare_callback);

     return cache;
}

void LruCache_Destroy(LruCache *cache)
{
     HashTable_Destroy(cache->hash_table);
     DoublyLinkedList_Destroy(cache->doubly_linked_list);
     free(cache);
}

void LruCache_Insert(LruCache *cache, void *data)
{
     HashTablePair *pair;
     DoublyLinkedListNode *node;
     void *key;
     
     key = data;
     pair = HashTable_Search(cache->hash_table, key);

     if (pair) {
          node = HashTable_GetValue(pair);
          DoublyLinkedList_RemoveNode(cache->doubly_linked_list, node);
     }
     
     DoublyLinkedList_PushHead(cache->doubly_linked_list, data);
     HashTable_Insert(cache->hash_table, data, DoublyLinkedList_GetHead(cache->doubly_linked_list));
     
     if (DoublyLinkedList_GetSize(cache->doubly_linked_list) == cache->capacity) {
          node = DoublyLinkedList_GetTail(cache->doubly_linked_list);
          key = DoublyLinkedList_GetNodeData(node);
          HashTable_Remove(cache->hash_table, key);
          DoublyLinkedList_PopTail(cache->doubly_linked_list);
     }
}

void *LruCache_Search(LruCache *cache, void *data)
{    
     return HashTable_GetKey(HashTable_Search(cache->hash_table, data));
}