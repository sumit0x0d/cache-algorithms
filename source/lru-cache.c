#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <doubly-linked-list.h>
#include <hash-table.h>
#include <lru-cache.h>

typedef LruCacheCreateInfo CreateInfo;
typedef LruCacheHash Hash;
typedef LruCacheCompare Compare;

struct lru_cache {
     DoublyLinkedList *doubly_linked_list;
     HashTable *hash_table;
     void *user_data;
     size_t capacity;
};

LruCache *LruCache_Create(CreateInfo *cInfo)
{
     LruCache *lCache = (LruCache *)malloc(sizeof (LruCache));
     assert(lCache);
     lCache->doubly_linked_list = DoublyLinkedList_Create(cInfo->data_size);
     lCache->hash_table = HashTable_Create(cInfo->data_size, sizeof(DoublyLinkedListNode *), cInfo->capacity * cInfo->capacity, cInfo->hash,
                                           cInfo->compare, NULL);
     lCache->user_data = cInfo->user_data;
     lCache->capacity = cInfo->capacity;
     return lCache;
}

void LruCache_Destroy(LruCache *lCache)
{
     HashTable_Destroy(lCache->hash_table);
     DoublyLinkedList_Destroy(lCache->doubly_linked_list);
     free(lCache);
}

void LruCache_Insert(LruCache *lCache, void *data)
{
     HashTablePair *htPair = HashTable_Search(lCache->hash_table, data);
     if (htPair) {
          void *value = HashTablePair_GetValue(htPair);
          DoublyLinkedList_Remove(lCache->doubly_linked_list, value);
     }
     DoublyLinkedList_PushHead(lCache->doubly_linked_list, data);
     DoublyLinkedListNode *hdllNode = DoublyLinkedList_GetHead(lCache->doubly_linked_list);
     HashTable_Insert(lCache->hash_table, data, hdllNode);
     if (DoublyLinkedList_GetSize(lCache->doubly_linked_list) == lCache->capacity) {
          DoublyLinkedListNode *tdllNode = DoublyLinkedList_GetTail(lCache->doubly_linked_list);
          void *key = DoublyLinkedListNode_GetData(tdllNode);
          HashTable_Remove(lCache->hash_table, key);
          DoublyLinkedList_PopTail(lCache->doubly_linked_list);
          return;
     }
}

void *LruCache_Search(LruCache *lCache, void *data)
{
     HashTablePair *htPair = HashTable_Search(lCache->hash_table, data);
     return HashTablePair_GetKey(htPair);
}
