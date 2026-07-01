// FUNC_NAME: GameObject::GameObject
// Constructor for a base game object with multiple inheritance vtables.
// param_1: this pointer (pre-allocated or null depending on flag)
// param_2: bit0 indicates if memory allocation is needed (1 = allocate, 0 = use existing)
undefined4 * __thiscall GameObject::GameObject(GameObject *this, byte allocFlag)
{
    int *vtablePtr;

    // Set primary vtable for this object
    *this = &PTR_FUN_00d7463c; // Primary vtable (likely GameObject base)

    // Set secondary vtables at fixed offsets (multiple inheritance / interfaces)
    this->vtable2 = &PTR_LAB_00d7462c;  // Offset +0x3C (0xF * 4)
    this->vtable3 = &PTR_LAB_00d74628;  // Offset +0x48 (0x12 * 4)
    this->vtable4 = &PTR_LAB_00d74624;  // Offset +0x50 (0x14 * 4)

    // Call base class constructor (likely SimObject or Entity)
    BaseConstructor(); // FUN_00473880 - base initialization

    // If allocation flag is set, allocate memory for this object (size 0x6C = 108 bytes)
    if ((allocFlag & 1) != 0)
    {
        vtablePtr = (int *)Allocator::GetInstance(); // FUN_009c8f80 returns allocator object
        // Call allocator's allocation method at vtable offset 4 (operator new)
        (vtablePtr->allocate)(this, 0x6C);  // (**(code **)(*vtablePtr + 4))(this, 108)
    }

    return this;
}