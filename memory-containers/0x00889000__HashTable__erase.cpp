// FUNC_NAME: HashTable::erase
// Address: 0x00889000
// Role: Removes a node from a hash table bucket chain and returns an iterator to the next element.
// The container uses an array of bucket head pointers (param_4). Each node has a 'next' pointer at +0x1C.
// The iterator (param_2) is a pair: [0] = current node pointer, [1] = pointer to bucket head pointer.
// After removal, the iterator is advanced to the next non-empty bucket if the removed node was the last in its bucket.

struct HashTableNode {
    // +0x00: data (unknown)
    // +0x1C: next pointer
    int* next; // offset 0x1C
};

struct HashTableIterator {
    HashTableNode* currentNode; // [0]
    HashTableNode** bucketPtr;  // [1] pointer to the bucket head pointer
};

class HashTable {
public:
    int size; // +0x0C (size counter)

    // Removes 'node' from the bucket chain starting at 'buckets' (array of head pointers).
    // 'iter' is an iterator that will be updated to point to the next element.
    // Returns the updated iterator (same as 'iter').
    HashTableIterator* erase(HashTableIterator* iter, HashTableNode* node, HashTableNode** buckets) {
        HashTableNode* nextNode = node->next; // +0x1C
        iter->currentNode = nextNode;
        iter->bucketPtr = buckets;

        // If the removed node was the last in its bucket, advance to the next non-empty bucket.
        while (nextNode == nullptr) {
            iter->bucketPtr++; // move to next bucket head pointer
            nextNode = *(iter->bucketPtr);
            iter->currentNode = nextNode;
        }

        // Unlink the node from the bucket chain.
        HashTableNode* head = *buckets;
        if (head == node) {
            // Node is the head of the first bucket.
            *buckets = node->next;
        } else {
            // Find the predecessor node.
            HashTableNode* prev = head;
            HashTableNode* curr = head->next;
            while (curr != node) {
                prev = curr;
                curr = curr->next;
            }
            // Unlink: prev->next = node->next
            prev->next = node->next;
        }

        // Destroy the removed node (likely free or destructor).
        destroyNode(node);

        // Decrement size.
        size--;

        return iter;
    }

private:
    void destroyNode(HashTableNode* node); // FUN_009c8f10
};