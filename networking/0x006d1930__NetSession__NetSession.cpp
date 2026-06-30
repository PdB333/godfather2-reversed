// FUNC_NAME: NetSession::NetSession
// Address: 0x006d1930
// Constructor for NetSession class. Initializes base, vtable pointers, clears fields,
// allocates sub-object (likely ReplicationManager), retrieves session ID from parent,
// and checks debug flag to enable logging.

class NetSession {
public:
    // Virtual function table pointers (multiple inheritance)
    void* vtable0;       // +0x00, points to PTR_FUN_00d5f360
    void* vtable2;       // +0x08, points to PTR_LAB_00d5f358
    // Reserved fields (cleared during init)
    int field_0x80[4];   // +0x80 (indices 0x20,0x21,0x22,0x23)
    int field_0x90[4];   // +0x90 (indices 0x24,0x25,0x26,0x27)
    int field_0xA0[4];   // +0xA0 (indices 0x28,0x29,0x2A,0x2B)
    int someId;          // +0xD4 (index 0x35) – result of parent vfunc at index 10
    void* subObject;     // +0xD8 (index 0x36) – allocated sub-object (size 0xA0)
    int field_0xE4;      // +0xE4 (index 0x39) – initialised to 0

    NetSession(int* parent) {
        // Call base class constructor (likely NetReflectable or similar)
        FUN_00473950(parent);

        // Set vtable pointers for this class
        vtable0 = &PTR_FUN_00d5f360;
        vtable2 = &PTR_LAB_00d5f358;

        // Clear reserved fields
        field_0x80[3] = 0; // index 0x23
        field_0x80[2] = 0; // index 0x22
        field_0x80[1] = 0; // index 0x21
        field_0x80[0] = 0; // index 0x20
        field_0x90[3] = 0; // index 0x27
        field_0x90[2] = 0; // index 0x26
        field_0x90[1] = 0; // index 0x25
        field_0x90[0] = 0; // index 0x24
        field_0xA0[3] = 0; // index 0x2B
        field_0xA0[2] = 0; // index 0x2A
        field_0xA0[1] = 0; // index 0x29
        field_0xA0[0] = 0; // index 0x28

        // Allocate sub-object of size 0xA0 with alignment parameters
        {
            void* allocator = FUN_009c8f80();  // get memory allocator
            int alignmentParams[] = {2, 0x10, 0}; // alignment = 2, extra = 0x10, flags = 0
            subObject = (void*)((void* (*)(void*, int*)) *(* (void***)allocator))(0xA0, alignmentParams);
            if (subObject) {
                // Set vtable for sub-object
                *(void**)subObject = &PTR_LAB_00d5f2f4;
            }
        }

        // Call virtual function #10 on parent to retrieve session ID
        someId = (*(int (**)(void))(*(int*)parent + 0x28))();

        field_0xE4 = 0;

        // Enable debug logging if global debug flag is set
        char debugFlag = FUN_0089c630();
        if (debugFlag != 0) {
            FUN_006913c0(8);
        }
    }
};