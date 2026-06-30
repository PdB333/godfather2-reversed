// FUNC_NAME: Container::getTotalSize

/*
 * Function: 0x005589e0
 * Role: Computes total size/count by adding a base value from a sub-structure and a dynamic value from a virtual call.
 *       Base value: *(*(this+0x4)+0x4)  -> read size from BaseInfo struct.
 *       Dynamic: if this+0x1c is non-null, follow pointer at offset 0x10 of that handle to an implementation object,
 *       then call its second virtual function (vtable+0x4) which returns the dynamic portion.
 */

#include <cstdint>

// Forward declarations for structs used by the container
struct BaseInfo {
    int32_t unused00; // +0x00
    int32_t size;     // +0x04: base size/count
};

struct DynamicPartImpl {
    virtual int32_t getDynamicSize() = 0; // vtable index 1 (offset +0x04)
};

struct DynamicPartHandle {
    // fields before the pointer to the implementation
    uint8_t padding0x10[0x10]; // placeholder for offsets 0x00-0x0F
    DynamicPartImpl* m_impl;   // +0x10: pointer to actual implementation (has vtable at offset 0)
};

class Container {
private:
    // offsets are relative to this (__thiscall)
    BaseInfo* m_baseInfo;           // +0x04: pointer to a BaseInfo struct (assumed non-null)
    uint8_t pad0x08[0x14];          // +0x08 to +0x1B: unknown
    DynamicPartHandle* m_dynamic;   // +0x1C: pointer to dynamic part handle (may be null)
public:
    int32_t getTotalSize() const;
};

int32_t Container::getTotalSize() const {
    // Base size from the fixed info structure
    int32_t base = m_baseInfo->size;

    // Dynamic part
    int32_t dynamic = 0;
    if (m_dynamic != nullptr) {
        DynamicPartImpl* impl = m_dynamic->m_impl; // follow handle to implementation
        if (impl != nullptr) {
            dynamic = impl->getDynamicSize(); // virtual call (index 1)
        }
    }

    return base + dynamic;
}