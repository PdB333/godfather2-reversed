// FUNC_NAME: EARS::ObjectArray::destroyObjects (destructor-like cleanup)
// Reconstructed destructor for a class managing a dynamic array of objects.
// The class has the following layout:
//   +0x00  vtable pointer
//   +0x04  (padding)
//   +0x08  pointer to array of object pointers (m_objects)
//   +0x0C  count of elements (m_count)
// Each object's first vtable entry is a release/destroy function that takes an int argument
// (1 means "delete this" or equivalent). The array itself is freed after all objects are released.

void __thiscall ObjectArray::destroyObjects()
{
    uint32_t uVar2;
    uint32_t* puVar1;

    // Set vtable (this is a destructor, vtable is set to the base class's vtable)
    *(uintptr_t**)this = &PTR_FUN_00d73888;

    // Destroy each object in the array
    if (this->m_count != 0) {
        for (uVar2 = 0; uVar2 < (uint32_t)this->m_count; uVar2++) {
            puVar1 = *(uint32_t**)(this->m_objects + uVar2 * 4);
            if (puVar1 != (uint32_t*)0x0) {
                // Call the virtual destructor/release function at vtable[0] with argument 1
                (**(code**)*puVar1)(1);
            }
        }
    }

    // Free the array memory
    if (this->m_objects != 0) {
        free(this->m_objects);  // Actually FUN_009c8f10, likely operator delete[] or free
        this->m_objects = 0;
    }
}