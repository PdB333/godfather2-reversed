// FUNC_NAME: SimManager::updateAllEntities
// Address: 0x00627290
// Role: Iterates over a linked list of entities, clears a flag (bit 0 at offset 5), calls an update function on each, and uses a local synchronization wrapper.

class SimManager {
public:
    // +0x10: Pointer to a container structure holding the linked list head at offset 0x14
    struct EntityListContainer; // Forward declaration

    // Reconstructed function
    int updateAllEntities() {
        // Local wrapper object for synchronization (likely a scope lock or event)
        struct SyncWrapper {
            // 16 bytes, initialized by some constructor
            int field0;
            int field4;
            int field8;
            int fieldC;
        } syncWrapper = {0}; // Initialized to zero

        // Get pointer to the container from this+0x10
        EntityListContainer* container = *(EntityListContainer**)((char*)this + 0x10);

        // Initialize the sync wrapper
        initializeSyncWrapper(&syncWrapper);

        // Enter critical section / acquire lock
        enterCriticalSection(&syncWrapper);

        // Two calls to an "unlock" or "leave" function (pairs with enter/leave?)
        leaveCriticalSection();
        leaveCriticalSection();

        // Get some value (maybe a counter or timestamp)
        int returnValue = getSomeValue();

        // Traverse linked list: container+0x14 holds head pointer
        for (EntityNode* node = *(EntityNode**)((char*)container + 0x14);
             node != nullptr;
             node = node->next) {
            // Clear bit 0 of byte at node+5 (likely a dirty/active flag)
            *((unsigned char*)node + 5) &= 0xFE;

            // Call update function for this node (function uses some global context)
            processEntity();
        }

        // Second enter critical section
        enterCriticalSection(&syncWrapper);

        // Two more leave functions (possibly matching the earlier leaves)
        leaveCriticalSection();
        leaveCriticalSection(); // This might be a different function; we group them

        // Another leave function call (maybe unmatched)
        leaveCriticalSection();
        leaveCriticalSection(); // Another

        return returnValue;
    }

private:
    // Forward declaration of node structure
    struct EntityNode {
        EntityNode* next; // +0x00
        // +0x04: unknown
        // +0x05: byte with flags (bit0 cleared)
        // ... rest of entity data
    };

    // Forward declaration of container
    struct EntityListContainer {
        // +0x14: EntityNode* head
        char unknown[0x14]; // assumed placeholder
    };

    // Called functions (stubs, addresses provided)
    void initializeSyncWrapper(SyncWrapper* sw);               // 0x00627220
    void enterCriticalSection(SyncWrapper* sw);               // 0x00626d10
    void leaveCriticalSection();                               // 0x00626e20 (called with no args, possibly static)
    int getSomeValue();                                        // 0x006266e0
    void processEntity();                                      // 0x00626640 (called with no args, uses global entity pointer)
    void anotherCriticalSection(SyncWrapper* sw);             // 0x00626dc0 (treated as leave here)
};
// Note: The pattern of lock/unlock calls is simplified; actual logic may involve multiple synchronization primitives.