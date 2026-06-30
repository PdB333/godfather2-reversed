// FUN_00421cb0: HashTable::rehash
// Rehash/resize the hash table to a new size = oldSize * 2 + 1.
// Node structure: key (int, offset 0), next (Node*, offset 4)
// Bucket list array is allocated by customAlloc, freed by customFree.

// Custom allocator/deallocator wrappers (mapped to original functions)
void* customAlloc(size_t size);
void  customFree(void* ptr);

class HashTable {
public:
    struct Node {
        int key;       // +0x00
        Node* next;    // +0x04
    };

    Node** buckets;   // +0x00 (array of bucket heads)
    int    bucketCount; // +0x04 (number of buckets)

    void rehash() {
        int newBucketCount = bucketCount * 2 + 1;
        Node** newBuckets = (Node**)customAlloc(newBucketCount * sizeof(Node*));
        memset(newBuckets, 0, newBucketCount * sizeof(Node*));

        for (int i = 0; i < bucketCount; i++) {
            Node* node = buckets[i];
            while (node) {
                Node* nextNode = node->next;
                int index = node->key % newBucketCount;
                node->next = newBuckets[index];
                newBuckets[index] = node;
                node = nextNode;
            }
        }

        customFree(buckets);
        buckets = newBuckets;
        bucketCount = newBucketCount;
    }
};