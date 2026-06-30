// FUNC_NAME: HashTable_rehash
// Function address: 0x0065a260
// Rehashes a hash table: flattens old buckets, reallocates bucket array to new size,
// redistributes nodes based on key % new capacity.

// The hash table uses:
// - g_pBucketArray: pointer to array of bucket heads (each a node index, 0 = empty)
// - g_numBuckets: current number of buckets
// - g_pNodeArray: base pointer to node array (each node is 12 bytes: [nodeIdx, nextIdx, key])
// Nodes are stored in a contiguous array; node index is its offset into the array.

#include <cstdlib> // for realloc

// Global variables (inferred from DAT_01205a3c, DAT_01205a34, DAT_01205a38)
extern int g_numBuckets;         // DAT_01205a3c
extern int* g_pNodeArray;        // DAT_01205a34 (base of node array)
extern int* g_pBucketArray;      // DAT_01205a38 (pointer to bucket heads)

// Node structure (inferred):
// struct HashNode {
//     int nodeIdx;    // +0x00 (self index, redundant but stored)
//     int nextIdx;    // +0x04 (next node in chain, 0 = end)
//     int key;        // +0x08
// };

void HashTable_rehash(uint newSize) {
    int currentNodeIdx;
    int nextNodeIdx;
    int* pNode;          // pointer to current node in node array
    int* newBucketArray; // newly allocated bucket array
    uint oldBucketCount;
    uint bucketIdx;
    int flattenedHead;   // head of reversed list of all nodes

    oldBucketCount = g_numBuckets;
    flattenedHead = 0;
    bucketIdx = 0;

    // Step 1: Flatten all nodes from old buckets into a single reversed list.
    if (g_numBuckets != 0) {
        do {
            // Get head of current bucket
            currentNodeIdx = *(int*)((int)g_pBucketArray + bucketIdx * 4);
            
            // Traverse the bucket's chain
            while (nextNodeIdx = currentNodeIdx, nextNodeIdx != 0) {
                // Get pointer to the node at index nextNodeIdx
                pNode = (int*)((int)g_pNodeArray + nextNodeIdx * 4); // each node is 12 bytes? Actually 4*3=12 but they treat as int* and access index, so node size is sizeof(int)*3 = 0xC
                // More precisely: g_pNodeArray is base, each node is at g_pNodeArray + nodeIdx * 12? But they use multiplication by 4, not 12.
                // Actually the access: *(int*)(g_pNodeArray + nodeIdx*4) gets the first int (nodeIdx). So they treat node as array of ints starting at g_pNodeArray.
                // That implies each node consists of three ints packed consecutively. So g_pNodeArray is actually a single array of ints, and node index is the offset in that array divided by 3.
                // Let's keep the original logic: pNode = (int*)((int)g_pNodeArray + nextNodeIdx * 4); then pNode[0], pNode[1], pNode[2] access the three fields.
                // So node size is 12 bytes, but the scaling by 4 offsets to the correct int (since each int is 4 bytes).
                // We'll keep using pointer arithmetic as decompiled.

                currentNodeIdx = *(int*)((int)pNode + 4); // save next node index before overwriting
                *(int*)((int)pNode + 4) = flattenedHead; // set next to previous node (reversing)
                flattenedHead = nextNodeIdx;             // update head of reversed list
            }
            bucketIdx++;
        } while (bucketIdx < oldBucketCount);
    }

    // Step 2: Reallocate bucket array to new size
    newBucketArray = (int*)_realloc(g_pBucketArray, newSize * 4);
    g_pBucketArray = newBucketArray;
    g_numBuckets = newSize;

    // Step 3: Zero out new buckets
    if (newSize != 0) {
        for (uint i = 0; i < newSize; i++) {
            newBucketArray[i] = 0;
        }
    }

    // Step 4: Reinsert all nodes into new buckets based on key % newSize
    while (flattenedHead != 0) {
        pNode = (int*)((int)g_pNodeArray + flattenedHead * 4); // pointer to node
        int nextNodeAfterReversal = pNode[1]; // since we reversed, this is the next in the flattened list (earlier original node)
        int* pNodeFields = pNode; // alias for clarity

        // Compute new bucket index
        uint newBucketIdx = (uint)pNodeFields[2] % newSize; // key % newSize

        // Insert node at head of new bucket
        pNodeFields[1] = newBucketArray[newBucketIdx];      // node->next = old head
        newBucketArray[newBucketIdx] = pNodeFields[0];      // bucket head = node's own index

        flattenedHead = nextNodeAfterReversal;
    }
}