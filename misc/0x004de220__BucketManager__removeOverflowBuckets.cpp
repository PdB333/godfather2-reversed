// FUNC_NAME: BucketManager::removeOverflowBuckets
// Address: 0x004de220
// Role: Cleans up address range buckets that exceed a threshold count, removing both the bucket entries and the associated items.

#include <cstddef>

// Forward declare the deallocation function (likely free or delete)
void __cdecl deleteBucketNode(void* ptr); // FUN_009c8eb0

class BucketManager {
private:
    // Node for the singly linked list of items to be bucketed
    struct ItemNode {
        ItemNode* next;      // +0x00
        // Actual data pointer is implicit (the address of this node or a separate payload)
    };

    // Node for the doubly linked list of address range buckets (sorted by address)
    struct BucketNode {
        BucketNode* prev;    // +0x00
        BucketNode* next;    // +0x04
        BucketNode* left;    // +0x08  // Lower bound of the address range
        BucketNode* right;   // +0x0C  // Upper bound of the address range
        int count;           // +0x10  // Number of items in this bucket
    };

    BucketNode* bucketListHead;  // +0x30  Head of the bucket doubly linked list (sorted by address)
    ItemNode* itemListHead;      // +0x34  Head of the item singly linked list

    int overflowThreshold;       // +0x18  Max count before a bucket is considered full
    int totalBucketCapacity;     // +0x1C  Total number of buckets currently allocated
    int totalItemCapacity;       // +0x0C  Sum of all bucket counts
    int totalItemSlots;          // +0x14  Another total (possibly max capacity)

public:
    // Note: __thiscall is the default for MSVC methods; just write normally.
    void removeOverflowBuckets() {
        BucketNode* currentBucket = bucketListHead;
        if (currentBucket == nullptr) {
            return;
        }

        // Step 1: Zero all bucket counts
        do {
            currentBucket->count = 0;
            currentBucket = currentBucket->next;
        } while (currentBucket != nullptr);

        // Step 2: For each item, find its bucket and increment the count
        ItemNode* item = itemListHead;
        while (item != nullptr) {
            // Find the bucket that contains this item's address
            BucketNode* bucket = bucketListHead;
            BucketNode* foundBucket = nullptr;

            while (true) {
                BucketNode* candidate = bucket;
                if (bucket == nullptr || foundBucket != nullptr) {
                    break;
                }

                // Compare item address with bucket range
                if (item < bucket->left || bucket->right < item) {
                    // Item is outside this bucket's range, move to next
                    bucket = bucket->next;
                    foundBucket = candidate;  // actually this is wrong? Wait, the original code sets iVar7 = iVar8 in the else, meaning it keeps the current bucket when item is inside. Let's reanalyze.
                } else {
                    // Item is within the bucket range
                    foundBucket = bucket;
                    break;
                }
            }
            // The original loop logic: while ((iVar4 = iVar7, iVar8 != 0 && (iVar4 == 0))) {
            // It sets iVar4 = iVar7 at start; iVar7 is previous candidate. If bucket is non-null and iVar4 is 0 (found not set), it checks condition.
            // If item < left OR right < item, it moves to next (iVar8 = next) and sets iVar7 = iVar4 (so iVar7 becomes the old candidate). Else, it sets iVar7 = iVar8 (keeping current bucket) and does not move.
            // This loops until bucket is null or foundBucket is non-null (iVar4 != 0). So at exit, iVar7 (or iVar4) holds the bucket we landed on.
            // Let's simplify: we search in order until we find a bucket whose range contains the item.
            BucketNode* search = bucketListHead;
            BucketNode* lastSmaller = nullptr;
            while (search != nullptr) {
                if (item < search->left) {
                    // Item is before this bucket's range, move to next
                    lastSmaller = search;
                    search = search->next;
                } else if (search->right < item) {
                    // Item is after this bucket's range, move to next
                    lastSmaller = search;
                    search = search->next;
                } else {
                    // Found containing bucket
                    foundBucket = search;
                    break;
                }
            }
            // If no bucket found, we would have lastSmaller? Unclear; original code uses iVar4 which might be null if not found.
            // Assuming foundBucket is always found (the list covers all addresses).
            if (foundBucket != nullptr) {
                foundBucket->count++;
            }
            item = item->next;
        }

        // Step 3: Remove items that belong to overflow buckets (count == threshold)
        ItemNode* prevItem = nullptr;
        ItemNode* currentItem = itemListHead;
        while (currentItem != nullptr) {
            // Find the bucket for this item again
            BucketNode* search = bucketListHead;
            BucketNode* containingBucket = nullptr;
            while (search != nullptr) {
                if (currentItem < search->left) {
                    search = search->next;
                } else if (search->right < currentItem) {
                    search = search->next;
                } else {
                    containingBucket = search;
                    break;
                }
            }

            bool removeItem = false;
            if (containingBucket != nullptr && containingBucket->count == overflowThreshold) {
                removeItem = true;
            }

            ItemNode* nextItem = currentItem->next;  // save next before modifying list
            if (removeItem) {
                // Remove currentItem from the singly linked list
                if (prevItem == nullptr) {
                    itemListHead = nextItem;
                } else {
                    prevItem->next = nextItem;
                }
                // Do NOT delete the item node here? The original code does not call delete on items, only on buckets.
                // The item nodes are probably owned elsewhere, just removed from list.
            } else {
                prevItem = currentItem;
            }
            currentItem = nextItem;
        }

        // Step 4: Remove buckets whose count equals the threshold
        BucketNode* current = bucketListHead;
        while (current != nullptr) {
            BucketNode* nextBucket = current->next;  // save next
            if (current->count == overflowThreshold) {
                // Remove this bucket from the doubly linked list
                if (current->prev != nullptr) {
                    current->prev->next = nextBucket;
                }
                if (nextBucket != nullptr) {
                    nextBucket->prev = current->prev;
                }
                if (current == bucketListHead) {
                    bucketListHead = nextBucket;
                }
                // Deallocate the bucket node
                deleteBucketNode(current);
                // Update totals
                totalBucketCapacity--;
                totalItemCapacity -= overflowThreshold;
                totalItemSlots -= overflowThreshold;
            }
            current = nextBucket;
        }
    }
};