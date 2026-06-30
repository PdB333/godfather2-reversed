// FUNC_NAME: AnimationData::operator=
// Reconstructed copy assignment operator for AnimationData class (size ~0x69 bytes)
// Address: 0x00656210

#include <cstdlib> // for malloc, free

// A 20-byte keyframe/entry structure (size 0x14)
struct AnimationEntry {
    uint64_t field0;  // offset 0
    uint64_t field8;  // offset 8
    uint32_t field10; // offset 16
};

// Intrusive reference counted pointer (vtable at +0, refCount at +8)
struct SharedObject {
    void** vtable;
    int refCount;
    // ... other data
};

// Global allocation counter (tracked by engine)
extern int g_totalAllocationCount; // _DAT_01205a30

class AnimationData {
public:
    // Assume first 32 bytes (0x00-0x1F) are copied directly - could be base class or other members
    // We'll treat them as an opaque block
    char baseBlock[32]; // offsets 0x00-0x1F

    SharedObject* ptr1;  // offset 0x20
    SharedObject* ptr2;  // offset 0x24
    SharedObject* ptr3;  // offset 0x28
    SharedObject* ptr4;  // offset 0x2C
    uint8_t flag0;       // offset 0x30
    uint8_t flag1;       // offset 0x31

    // Two 16-byte arrays (e.g., quaternions, bounding boxes, or transform data)
    uint8_t arrayA[16];  // offset 0x32
    uint8_t arrayB[16];  // offset 0x42

    int entryCount;      // offset 0x54
    int entryCapacity;   // offset 0x58
    AnimationEntry* entries; // offset 0x5C

    uint8_t flag2;       // offset 0x60
    uint8_t flag3;       // offset 0x61
    // padding? (offsets 0x62-0x63)

    SharedObject* ptr5;  // offset 0x64
    uint8_t flag4;       // offset 0x68

    // Helpers for intrusive pointer management
    static void addRef(SharedObject* obj) {
        if (obj) {
            obj->refCount++;
        }
    }

    static void release(SharedObject* obj) {
        if (obj) {
            obj->refCount--;
            if (obj->refCount == 0) {
                // Call destructor through vtable (vtable+8)
                void (*destructor)(SharedObject*) = (void (*)(SharedObject*))(obj->vtable[2]);
                destructor(obj);
            }
        }
    }

    void operator=(const AnimationData& other) {
        // Copy first 32 bytes (base block)
        // This is done piecewise to match the original assembly
        baseBlock[0] = other.baseBlock[0];
        baseBlock[1] = other.baseBlock[1];
        baseBlock[2] = other.baseBlock[2];
        *(uint32_t*)(baseBlock + 3) = *(uint32_t*)(other.baseBlock + 3);
        *(uint32_t*)(baseBlock + 7) = *(uint32_t*)(other.baseBlock + 7);
        *(uint32_t*)(baseBlock + 11) = *(uint32_t*)(other.baseBlock + 11);
        *(uint32_t*)(baseBlock + 15) = *(uint32_t*)(other.baseBlock + 15);
        *(uint32_t*)(baseBlock + 20) = *(uint32_t*)(other.baseBlock + 20);
        *(uint32_t*)(baseBlock + 24) = *(uint32_t*)(other.baseBlock + 24);
        *(uint32_t*)(baseBlock + 28) = *(uint32_t*)(other.baseBlock + 28);

        // Assign shared pointers with ref counting
        release(ptr1);
        ptr1 = other.ptr1;
        addRef(ptr1);

        release(ptr2);
        ptr2 = other.ptr2;
        addRef(ptr2);

        release(ptr3);
        ptr3 = other.ptr3;
        addRef(ptr3);

        release(ptr4);
        ptr4 = other.ptr4;
        addRef(ptr4);

        // Copy byte flags
        flag0 = other.flag0;
        flag1 = other.flag1;

        // Copy 16-byte arrays
        for (int i = 0; i < 16; i++) {
            arrayA[i] = other.arrayA[i];
        }
        for (int i = 0; i < 16; i++) {
            arrayB[i] = other.arrayB[i];
        }

        // Handle dynamic array (AnimationEntry list)
        if (entryCapacity < other.entryCount) {
            // Need to grow
            int newCapacity = (other.entryCount + 0x0F) & ~0x0F; // align to 16
            AnimationEntry* newBuffer = (AnimationEntry*)malloc(newCapacity * sizeof(AnimationEntry));
            int oldCount = entryCount;
            AnimationEntry* oldBuffer = entries;
            entries = newBuffer;
            // Copy old entries if any
            if (oldCount > 0) {
                for (int i = 0; i < oldCount; i++) {
                    entries[i] = oldBuffer[i];
                }
            }
            // Free old buffer
            if (oldBuffer) {
                g_totalAllocationCount -= oldCount;
                free(oldBuffer);
            }
            entryCapacity = newCapacity;
        }
        // Copy entries from other
        if (other.entryCount > 0) {
            for (int i = 0; i < other.entryCount; i++) {
                entries[i] = other.entries[i];
            }
        }
        entryCount = other.entryCount;

        // Copy remaining bytes
        flag2 = other.flag2;
        flag3 = other.flag3;

        // Assign last shared pointer
        release(ptr5);
        ptr5 = other.ptr5;
        addRef(ptr5);

        // Copy final flag
        flag4 = other.flag4;
    }
};