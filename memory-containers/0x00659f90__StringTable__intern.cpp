// FUNC_NAME: StringTable::intern
// Address: 0x00659f90
// This function implements a string interning (hash table with chaining) for deduplicating strings.
// It takes a string and its length (passed in EDI), returns a unique integer ID (node index).
// The table automatically resizes when load factor exceeds 0.5.

#include <cstring>
#include <cstdlib>

// Node structure stored in the pool
struct StringNode {
    uint id;          // +0x00: node index (same as position in pool)
    uint next;        // +0x04: linked list next index (0 = end)
    uint hash;        // +0x08: hash value of string
    short length;     // +0x0C: string length
    short refCount;   // +0x0E: reference count (incremented on lookup)
    char string[1];   // +0x10: null-terminated string (flexible array)
};

class StringTable {
public:
    static uint intern(const char* str, size_t len) {
        if (!str || *str == '\0' || len == 0)
            return 0;

        // Initialize hash table if first time
        if (hashTable == nullptr)
            initialize();

        uint hash = computeHash();
        uint bucketIndex = hash % tableSize;
        uint* pBucket = &hashTable[bucketIndex];
        uint nodeIdx = *pBucket;

        uint currentCapacity = nodeArrayCapacity; // could be modified in loop (used as a counter)

        while (true) {
            nodeArrayCapacity = currentCapacity; // sync back? This appears to be for concurrency tracking

            if (nodeIdx == 0) {
                // Bucket empty: allocate new node
                if (freeListHead == 0) {
                    // Grow the node array
                    uint newCapacity = currentCapacity + 0x800;
                    nodeArrayCapacity = newCapacity;
                    void* newArray = realloc(nodeArrayPointer, newCapacity * sizeof(StringNode*));
                    nodeArrayPointer = newArray;

                    // Initialize free list for new slots
                    if (currentCapacity < newCapacity) {
                        uint prev = currentCapacity * 2;
                        uint idx = currentCapacity;
                        do {
                            prev += 2;
                            ((uint*)newArray)[idx] = prev | 1; // mark as free
                            idx++;
                        } while (idx < newCapacity);
                    }
                    // Terminate free list
                    ((uint*)newArray)[newCapacity - 1] = 0;
                    freeListHead = (currentCapacity * 2) | 1;
                }

                // Allocate a new StringNode
                uint newNodeIdx = freeListHead >> 1;
                void* rawNode = allocateNode(len + 0x14); // size = 0x14 + len
                StringNode* node = (StringNode*)rawNode;

                // Fill node fields
                node->id = newNodeIdx;
                node->next = 0;
                node->hash = hash;
                node->length = (short)len;
                node->refCount = 1;
                // Insert into bucket
                *pBucket = newNodeIdx;
                // Update free list
                freeListHead = *(uint*)((uint*)nodeArrayPointer + newNodeIdx);
                // Store pointer to node in array
                ((uint**)nodeArrayPointer)[node->id] = (uint*)node;
                // Copy string
                strncpy(node->string, str, len);
                node->string[len] = '\0';

                totalNodes++;
                // Rehash if load factor > 0.5
                if (tableSize * 2 < totalNodes) {
                    rehash(tableSize * 4 - 1); // approximate new size
                }

                return node->id;
            }

            // Traverse chain
            StringNode* currentNode = (StringNode*)((uint*)nodeArrayPointer)[nodeIdx];
            int cmp = strncmp(currentNode->string, str, len);
            if (cmp == 0 && currentNode->string[len] == '\0') {
                // Found existing string
                currentNode->refCount++;
                return nodeIdx; // return the node index
            }
            // Move to next
            pBucket = &currentNode->next;
            nodeIdx = currentNode->next;
            currentCapacity = nodeArrayCapacity;
        }
    }

private:
    static uint* hashTable;             // DAT_01205a38: pointer to bucket heads (table of indices)
    static uint  tableSize;             // DAT_01205a3c: number of buckets
    static uint  nodeArrayCapacity;     // DAT_01205a40: total slots in node array
    static uint  freeListHead;          // DAT_01205a44: free list head (bit0=1 means free)
    static void* nodeArrayPointer;      // DAT_01205a34: pointer to array of StringNode*
    static uint  totalNodes;            // DAT_01205a48: number of nodes currently in use

    static void initialize();
    static uint computeHash();
    static void* allocateNode(size_t size);
    static void rehash(uint newSize);
};

// Static definitions (actual addresses from decompilation)
uint* StringTable::hashTable = (uint*)0x01205a38;
uint  StringTable::tableSize = *(uint*)0x01205a3c;
uint  StringTable::nodeArrayCapacity = *(uint*)0x01205a40;
uint  StringTable::freeListHead = *(uint*)0x01205a44;
void* StringTable::nodeArrayPointer = (void*)0x01205a34;
uint  StringTable::totalNodes = *(uint*)0x01205a48;