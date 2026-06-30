// FUNC_NAME: SnapshotManager::createSnapshotNode
// Address: 0x00672b00
// Role: Creates a new snapshot node, copies object state into it, and inserts into hash and sequence lists.

// Struct representing the node placed into the manager
struct SnapshotNode {
    SnapshotNode* hashNext;   // +0x00
    SnapshotNode* hashPrev;   // +0x04
    SnapshotNode* seqNext;    // +0x08
    SnapshotNode* seqPrev;    // +0x0c
    SnapshotNode* unknown;    // +0x10 (maybe another list member)
    // +0x14: snapshot data (68 bytes copied from source object)
    unsigned short flag1;     // +0x5a   (0 or 1 depending on source flag)
    unsigned short someFlag;  // +0x5c   (from source +0x108)
    unsigned short keyY;      // +0x60   (param_4)
    unsigned short keyX;      // +0x62   (param_3)
    int keyZ;                 // +0x64   (param_5)
};

// Manager struct holding the hash table and sequence list
struct SnapshotManager {
    int field_00;                           // +0x00
    SnapshotNode* currentFree;               // +0x04? (the node to reuse)
    SnapshotNode* currentNode;               // +0x08? (current node being filled)
    SnapshotNode* hashBuckets[128];          // +0x0c (actually pointer to array, size 128)
    SnapshotNode* seqHead;                   // +0x14
    SnapshotNode* seqTail;                   // +0x18
};

// Source object whose state is captured
struct StateSource {
    // vtable at +0x00
    int* vtable;                     // +0x00
    // +0x20: some pointer (has +4 set to 0)
    int* somePointer;                // +0x20
    SnapshotManager* manager;        // +0x38
    void* vtableFunc;                // +0x3c (function pointer, typically a method)
    // +0xcc..+0x120: state data (68 bytes)
    unsigned short field_0xcc;       // +0xcc
    int field_0xd0;                  // +0xd0
    int field_0xd4;                  // +0xd4
    int field_0xd8;                  // +0xd8
    int field_0xdc;                  // +0xdc
    int field_0xe0;                  // +0xe0
    int field_0xe4;                  // +0xe4
    unsigned short field_0xe8;       // +0xe8
    int field_0xec;                  // +0xec
    int field_0xf0;                  // +0xf0
    int field_0xf4;                  // +0xf4
    int field_0xf8;                  // +0xf8
    int field_0xfc;                  // +0xfc
    int field_0x100;                 // +0x100
    unsigned short field_0x108;      // +0x108
    int flagDirty;                   // +0x10c   (0 if clean)
    int flagDeactivated;             // +0x110   (0 if active)
    int field_0x114;                 // +0x114
    int field_0x118;                 // +0x118   (if 0, sets node flag1=1 else 0)
    unsigned short field_0x120;      // +0x120
};

// External functions
extern int FUN_00674d40(void* param_1, int param_2, int param_3, int* result);
extern SnapshotNode* FUN_00672d10(void);

