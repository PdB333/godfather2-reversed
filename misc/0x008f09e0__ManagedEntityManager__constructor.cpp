// FUNC_NAME: ManagedEntityManager::constructor

// Function address: 0x008f09e0
// Constructor for ManagedEntityManager class (EA EARS engine)
// Initializes multiple object pools (linked lists) and registers message handlers for managed entity messages.

typedef int (*VoidFunc)(); // placeholder for vtable function pointer

class ManagedEntityManager {
public:
    // VTable pointer at +0x00
    void** vtable; // +0x00

    // Internal data after vtable
    int field_0x04;   // +0x04
    int field_0x08;   // +0x08
    // Pool 1 (size 0x28 bytes, 40 bytes)
    struct PoolNode1 {
        PoolNode1* next;   // +0x00
        PoolNode1* prev;   // +0x04
        PoolNode1* self;   // +0x08 (points to self after init)
        // rest of node data up to 0x24
        // byte at +0x24 = 1 (active flag)
        // other fields unknown
    };
    PoolNode1* pool1Head;   // +0x10 (offset of param_1[4])
    int pool1FreeCount;       // +0x14 (param_1[5])

    // Pool 2 (size 0x1c bytes, 28 bytes)
    struct PoolNode2 {
        PoolNode2* next;   // +0x00
        PoolNode2* prev;   // +0x04
        PoolNode2* self;   // +0x08
        // byte at +0x19 = 1
    };
    PoolNode2* pool2Head;   // +0x24 (param_1[9])
    int pool2FreeCount;       // +0x28 (param_1[10])

    // Pool 3 (size 0x1c bytes, 28 bytes) - same struct as pool2
    PoolNode2* pool3Head;   // +0x30 (param_1[0xc])
    int pool3FreeCount;       // +0x34 (param_1[0xd])

    // Pool 4 (size 0x18 bytes, 24 bytes)
    struct PoolNode4 {
        PoolNode4* next;   // +0x00
        PoolNode4* prev;   // +0x04
        PoolNode4* self;   // +0x08
        // byte at +0x15 = 1
    };
    PoolNode4* pool4Head;   // +0x3c (param_1[0xf])
    int pool4FreeCount;       // +0x40 (param_1[0x10])

    // Other data
    int storage1;            // +0x18 (param_1[6]) - argument param_2
    int storage2;            // +0x1c (param_1[7]) - argument param_3

    int field_0x44;          // +0x44 (param_1[0x11])
    char byte_0x48;          // +0x48 (param_1 + 0x12)  bool?
    int field_0x4c;          // +0x4c (param_1[0x13])
    int field_0x50;          // +0x50 (param_1[0x14])

    // Constructor
    __thiscall ManagedEntityManager(int arg1, int arg2) {
        // Set vtable
        this->vtable = &PTR_FUN_00d80e0c;  // actual vtable address from binary

        // Initialize pool 1 (size 0x28)
        this->field_0x04 = 1;
        this->field_0x08 = 0;

        PoolNode1* node1 = (PoolNode1*) allocateMemory(0x28); // FUN_009c8e50
        if (node1) {
            node1->next = 0;
            node1->prev = 0;
            node1->self = 0;
        }
        // Note: The original checks for null pointer on node1+1 etc. are redundant; they zero the fields anyway
        // Setting the active flag at offset +0x24
        *(char*)((int)node1 + 0x24) = 1; // mark as active

        this->pool1Head = node1;
        // Initialize circular list: node1->next = node1->prev = node1->self = node1
        node1->prev = node1;
        node1->next = node1;
        node1->self = node1; // self pointer at +0x08

        this->pool1FreeCount = 0;

        // Pool 2 (size 0x1c)
        PoolNode2* node2 = (PoolNode2*) allocateMemory(0x1c);
        if (node2) {
            node2->next = 0;
            node2->prev = 0;
            node2->self = 0;
        }
        *(char*)((int)node2 + 0x19) = 1; // active flag

        this->pool2Head = node2;
        node2->prev = node2;
        node2->next = node2;
        node2->self = node2;
        this->pool2FreeCount = 0;

        // Pool 3 (same size 0x1c)
        PoolNode2* node3 = (PoolNode2*) allocateMemory(0x1c);
        if (node3) {
            node3->next = 0;
            node3->prev = 0;
            node3->self = 0;
        }
        *(char*)((int)node3 + 0x19) = 1;
        this->pool3Head = node3;
        node3->prev = node3;
        node3->next = node3;
        node3->self = node3;
        this->pool3FreeCount = 0;

        // Pool 4 (size 0x18)
        PoolNode4* node4 = (PoolNode4*) allocateMemory(0x18);
        if (node4) {
            node4->next = 0;
            node4->prev = 0;
            node4->self = 0;
        }
        *(char*)((int)node4 + 0x15) = 1;
        this->pool4Head = node4;
        node4->prev = node4;
        node4->next = node4;
        node4->self = node4;
        this->pool4FreeCount = 0;

        // Store constructor arguments
        this->storage1 = arg1; // param_2
        this->storage2 = arg2; // param_3

        // Initialize other fields
        this->field_0x44 = 0;
        this->byte_0x48 = 0;
        this->field_0x4c = 0;
        this->field_0x50 = 0;

        // Register message strings via string table
        registerString(&DAT_0112fddc, "iMsgManagedEntityCreated");   // FUN_00408240
        registerString(&DAT_0112fdf8, "iMsgManagedEntityPostSpawn");
        registerString(&DAT_0112fde8, "iMsgManagedEntityCancelled");
        registerString(&DAT_0112fe00, "iMsgManagedEntityIsStillNeeded");
        registerString(&DAT_0112fdf0, "iMsgRetryEntityProxy");

        // Initialize message handlers if global data is present
        if (DAT_01206940 != 0) {
            initMessageHandlers(this, &DAT_01206940, 0x8000); // FUN_00408900
        }
    }
};

// Note: PTR_FUN_00d80e0c, DAT_0112fddc, DAT_01206940, etc. are addresses from binary.
// allocateMemory, registerString, initMessageHandlers are stubs for the corresponding functions:
// FUN_009c8e50 - memory allocator
// FUN_00408240 - string registration (likely stores string pointer)
// FUN_00408900 - handler registration (binds messages to this object)