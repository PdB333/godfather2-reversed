// FUNC_NAME: PriorityPool::pop
// Address: 0x0051f960
// Role: Pops an object from the pool. First tries a fast free-list at +0x474. If empty, evicts
//       the bucket with the highest priority score (float at object+0x14), removes the first
//       object from that bucket's internal doubly-linked list (head at bucket+0x14, tail at +0x1c),
//       and returns it. The removed object's destructor (vtable+4) is called before return.
// Pool layout (relative to this):
//   +0x04: head of bucket linked list
//   +0x0c: tail of bucket linked list
//   +0x474: head of free-list of objects (single-linked via +0x40)
// Bucket layout (int*):
//   +0x14: pointer to first object in internal list (if != +0x1c)
//   +0x1c: end marker (tail) for internal list
//   +0x2c: next bucket in list
// Object layout (int*):
//   [0]: vtable pointer
//   [1]: virtual destructor (offset 4)
//   +0x14: float priority score (used for eviction)
//   +0x40: next pointer (in free list or internal list)
//   +0x44: prev pointer (internal list only)

#include <cstdint>

class PriorityPool {
public:
    // Object structure (first fields)
    struct PoolObject {
        void** vtable;      // +0x00
        // virtual dtor at +0x04
        float priority;     // +0x14
        PoolObject* next;   // +0x40
        PoolObject* prev;   // +0x44
    };

    // Bucket structure (holds a doubly-linked sublist of objects with same priority)
    struct Bucket {
        uint8_t pad_0x00[0x14]; // unknown
        PoolObject* head;   // +0x14
        PoolObject* tail;   // +0x1c (sentinel, not necessarily null)
        uint8_t pad_0x20[0x0C]; // padding to next pointer at +0x2c?
        Bucket* next;       // +0x2c
    };

    // Pool members
    Bucket* bucketHead;     // +0x04
    Bucket* bucketTail;     // +0x0c (used as loop end)
    // ... other fields until +0x474
    PoolObject* freeList;   // +0x474

    // Pop one object, evicting if necessary
    PoolObject* pop() {
        PoolObject* obj;

        // Fast path: pop from free list
        obj = this->freeList;
        if (obj != nullptr) {
            this->freeList = obj->next;
            return obj;
        }

        // No free object; find the bucket with the highest priority object
        Bucket* bestBucket = nullptr;
        float bestPriority = 0.0f; // initial value from global? Assume 0
        Bucket* cur = this->bucketHead;
        Bucket* tail = this->bucketTail;

        // Global constants (likely 0.0f or -inf)
        const float initScore = 0.0f; // DAT_00e2eff4

        while (cur != tail) {
            float score = initScore;
            // If bucket has at least one object, get its priority
            if (cur->head != cur->tail) {
                score = cur->head->priority;
            }
            if (bestPriority < score) {
                bestBucket = cur;
                bestPriority = score;
            }
            cur = cur->next;
        }

        // If we found a bucket with objects, evict and return its first object
        if (bestBucket != nullptr && bestBucket->head != bestBucket->tail && bestBucket->head != nullptr) {
            PoolObject* victim = bestBucket->head;

            // Remove victim from bucket's internal doubly linked list
            if (victim->prev != nullptr) {
                victim->prev->next = victim->next;
            } else {
                // victim is head, update bucket head
                bestBucket->head = victim->next;
            }
            if (victim->next != nullptr) {
                victim->next->prev = victim->prev;
            } else {
                // victim is tail, update bucket tail
                bestBucket->tail = victim->prev;
            }

            // Call destructor (vtable+4) on the victim
            // (The function does not actually destroy it, but calls something)
            // Assuming the vtable has a function at offset 4
            void (*destroy)(PoolObject*) = (void (*)(PoolObject*))victim->vtable[1];
            destroy(victim);

            return victim;
        }

        // No object available
        return nullptr;
    }
};