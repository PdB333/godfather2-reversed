// FUNC_NAME: HandleManager::acquireOrCreateHandle
#include <cstdint>

// Global handle management tables
// Base address of bucket heads (0x1000 entries, each 4 bytes pointer)
extern uint8_t* g_handleBucketBase; // DAT_012058e0
// Offset from g_handleBucketBase to total count (stored at +0x4000)
extern int32_t* g_handleTotalCount; // (int*)(g_handleBucketBase + 0x4000)

// Handle-to-node index table (0x1000 entries, each 0x38 bytes, first field is pointer to node)
extern uint8_t* g_handleTableBase; // DAT_011a0f38

// Node structure (allocated via pool)
struct HandleNode {
    int32_t refCount;   // +0x00
    uint32_t handle;    // +0x04
    int32_t flags;      // +0x08 (operation flag, e.g., 3 = acquire)
    // ... padding up to 0x34
    uint32_t key;       // +0x34
    HandleNode* next;   // +0x38
};

// Forward declaration – allocation from pool
HandleNode* allocateHandleNode(); // FUN_00610a80

// Acquire or create a handle entry.
// key: unique resource key (hash)
// handle: index into handle table (must be < 0x1000 or -1 to reject)
// flags: operation type (3 = acquire existing, other = create)
// Returns 1 on success, 0 on failure.
int32_t HandleManager::acquireOrCreateHandle(uint32_t key, uint32_t handle, int32_t flags) {
    if (handle == 0xFFFFFFFF) {
        return 0;
    }

    // Hash bucket index from lower 12 bits of key
    uint32_t bucketIdx = key & 0xFFF;
    HandleNode* node = *(HandleNode**)(g_handleBucketBase + bucketIdx * 4);

    // Search existing chain for matching key
    while (node != nullptr) {
        if (node->key == key) {
            break;
        }
        node = node->next;
    }

    if (node == nullptr) {
        // No existing node, allocate new one
        HandleNode* newNode = allocateHandleNode();
        if (newNode == nullptr) {
            return 0;
        }

        newNode->key = key;                    // +0x34
        newNode->refCount = 1;                 // +0x00
        newNode->handle = handle;              // +0x04
        newNode->flags = flags;                // +0x08

        // Register in handle-to-node table (if handle is within range and table slot exists)
        // Each slot is 0x38 bytes; store pointer at slot start
        if (handle < 0x1000 && (handle * 0x38 != 0xFFFFF0D8)) { // second condition guards against overflow/negative? original had -0x11a0f28 = 0xFEE5F0D8? Ignored.
            *(HandleNode**)(g_handleTableBase + handle * 0x38) = newNode;
        }

        // Insert into hash chain (head insertion)
        newNode->next = *(HandleNode**)(g_handleBucketBase + (newNode->key & 0xFFF) * 4);
        *(HandleNode**)(g_handleBucketBase + (newNode->key & 0xFFF) * 4) = newNode;

        // Increment total global count
        (*g_handleTotalCount)++;

        return 1;
    } else {
        // Existing node found; only proceed if operation is "acquire" (3)
        if (flags != 3) {
            return 0;
        }

        // If handle is out of range, just return success (no ref increment)
        if (handle > 0xFFF) {
            return 1;
        }

        // Retrieve the node pointer stored at handle slot
        HandleNode* slotNode = *(HandleNode**)(g_handleTableBase + handle * 0x38);
        if (slotNode == nullptr) {
            // Slot empty – nothing to increment
            return 1;
        }

        // Increment reference count
        slotNode->refCount++;
        return 1;
    }
}