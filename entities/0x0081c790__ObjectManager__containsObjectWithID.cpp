// FUNC_NAME: ObjectManager::containsObjectWithID
// Function address: 0x0081c790
// Searches all buckets in a hash table for an object with the given ID.
// The ID is stored as (id + 0x48) in the node, or 0 if none.
// Returns 1 if found, 0 otherwise.

struct LinkedListNode {
    LinkedListNode* next;      // +0x00
    int idOrPointer;           // +0x04  // if non-zero, id = this - 0x48
};

struct ObjectBucket {
    char pad_0x00[0x18];
    LinkedListNode* head;      // +0x18
};

class ObjectManager {
public:
    int bucketCount;           // +0x08
    ObjectBucket** buckets;    // +0x0C

    bool containsObjectWithID(int targetID) {
        int i = 0;
        bool found = false;

        if (bucketCount > 0) {
            do {
                ObjectBucket* bucket = buckets[i];
                LinkedListNode* currentNode = bucket->head;

                while (true) {
                    // Debug assertion: bucket pointer should be consistent
                    ObjectBucket* sameBucket = buckets[i];
                    LinkedListNode* headNode = sameBucket->head;
                    if (bucket != sameBucket) {
                        // FUN_00b97aea(); // assert
                    }

                    if (currentNode == headNode) {
                        break; // wrapped around, bucket empty or fully traversed
                    }

                    // Debug assertion: currentNode should not be head again
                    if (currentNode == bucket->head) {
                        // FUN_00b97aea(); // assert
                    }

                    int id;
                    if (currentNode->idOrPointer == 0) {
                        id = 0;
                    } else {
                        id = currentNode->idOrPointer - 0x48; // stored as id + 0x48
                    }

                    if (id == targetID) {
                        found = true;
                    }

                    // Debug assertion again
                    if (currentNode == bucket->head) {
                        // FUN_00b97aea(); // assert
                    }

                    currentNode = currentNode->next;
                }

                i++;
            } while (i < bucketCount);
        }

        return found;
    }
};