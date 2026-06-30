// FUNC_NAME: BucketManager::pruneBuckets
// Address: 0x004de220
// This function is part of a bucket-based spatial partitioning or culling system.
// It removes items that fall into buckets that have reached the maximum capacity (threshold),
// and then removes those overfull bucket nodes themselves from the doubly linked list.

#include <cstddef>

// Forward declaration of deallocation function (likely operator delete)
void __fastcall deallocateBucket(void* ptr); // actual: FUN_009c8eb0

struct BucketNode {
    BucketNode* prev;      // +0x00: previous node in doubly linked list
    BucketNode* next;      // +0x04: next node
    void* rangeStart;      // +0x08: start of bucket range (pointer comparison)
    void* rangeEnd;        // +0x0c: end of bucket range
    int count;             // +0x10: number of items in this bucket
};

struct ItemNode {
    ItemNode* next;        // +0x00: singly linked list pointer (next item)
    // Additional item data follows
};

class BucketManager {
public:
    // Unknown fields from offset 0x00 to 0x0b
    int totalItemCount;         // +0x0c: total number of items (decremented by threshold when bucket removed)
    int field_0x10;             // +0x10: unknown
    int otherCount;             // +0x14: another count (decremented by threshold when bucket removed)
    int maxCountPerBucket;      // +0x18: threshold – maximum items per bucket
    int bucketCount;            // +0x1c: number of bucket nodes
    // padding?
    BucketNode* bucketHead;    // +0x30: head of doubly linked list of bucket nodes
    ItemNode* itemHead;        // +0x34: head of singly linked list of items

    void __thiscall pruneBuckets();
};

void __thiscall BucketManager::pruneBuckets() {
    BucketNode* bucket;
    ItemNode* item;

    // Step 1: Reset all bucket counters to zero
    for (bucket = bucketHead; bucket != nullptr; bucket = bucket->next) {
        bucket->count = 0;
    }

    // Step 2: For each item, find its containing bucket and increment that bucket's count
    for (item = itemHead; item != nullptr; item = item->next) {
        bucket = bucketHead;
        // Traverse bucket list to find the bucket that contains this item pointer
        bool found = false;
        while (bucket != nullptr && !found) {
            // Check if item pointer falls within the bucket's range
            if (item >= static_cast<ItemNode*>(bucket->rangeStart) &&
                item <= static_cast<ItemNode*>(bucket->rangeEnd)) {
                found = true;
                // break out of loop, bucket is the containing node
            } else {
                bucket = bucket->next;
            }
        }
        if (found) {
            bucket->count++;
        }
    }

    // Step 3: Remove items whose containing bucket has reached the maximum count
    ItemNode** prevItemPtr = &itemHead;
    item = itemHead;
    while (item != nullptr) {
        // Find the bucket for this item again
        bucket = bucketHead;
        bool found = false;
        while (bucket != nullptr && !found) {
            if (item >= static_cast<ItemNode*>(bucket->rangeStart) &&
                item <= static_cast<ItemNode*>(bucket->rangeEnd)) {
                found = true;
            } else {
                bucket = bucket->next;
            }
        }
        if (found && bucket->count == maxCountPerBucket) {
            // Remove this item from the singly linked list
            *prevItemPtr = item->next;
            // Note: item pointer is still valid, but we advance without updating prevItemPtr
        } else {
            prevItemPtr = &(item->next);
        }
        item = item->next;
    }

    // Step 4: Remove bucket nodes that have reached the maximum count
    BucketNode* currentBucket = bucketHead;
    while (currentBucket != nullptr) {
        BucketNode* nextBucket = currentBucket->next;
        if (currentBucket->count == maxCountPerBucket) {
            // Unlink from doubly linked list
            if (currentBucket->prev != nullptr) {
                currentBucket->prev->next = currentBucket->next;
            }
            if (currentBucket->next != nullptr) {
                currentBucket->next->prev = currentBucket->prev;
            }
            if (currentBucket == bucketHead) {
                bucketHead = currentBucket->next;
            }
            // Deallocate the bucket node
            deallocateBucket(currentBucket);
            // Update counters
            bucketCount--;
            totalItemCount -= maxCountPerBucket;
            otherCount -= maxCountPerBucket;
        }
        currentBucket = nextBucket;
    }
}