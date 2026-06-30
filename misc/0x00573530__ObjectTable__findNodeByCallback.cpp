// FUNC_NAME: ObjectTable::findNodeByCallback
// Address: 0x00573530
// Iterates over all nodes (linked list then array buckets) using a callback.
// Callback receives node data, key, and userData; returns true (bit0 set) to stop iteration.
// Returns index of found node, or -1.

typedef unsigned int uint;

// Node structure (16 bytes): data pointer, flags, key, next pointer
struct Node {
    void* data;    // +0x00
    uint flags;    // +0x04
    uint key;      // +0x08
    Node* next;    // +0x0C
};

// Bucket array structure at this+0x30
struct BucketArray {
    Node** buckets; // +0x00 : array of node pointers
    int count;      // +0x04 : number of buckets
};

// Callback type returns non-zero (bit0 set) if node matches.
typedef uint (__cdecl *FindCallback)(void* data, uint key, void* userData);

// Initialize iteration state (sets head node pointer and bucket index)
// Implemented elsewhere (FUN_00573aa0)
extern void startIteration(Node*& head, int& bucketIndex);

int __thiscall ObjectTable::findNodeByCallback(FindCallback callback, void* userData) {
    int index = 0;
    BucketArray* bucketArray = *(BucketArray**)(this + 0x30);
    Node* node = nullptr;
    int bucketIndex = 0;

    // Initialise iteration – sets 'node' to head of primary linked list,
    // and 'bucketIndex' to 0.
    startIteration(node, bucketIndex); // FUN_00573aa0

    if (node != nullptr) {
        do {
            // Traverse current linked list until callback matches, or list exhausted
            while (true) {
                // Call the predicate
                uint result = callback(node->data, node->key, userData);
                if ((result & 1) != 0) {
                    return index;
                }
                node = node->next;
                ++index;

                // If no bucket array exists, we cannot refill node from array -> break
                if (bucketArray == nullptr) {
                    break;
                }
                // When linked list runs out, try to get next node from bucket array
                if (node == nullptr) {
                    // Find next non-null bucket entry
                    do {
                        if (bucketArray->count <= bucketIndex) {
                            goto end_of_iteration;
                        }
                        node = bucketArray->buckets[bucketIndex];
                        ++bucketIndex;
                    } while (node == nullptr);
                }
            }
end_of_iteration:
            // If we broke out of the inner loop because bucketArray was null
            // and node became null, node is null so the do-while condition fails.
            ;
        } while (node != nullptr);
    }
    return -1;
}