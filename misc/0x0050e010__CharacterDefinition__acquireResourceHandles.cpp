// FUNC_NAME: CharacterDefinition::acquireResourceHandles
// Address: 0x0050e010
// This function acquires resource handles for three resource slots (e.g., body, head, props) from a character definition.
// It checks state flags, allocates handles via a global resource manager, and increments reference counts.
// The character definition is stored at 'this' with inner model data at offset 0x24.

// Forward declaration of resource manager allocation function
uint ResourceManager::allocateHandle(); // FUN_004e9270

// Global resource table: each entry is 0x38 bytes, with a pointer to a reference count at offset 0x10
struct ResourceTableEntry {
    char unknown0[0x10];        // +0x00
    int* refCountPtr;           // +0x10, pointer to reference count variable
    char unknown20[0x28];       // remainder
};

extern ResourceTableEntry g_resourceTable[0x1000]; // At 0x011a0f28

// Character definition class (partial)
class CharacterDefinition {
public:
    char m_state;               // +0x5b: state byte (0,4,5 allowed)
    char pad0x5c[0xc];          // padding to 0x68? Actually +0x24 is below
    // Inner model data object at +0x24
    ModelData* m_modelData;      // +0x24
};

class ModelData {
public:
    // Group 1: body resources?
    int m_handle1a;             // +0x10
    int m_handle1b;             // +0x14
    int m_handle1c;             // +0x18
    int m_handle1d;             // +0x1c
    // Group 2: head resources?
    int m_handle2a;             // +0x20
    int m_handle2b;             // +0x24
    int m_handle2c;             // +0x28
    int m_handle2d;             // +0x2c
    // Group 3: prop resources?
    int m_handle3a;             // +0x30
    int m_handle3b;             // +0x34
    int m_handle3c;             // +0x38
    int m_handle3d;             // +0x3c
    char m_missingFlags;        // +0x60: set to 0 if no resources needed for a group
};

int __thiscall CharacterDefinition::acquireResourceHandles(uint* outParam1, uint* outParam2, uint* outParam3) {
    char state = this->m_state;
    // Only proceed if state is 0, 4, or 5; otherwise return 1 (already satisfied?)
    if ((state != 0) && (state != 5) && (state != 4)) {
        return 1;
    }

    uint handle = ResourceManager::allocateHandle();
    *outParam1 = handle;
    if (handle == 0) {
        return 0;
    }
    // Increment reference count if valid handle
    if ((handle != 0xFFFFFFFF) && (handle < 0x1000)) {
        ResourceTableEntry* entry = &g_resourceTable[handle];
        if (entry->refCountPtr != nullptr) {
            (*entry->refCountPtr)++;
        }
    }
    if (*outParam1 == 0) {
        return 0;
    }

    // Process first group (body)
    *outParam1 = 0;
    ModelData* modelData = this->m_modelData;
    if ((modelData->m_handle1a != 0) || (modelData->m_handle1b != 0) ||
        (modelData->m_handle1c != 0) || (modelData->m_handle1d != 0)) {
        handle = ResourceManager::allocateHandle();
        *outParam1 = handle;
        if (handle != 0) {
            if ((handle != 0xFFFFFFFF) && (handle < 0x1000)) {
                ResourceTableEntry* entry = &g_resourceTable[handle];
                if (entry->refCountPtr != nullptr) {
                    (*entry->refCountPtr)++;
                }
            }
            if (*outParam1 != 0) {
                goto skipGroup1;
            }
        }
        // If allocation fails or handle becomes zero, mark missing
        modelData->m_missingFlags = 0; // Set byte at offset 0x60 to 0
    }
skipGroup1:

    // Process second group (head)
    *outParam2 = 0;
    if ((modelData->m_handle2a != 0) || (modelData->m_handle2b != 0) ||
        (modelData->m_handle2c != 0) || (modelData->m_handle2d != 0)) {
        handle = ResourceManager::allocateHandle();
        *outParam2 = handle;
        if ((handle != 0) && (handle != 0xFFFFFFFF) && (handle < 0x1000)) {
            ResourceTableEntry* entry = &g_resourceTable[handle];
            if (entry->refCountPtr != nullptr) {
                (*entry->refCountPtr)++;
            }
        }
        // Note: no missing flag set for group2? The decompiled code does not set byte 0x60 for group2 failure.
    }

    // Process third group (prop)
    *outParam3 = 0;
    if ((modelData->m_handle3a != 0) || (modelData->m_handle3b != 0) ||
        (modelData->m_handle3c != 0) || (modelData->m_handle3d != 0)) {
        handle = ResourceManager::allocateHandle();
        *outParam3 = handle;
        if (handle != 0) {
            if ((handle != 0xFFFFFFFF) && (handle < 0x1000)) {
                ResourceTableEntry* entry = &g_resourceTable[handle];
                if (entry->refCountPtr != nullptr) {
                    (*entry->refCountPtr)++;
                }
            }
        }
    }

    return 1;
}