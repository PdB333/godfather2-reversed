// FUNC_NAME: Stream::createStream
// Reconstructed static factory for creating a streaming object in the EARS engine.
// Handles allocation, initialization from a stream template data manager, and error control.
// Returns pointer to new stream or null with error code in outErrorCode for invalid types.

#include <cstdint>

struct StreamData; // forward declaration for stream template structure

// Internal memory allocator (likely from EARS memory manager)
void* __cdecl allocStreamMemory(size_t size);

// Base initialization of stream fields, sets many to zero/defaults
void __cdecl streamBaseInit(void* stream);

// Retrieves a stream template from the data manager. Returns pointer to large structure.
// Parameters: manager context (void*), lookup key (void*)
StreamData* __cdecl getStreamData(void* manager, void* key);

// Prepares callback data at a given offset (+0x21 from stream base)
uint32_t __cdecl prepareStreamCallback(void* streamCallbackData);

// External function pointers used as vtable entries (thunks)
extern void* LAB_00675800;  // address of vtable for streams with no parent
extern void* LAB_006757f0;  // address of vtable for streams with a parent

// Known offsets into the stream object (0-based byte offsets)
enum StreamOffsets {
    kFlags             = 0x00,  // int
    kVtablePtr         = 0x04,  // void* (points to a thunk table)
    kAssociatedObj     = 0x08,  // void* (the "this" for the vtable)
    kUnknown0C         = 0x0C,  // int
    kParentOrNext      = 0x10,  // void* (linked stream or parent)
    kDataPtr           = 0x20,  // void* (pointer to StreamData from manager, offset 8 in int indices)
    kCallbackFunc      = 0x80,  // void (*)(void*, void*, uint32_t)
    kCallbackData      = 0x84,  // offset for callback data structure
    kTemplateField_100 = 0x40,  // void* (copied from StreamData+0x100)
    kTemplateField_128 = 0x4C,  // void* (copied from StreamData+0x128)
    kField_1a          = 0x68,  // int (from StreamData+0x1E4)
    kShortField_1b     = 0x6C,  // short (from StreamData+0x1E8)
    kShortField_6E     = 0x6E,  // short (from StreamData+0x1EA)
    kField_1c          = 0x70,  // int (initialized to -1)
    kField_1d          = 0x74,  // int (initialized to -1)
    kField_1e          = 0x78,  // int (initialized to 0)
    kParam3            = 0xA8,  // void* (store of param3)
    kParam4            = 0xAC,  // void* (store of param4)
    kParam_EAX         = 0xB4,  // void* (store of in_EAX register)
    kField_2f          = 0xBC,  // int (set from stream data or default)
    kStreamType        = 0xC0,  // int (set to 1 initially)
};

// Known offsets into the StreamData template structure (0-based byte offsets)
enum StreamDataOffsets {
    kDataField_10   = 0x10,   // void*
    kDataField_100  = 0x100,  // void*
    kDataField_108  = 0x108,  // short (used as length or index)
    kDataField_128  = 0x128,  // void*
    kDataField_1E4  = 0x1E4,  // int
    kDataField_1E8  = 0x1E8,  // short
    kDataField_1EA  = 0x1EA,  // short
};

// The created stream type (parameter 1)
enum StreamType : short {
    kStreamTypeInvalid1 = 2,
    kStreamTypeSpecial  = 3,  // loads data from manager
    kStreamTypeInvalid2 = 5,
    kStreamTypeInvalid3 = 7,
};

