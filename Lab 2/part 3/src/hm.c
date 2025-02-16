/**
@file hm.h
@brief Implements data structure in C
*/

#include "mythread.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#define SZ 4096

/** 
@struct hashmap_element_s
@brief Structure representing an element in hashmap
*/
struct hashmap_element_s
{
    char* key; /**Key associated with the element*/
    void* data; /** Data stored in the element*/
};
/**
@struct hashmap_s
@brief Structure representing hashmap
*/
struct hashmap_s
{
    struct list* table[SZ]; /** Array of linked lists representing the hash table*/
  struct lock* lk[SZ];    /** Array of locks for each slot in the hash table*/
};

// Initialize a hashmap
/**
@brief Initializes a hashmap
@param out_hashmap Pointer to the hashmap to initialize 
@return 0 if successful,-1 otherwise
*/
int hashmap_create(struct hashmap_s *const out_hashmap){
    if (out_hashmap == NULL)
    {
        return -1;
    }
    for (int i = 0; i < SZ; i++)
    {
        out_hashmap->table[i] = malloc(sizeof(struct hashmap_element_s));
out_hashmap->table[i]->head = NULL;
out_hashmap->table[i]->tail = NULL;
out_hashmap->lk[i] = lock_new();
  }
  return 0;
}   

//Also write your own hashing function
/**
@brief Calculates the hash value of a given string 
@param key Pointer to the string to hash
@return Hash value of the given string 
*/
unsigned int hash_function(const char* key)
{
    unsigned int hash_value = 0;
    int i = 0;
    for (i = 0; i < strlen(key); i++)
    {
        hash_value = hash_value * 26 + key[i];
    }
    return hash_value % SZ;
}

// Set value of the key as data in hashmap. You can use any method to resolve conflicts. 
/**
@brief Adds a key-value pair to the hashmap
@param hashmap Pointer to the hashmap to add the pair to 
@param key Pointer to the key string 
@param data Pointer to the data to store 
@return 0 if successful, -1 otherwise
*/
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data){
    if (key == NULL)
    {
        return -1;
    }

    int hash_val = hash_function(key);
    struct list*first = hashmap->table[hash_val];
struct listentry*p = first->head;
while (p != NULL)
{
      struct hashmap_element_s*ele = (struct hashmap_element_s*)p->data;
if (strcmp(ele->key, key) == 0)
{
    ele->data = data;
    return 0;
}
p = p->next;
    }
  struct hashmap_element_s*ele = (struct hashmap_element_s*)malloc(sizeof(struct hashmap_element_s));
ele->key = strdup(key);
ele->data = data;
struct listentry*new_entry = list_add(hashmap->table[hash_val], ele);
return 0;
} 

// Fetch value of a key from hashmap
/**
@brief Retrieves the data associated with the given key from the hashmap
@param hashmap Pointer to the hashmap to retrieve from
@param key Pointer to the key string
@return Pointer to the data if found,NULL otherwise
*/
void* hashmap_get(struct hashmap_s *const hashmap, const char* key){
    int hash_val = hash_function(key);
  struct list*first = hashmap->table[hash_val];
struct listentry*p = first->head;
while (p != NULL)
{
    struct hashmap_element_s*ele = (struct hashmap_element_s*)p->data;
if (strcmp(ele->key, key) == 0)
{
    return ele->data;
}
p = p->next; 
  }
  return NULL;
}  

// Execute argument function on each key-value pair in hashmap
/**

@brief Iterates over each key-value pair in the hashmap and executes the provided function on each element.
@param hashmap Pointer to the hashmap structure.
@param f Pointer to the function that takes a pointer to a hashmap element and returns an integer.
@return void.
*/
void hashmap_iterator(struct hashmap_s* const hashmap, int (*f)(struct hashmap_element_s *const)){
    for (int i = 0; i < SZ; i++)
    {
    struct list*first = hashmap->table[i];
struct listentry*p = first->head;
while (p != NULL)
{
      struct hashmap_element_s*ele = (struct hashmap_element_s*)p->data;
f(ele);
p = p->next;
    }
  }
}
// Acquire lock on a hashmap slot
/**

@brief Acquires a lock on the bucket where the specified key belongs.
@param hashmap Pointer to the hashmap structure.
@param key The key used to lookup the bucket to be locked.
@return 0 on success, -1 on failure.
*/
int acquire_bucket(struct hashmap_s* const hashmap, const char* key){
    int hash_val = hash_function(key);
  struct lock*ac_lock = hashmap->lk[hash_val];
lock_acquire(ac_lock);
return 0;
}  
// Release acquired lock
/**

@brief Releases the lock previously acquired on the bucket where the specified key belongs.
@param hashmap Pointer to the hashmap structure.
@param key The key used to lookup the bucket to be unlocked.
@return 0 on success, -1 on failure.
*/
int release_bucket(struct hashmap_s* const hashmap, const char* key){
    int hash_val = hash_function(key);
  struct lock*rel_lock = hashmap->lk[hash_val];
lock_release(rel_lock);
return 0;
}  
