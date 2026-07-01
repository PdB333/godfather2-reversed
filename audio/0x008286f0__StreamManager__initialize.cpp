// FUNC_NAME: StreamManager::initialize
// Address: 0x008286f0
// Initializes global StreamManager singleton object with vtable and stream buffer.

struct StreamManagerVtable;

struct StreamManager {
    StreamManagerVtable* vtable; // +0x00
    void* somePointer;           // +0x04 (initially set to PTR_FUN_00e2f19c, then to PTR_LAB_00d735b8)
    int field_8;                 // +0x08 (initialized to 1)
    int field_C;                 // +0x0C (initialized to 0)
};

// Global pointer to the singleton StreamManager instance
StreamManager* gStreamManager; // DAT_0112db98

// Static buffer used for streaming (size 0x8000 = 32768 bytes)
byte gStreamBuffer[0x8000]; // DAT_0112db7c

// External function: copies data from source to destination, size given in bytes
void memcpy_40900(void* dest, void* src, int size); // FUN_00408900

// __fastcall: param_1 in ECX, this is the object to initialize
StreamManager* __fastcall StreamManager::initialize(StreamManager* this)
{
    void* ptrAt4 = reinterpret_cast<byte*>(this) + 4; // offset 0x04

    // Store global pointer to this instance
    gStreamManager = this;

    // Set initial pointer at offset 0x04 to a known function table
    *reinterpret_cast<void**>(ptrAt4) = &PTR_FUN_00e2f19c;

    // Initialize fields
    this->field_8 = 1;
    this->field_C = 0;

    // Set vtable at offset 0
    this->vtable = reinterpret_cast<StreamManagerVtable*>(&PTR_FUN_00d735c8);

    // Set offset 0x04 to a different pointer (probably a static destructor or cleanup label)
    *reinterpret_cast<void**>(ptrAt4) = &PTR_LAB_00d735b8;

    // If the global stream buffer already has data, copy it to the object's internal buffer?
    // The destination is ptrAt4 (offset 0x04) meaning it's the pointer at +0x04, not the object itself.
    // This seems to copy data from the global buffer into wherever ptrAt4 points to (maybe a dynamically allocated buffer?)
    if (gStreamBuffer != nullptr) {
        memcpy_40900(ptrAt4, &gStreamBuffer, 0x8000);
    }

    return this;
}