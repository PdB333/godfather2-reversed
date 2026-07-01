// FUNC_NAME: EARS::GameObject::GameObject(byte allocateFlag)
// Constructor for a base game object with multiple inheritance (3 vtable pointers).
// Layout: this[0] = primary vtable (PTR_FUN_00d74574)
//         this[0xF] = secondary vtable (at offset 0x3C) (PTR_LAB_00d74564)
//         this[0x12] = tertiary vtable (at offset 0x48) (PTR_LAB_00d74560)
// The object size is 0xFC (252) bytes, used in conditional cleanup call.
// Flag param_2 bit 0 triggers an extra destruction/cleanup via FUN_0043b960.

class BaseGameObject {
public:
    uint* vtable;        // +0x00 primary vtable
    // ... unknown data up to offset 0x3C
    uint* secondaryVtable; // +0x3C (this[0xF])
    // ... unknown data up to offset 0x48
    uint* tertiaryVtable;  // +0x48 (this[0x12])
    // ... remaining data up to 0xFC size
};

void FUN_0083f920();  // Base class initialization (constructs subobjects)
void FUN_0043b960(void* obj, uint size); // Likely placement delete or cleanup

// __thiscall: this pointer in ECX, param_2 in AL (or byte on stack)
BaseGameObject* __thiscall BaseGameObject::BaseGameObject(BaseGameObject* this, byte allocateFlag)
{
    // Set vtable pointers for multiple inheritance
    this->vtable = &PTR_FUN_00d74574;          // primary vtable
    this->secondaryVtable = &PTR_LAB_00d74564; // secondary base vtable at +0x3C
    this->tertiaryVtable = &PTR_LAB_00d74560;  // tertiary base vtable at +0x48

    // Call base class constructor(s) (likely initializes other members)
    FUN_0083f920();

    // If allocateFlag bit 0 is set, perform cleanup/deallocation
    // (e.g., object was allocated on heap and needs to be freed if construction fails?)
    if (allocateFlag & 1)
    {
        FUN_0043b960(this, 0xFC); // Size matches this class's allocation size
    }

    return this;
}