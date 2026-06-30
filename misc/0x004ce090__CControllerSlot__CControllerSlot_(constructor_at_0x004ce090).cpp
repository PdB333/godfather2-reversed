// FUNC_NAME: CControllerSlot::CControllerSlot (constructor at 0x004ce090)

#include <cstdint>

// Forward declarations
class CEngineSingleton;
class CSubObject; // initialized at offset 0xC

// The class being constructed
class CControllerSlot {
public:
    // vtable pointer at +0x00
    void** vtable;

    // +0x04: flag set to 1 (likely active or something)
    int32_t m_activeFlag;

    // +0x08: flag set to 0
    int32_t m_enabledFlag;

    // +0x0C: embedded sub-object (e.g., a network node or controller state)
    CSubObject m_subObject;

    // +0x2C: first constructor parameter (e.g., device type)
    int32_t m_deviceType;

    // +0x30: second constructor parameter (e.g., device index)
    int32_t m_deviceIndex;

    // Constructor (__thiscall)
    void __thiscall Constructor(int32_t deviceType, int32_t deviceIndex);
};

// Sub-object initializer (callee at 0x004ceb40)
void __thiscall InitSubObject(CSubObject* subObj);

// Singleton accessor (callee at 0x009c8f80)
CEngineSingleton* __cdecl GetEngineSingleton();

// Allocation/creation function (callee at 0x004265d0)
// Takes a pointer to a zeroed block and engine singleton, returns handle
int32_t __cdecl AllocateHandle(int32_t* zeroBlock, CEngineSingleton* engine);

// -- Implementation --

void __thiscall CControllerSlot::Constructor(int32_t deviceType, int32_t deviceIndex) {
    // Initialize vtable
    this->vtable = &PTR_FUN_00e36c60; // external vtable reference

    // Set flags
    this->m_activeFlag = 1;
    this->m_enabledFlag = 0;

    // Local zero-initialized block (used for allocation/creation)
    int32_t zeroBlock[3] = {0, 0, 0}; // corresponds to local_10, local_c, local_8

    // Get engine singleton (e.g., memory manager or object factory)
    CEngineSingleton* engine = GetEngineSingleton();

    // Call vtable method at offset 0x8 (e.g., BeginAllocation)
    engine->BeginAllocation(); // offset 8 in vtable

    // Allocate/create a handle using the zero block
    int32_t handle = AllocateHandle(zeroBlock, engine);

    // Initialize sub-object at offset +0x0C
    InitSubObject(&this->m_subObject);

    // If handle is valid, call vtable method at offset 0x4 (e.g., EndAllocation)
    if (handle != 0) {
        engine->EndAllocation(handle, 0); // offset 4 in vtable
    }

    // Call vtable method at offset 0xC (e.g., Finalize)
    engine->Finalize(); // offset 0xC in vtable

    // Store constructor parameters
    this->m_deviceType = deviceType;
    this->m_deviceIndex = deviceIndex;
}