// Main factory function
void* __cdecl Stream::createStream(
    short streamType,
    void* param2,
    void* param3,
    void* param4,
    void* param5,
    int* outErrorCode
) {
    void* stream;
    void* data;
    int i;
    uint32_t uVar4;

    if (outErrorCode == nullptr) {
        return nullptr;
    }
    *outErrorCode = 0;

    stream = allocStreamMemory(0); // size likely determined by allocator
    if (stream == nullptr) {
        return nullptr;
    }

    // Zero-initialize many fields (the decompiler shows a long list)
    *(int*)((uint8_t*)stream + kFlags) = 0;
    *(void**)((uint8_t*)stream + kVtablePtr) = nullptr;
    // ... (many zero assignments omitted for brevity, but present in original)

    // Store provided parameters
    *(void**)((uint8_t*)stream + kParam3) = param3;
    *(void**)((uint8_t*)stream + kParam4) = param4;
    // in_EAX is stored at kParam_EAX (likely a global or register value)
    // In the decompiled code, it's the value of EAX at entry, possibly a hidden this pointer
    *(void**)((uint8_t*)stream + kParam_EAX) = /* in_EAX */ nullptr;  // placeholder
    *(int*)((uint8_t*)stream + 0xB0) = 0;
    *(int*)((uint8_t*)stream + kStreamType) = 1;

    // Additional zeros and short zero at offset 0x1C
    // (All zero fields from decompiled listing)
    *(short*)((uint8_t*)stream + 0x1C) = 0;

    // Call base initialization (likely sets more defaults)
    streamBaseInit(stream);

    // Set sentinel fields to -1
    *(int*)((uint8_t*)stream + kField_1c) = -1;
    *(int*)((uint8_t*)stream + kField_1d) = -1;
    *(int*)((uint8_t*)stream + kField_1e) = 0;

    // Additional zeros (from decompiled)
    // ...

    // Handle special stream type 3 (load from data manager)
    if (streamType == kStreamTypeSpecial) {
        data = getStreamData(*(void**)((uint8_t*)stream + kParam3), param2);
        *(void**)((uint8_t*)stream + kDataPtr) = data;
        if (data != nullptr) {
            // Copy fields from the template
            *(void**)((uint8_t*)stream + kTemplateField_128) = *(void**)((uint8_t*)data + kDataField_128);
            *(void**)((uint8_t*)stream + kTemplateField_100) = *(void**)((uint8_t*)data + kDataField_100);
            // Null out the source field (ownership transfer?)
            *(void**)((uint8_t*)data + kDataField_100) = nullptr;

            // More fields from template
            i = (int)data;
            *(int*)((uint8_t*)stream + kStreamType) = *(int*)(i + 0x10);
            *(short*)((uint8_t*)stream + kShortField_1b) = *(short*)(i + kDataField_1E8);
            *(short*)((uint8_t*)stream + kShortField_6E) = *(short*)(i + kDataField_1EA);
            *(int*)((uint8_t*)stream + kField_1a) = *(int*)(i + kDataField_1E4);

            // Invoke callback if present
            if (*(void**)((uint8_t*)stream + kCallbackFunc) != nullptr) {
                uint32_t cbData = prepareStreamCallback((void*)((uint8_t*)stream + kCallbackData));
                ((void (*)(void*, void*, uint32_t))(*(void**)((uint8_t*)stream + kCallbackFunc)))(
                    *(void**)((uint8_t*)stream + kTemplateField_100),
                    *(void**)((uint8_t*)stream + kParam_EAX),
                    cbData
                );
            }
        }
    }

    // Choose vtable based on whether we have a parent/next pointer
    if (*(void**)((uint8_t*)stream + kParentOrNext) == nullptr) {
        *(void**)((uint8_t*)stream + kVtablePtr) = &LAB_00675800;
        *(void**)((uint8_t*)stream + kAssociatedObj) = stream;
    } else {
        *(void**)((uint8_t*)stream + kVtablePtr) = &LAB_006757f0;
        *(void**)((uint8_t*)stream + kAssociatedObj) = *(void**)((uint8_t*)stream + kParentOrNext);
    }

    // Determine value for field at kField_2f (offset 0xBC)
    if (*(void**)((uint8_t*)stream + kDataPtr) != nullptr) {
        i = (int)(*(void**)((uint8_t*)stream + kDataPtr));
        *(int*)((uint8_t*)stream + kField_2f) = (int)*(short*)(i + kDataField_108);
    } else {
        uVar4 = (uint)*(unsigned short*)((uint8_t*)stream + 0x2C); // index 11 (0x2C)
        // Check another field at index 12 (offset 0x30) for length limit
        if ( (*(void**)((uint8_t*)stream + 0x30) != nullptr) &&
             (i = *(int*)((uint8_t*)(*(void**)((uint8_t*)stream + 0x30)) + 8), i <= (int)uVar4) ) {
            uVar4 = i - 1;
        }
        *(int*)((uint8_t*)stream + kField_2f) = uVar4;
    }

    // Check for invalid stream types (2, 5, 7) – these return error
    if (streamType == 2 || streamType == 5 || streamType == 7) {
        *outErrorCode = 0x2729; // Error code (likely “unsupported stream type”)
        return nullptr;
    }

    return stream;
}