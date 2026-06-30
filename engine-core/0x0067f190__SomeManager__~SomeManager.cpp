// FUNC_NAME: SomeManager::~SomeManager
// Function address: 0x0067f190
// Destructor for a manager class. Sets vtable pointer, releases a member at +0x04, then sets vtable to base class and clears global singleton pointer.

void __thiscall SomeManager::~SomeManager(SomeManager* this) // __thiscall, param_1 = this
{
    // Set vtable to derived class vtable (PTR_FUN_00d58188) – likely redundant, might be initial assignment
    *this = (void*)&PTR_FUN_00d58188;

    // Check if member pointer at +0x04 is non-null
    if (this->field_0x04 != 0) {
        // Call release/destructor function on the member object
        FUN_009c8f10(this->field_0x04); // Likely frees or decrements ref count
    }

    // Set vtable to base class vtable (PTR_LAB_00d580d4)
    *this = (void*)&PTR_LAB_00d580d4;

    // Clear the global singleton instance pointer (DAT_011298c4)
    g_pSomeManagerSingleton = 0; // DAT_011298c4
}