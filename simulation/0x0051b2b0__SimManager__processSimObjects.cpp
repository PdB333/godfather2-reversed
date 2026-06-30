// FUNC_NAME: SimManager::processSimObjects
#include <cstdint>

// Thread-local storage pointer (FS segment selector)
extern "C" void* __readfsdword(unsigned long); // MSVC intrinsic

struct SimObject {
    virtual void vMethod0();       // vtable[0]
    virtual void vMethod1();       // vtable[1]
    // ...
    virtual void process();        // vtable[9] (offset 0x24)
    // +0x10: uint32* bufferPtr;   // pointer to a memory block used for flags
};

struct ThreadContext {
    // +0x00: unknown
    // +0x08: int32 flagBaseOffset; // added to object's buffer
};

struct ObjectEntry {
    SimObject* pObject;   // +0x00
    // remaining 16 bytes (4 ints) unused in this function
};

class SimManager {
    // +0x10: int32 m_activeFlag;  // 0 = disabled, others = enabled
    // +0x80: int16 m_objectCount; // number of valid entries in the array
    // +0xF4: ObjectEntry m_entries[]; // array of 20-byte structs

public:
    void processSimObjects() {
        if (m_objectCount <= 0) return;

        // Get TLS pointer (Windows: FS:[0x2c] -> ThreadEnvironmentBlock->TLS array)
        ThreadContext* threadCtx = reinterpret_cast<ThreadContext*>(__readfsdword(0x2c));
        int flagOffset = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(threadCtx) + 8);

        ObjectEntry* entry = &m_entries[0];
        for (int i = 0; i < m_objectCount; i++, entry++) {
            if (m_activeFlag && entry->pObject) {
                // Obtain the object's buffer from its own +0x10 field
                uint8_t* buffer = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(entry->pObject) + 0x10);
                // Set flag 0x40000000 at the computed offset
                uint32_t* flagWord = reinterpret_cast<uint32_t*>(buffer + flagOffset);
                *flagWord |= 0x40000000;
                // Call virtual function (vtable index 9)
                entry->pObject->process();
            }
        }
    }

private:
    uint8_t pad1[0x10];           // offset 0x00-0x0F
    int32_t m_activeFlag;         // offset 0x10
    uint8_t pad2[0x80 - 0x14];   // offset 0x14-0x7F
    int16_t m_objectCount;        // offset 0x80
    uint8_t pad3[0xF4 - 0x82];   // offset 0x82-0xF3
    ObjectEntry m_entries[1];     // offset 0xF4, actual size determined by m_objectCount
};