// __fastcall with ECX = param_1, EDX = param_2
int __fastcall SnapshotManager::createSnapshotNode(
    int param_1,                // ECX: some user data (passed to vtable)
    StateSource** outSource,    // EDX: pointer to source object pointer
    unsigned short keyX,        // stack param_3: key component for hash
    unsigned short keyY,        // stack param_4: key component for hash
    int keyZ,                   // stack param_5: key component for hash
    int* outResult              // stack param_6: result code (0 success)
) {
    StateSource* source = *outSource;
    SnapshotManager* manager = source->manager;  // +0x38

    // Clear the pointer at source+0x20 +4
    *(int*)(source->somePointer + 1) = 0;  // +0x24

    if (manager == 0) {
        // No manager yet, call constructor to allocate one
        FUN_00674d40(source, 0, 0, outResult);
    } else {
        // Call a virtual function on source to prepare the node
        void (*prepFunc)(SnapshotManager*, int, StateSource**, int, int, int, int, int) =
            (void (*)(SnapshotManager*, int, StateSource**, int, int, int, int, int))source->vtableFunc;
        prepFunc(manager, keyY, outSource, keyX, 0, 0, 3, param_1);
    }

    if (*outResult != 0) {
        return 0;   // failure
    }

    // Check if source is not flagged as deactivated or dirty
    if (source->flagDirty == 0 && source->flagDeactivated == 0) {
        SnapshotNode* node = FUN_00672d10();   // allocate a node
        if (node != 0) {
            node = (SnapshotNode*)((int)node + 0x68);  // adjust pointer? (likely offset to payload)
        }
        manager->currentNode = node;   // store in manager
    }

    SnapshotNode* node = manager->currentNode;  // +0x08? Actually +0x08 is the node pointer
    if (node != 0) {
        // Set keys into node
        node->keyX = keyX;   // +0x62
        node->keyY = keyY;   // +0x60
        node->keyZ = keyZ;   // +0x64

        // Copy state data from source to node (starting at node+0x14 from source+0xcc)
        unsigned short* src16 = (unsigned short*)((int)source + 0xcc);
        unsigned short* dst16 = (unsigned short*)((int)node + 0x14);
        *dst16 = *src16;                          // +0x14 = +0xcc
        int* src32 = (int*)((int)source + 0xd0);
        int* dst32 = (int*)((int)node + 0x18);   // align to 4? Actually after 2 bytes, so +0x18
        dst32[0] = src32[0];  // +0xd0 -> +0x18
        dst32[1] = src32[1];  // +0xd4 -> +0x1c
        dst32[2] = src32[2];  // +0xd8 -> +0x20
        dst32[3] = src32[3];  // +0xdc -> +0x24
        dst32[4] = src32[4];  // +0xe0 -> +0x28
        dst32[5] = src32[5];  // +0xe4 -> +0x2c
        unsigned short* src16_2 = (unsigned short*)((int)source + 0xe8);
        unsigned short* dst16_2 = (unsigned short*)((int)node + 0x30);
        *dst16_2 = *src16_2;  // +0xe8 -> +0x30
        int* src32_2 = (int*)((int)source + 0xec);
        int* dst32_2 = (int*)((int)node + 0x34);
        dst32_2[0] = src32_2[0];  // +0xec -> +0x34
        dst32_2[1] = src32_2[1];  // +0xf0 -> +0x38
        dst32_2[2] = src32_2[2];  // +0xf4 -> +0x3c
        dst32_2[3] = src32_2[3];  // +0xf8 -> +0x40
        dst32_2[4] = src32_2[4];  // +0xfc -> +0x44
        dst32_2[5] = src32_2[5];  // +0x100 -> +0x48
        int* src32_3 = (int*)((int)source + 0x10c);
        int* dst32_3 = (int*)((int)node + 0x4c);
        dst32_3[0] = src32_3[0];  // +0x10c -> +0x4c
        dst32_3[1] = src32_3[1];  // +0x110 -> +0x50
        dst32_3[2] = src32_3[2];  // +0x114 -> +0x54
        unsigned short* src16_3 = (unsigned short*)((int)source + 0x120);
        unsigned short* dst16_3 = (unsigned short*)((int)node + 0x58);
        *dst16_3 = *src16_3;  // +0x120 -> +0x58
        unsigned short* src16_4 = (unsigned short*)((int)source + 0x108);
        unsigned short* dst16_4 = (unsigned short*)((int)node + 0x5c);
        *dst16_4 = *src16_4;  // +0x108 -> +0x5c

        // Set node flag based on source field
        if (source->field_0x118 == 0) {
            node->flag1 = 1;    // +0x5a
        } else {
            node->flag1 = 0;
        }

        // Insert into hash table
        int hashIndex = ((unsigned short)node->keyX * 0x10 +
                         (unsigned short)node->keyY +
                         (node->keyZ & 0x7f)) & 0x7f;  // +0x60, +0x62, +0x64
        SnapshotNode** bucket = &manager->hashBuckets[hashIndex]; // +0x0c is array pointer
        SnapshotNode* oldHead = *bucket;
        *bucket = node;
        node->hashNext = oldHead;
        node->hashPrev = 0;
        if (oldHead != 0) {
            oldHead->hashPrev = node;
        }

        // Insert into sequence list (doubly linked)
        SnapshotNode* oldSeqHead = manager->seqHead; // +0x14
        node->seqNext = oldSeqHead;
        node->seqPrev = 0;
        if (oldSeqHead != 0) {
            oldSeqHead->seqPrev = node;
        }
        manager->seqHead = node;  // new head
        if (manager->seqTail == 0) {  // +0x18
            manager->seqTail = node;  // first element
        }

        return (int)node;
    }

    return 0;  // no node created
}