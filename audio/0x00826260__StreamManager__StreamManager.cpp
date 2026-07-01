// FUNC_NAME: StreamManager::StreamManager

// Constructor for the StreamManager class.
// Initializes stream buffer infrastructure and vtable pointers.
// Address: 0x00826260

class StreamManager {
public:
    // Vtable pointer (offset +0x00)
    void* vtable;

    // ... padding / other fields ...

    // Base class A vtable pointer at offset +0x3C (0xF * 4)
    void* baseAVtable;

    // Base class B vtable pointer at offset +0x48 (0x12 * 4)
    void* baseBVtable;

    // Three stream buffer sub-objects starting at offset +0x58 (0x16 * 4)
    // Each is 8 bytes (0x18 - 0x16 = 0x2, i.e. 2 ints / 8 bytes)
    // Only the first stream buffer is fully constructed; others are reset.
    struct StreamBuffer {
        // 8 byte structure (two ints)
        int field_0;
        int field_4;
    };

    StreamBuffer stream0; // offset +0x58
    StreamBuffer stream1; // offset +0x60
    StreamBuffer stream2; // offset +0x68

    // Possibly more fields up to 0x70 total size.

    StreamManager(byte allocFlag);
};

// External vtable symbols
extern void* PTR_FUN_00d734d4;
extern void* PTR_LAB_00d734c4;
extern void* PTR_LAB_00d734c0;

// Forward declarations of helper functions
void constructStream(StreamManager::StreamBuffer* buffer);    // FUN_004086d0
void resetStream(StreamManager::StreamBuffer* buffer);        // FUN_00408310
void initGlobalStreamSystem();                                 // FUN_0046c640
void operatorDelete(void* ptr, size_t size);                  // FUN_0043b960

StreamManager::StreamManager(byte allocFlag) {
    // Set up vtable pointers (main class + two base classes)
    this->vtable = &PTR_FUN_00d734d4;
    this->baseAVtable = &PTR_LAB_00d734c4;
    this->baseBVtable = &PTR_LAB_00d734c0;

    // Construct first stream buffer, then reset all three
    constructStream(&this->stream0);
    resetStream(&this->stream0);
    resetStream(&this->stream1);
    resetStream(&this->stream2);

    // Initialize global stream engine infrastructure
    initGlobalStreamSystem();

    // If the allocFlag indicates a dynamically allocated object, deallocate it
    if (allocFlag & 1) {
        operatorDelete(this, sizeof(StreamManager));
    }
}