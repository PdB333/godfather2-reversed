// FUNC_NAME: GameObject::GameObject
// Address: 0x008960e0
// Constructor for a game object with multiple inheritance.
// param_2: if bit 0 set, calls operator delete(this, 0x74) after construction (likely for placement new cleanup)
// Class size: 0x74 bytes
// Vtable at offset 0, additional vtables at offsets 0x3C (0xF*4) and 0x48 (0x12*4)
// Sub-objects at offsets 0x5C (0x17*4), 0x64 (0x19*4), 0x6C (0x1B*4)

undefined4 * __thiscall GameObject::GameObject(undefined4 *this, byte param_2)
{
    // Set primary vtable pointer
    *this = &PTR_FUN_00d77a54;  // +0x00: vtable

    // Set secondary vtable pointers (multiple inheritance / interfaces)
    this[0xF] = &PTR_LAB_00d77a44;  // +0x3C: vtable for base class / interface 1
    this[0x12] = &PTR_LAB_00d77a40; // +0x48: vtable for base class / interface 2

    // Initialize sub-object at offset 0x5C (likely a container or string)
    initSubObject(this + 0x17);      // FUN_004086d0
    clearSubObject(this + 0x17);     // FUN_00408310
    clearSubObject(this + 0x19);     // FUN_00408310 (offset 0x64)
    clearSubObject(this + 0x1B);     // FUN_00408310 (offset 0x6C)

    // Global initialization (e.g., singleton getter, static counter)
    globalInit();                    // FUN_0046c640

    // If param_2 indicates heap allocation, free the object (placement new cleanup)
    if ((param_2 & 1) != 0) {
        operatorDelete(this, 0x74);  // FUN_0043b960
    }

    return this;
}