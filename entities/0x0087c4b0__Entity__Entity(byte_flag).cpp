// FUNC_NAME: Entity::Entity(byte flag)
// Function address: 0x0087c4b0
// Constructor for Entity class. Calls base constructor, then optionally allocates a large buffer (0xF20 bytes)
// if bit 0 of 'flag' is set. Allocation is done via FUN_0043b960 (likely operator new or custom allocator).

int __thiscall Entity::Entity(int this, byte flag)
{
    // Call base class constructor
    BaseClass::BaseClass(this);

    // If bit 0 of flag is set, allocate an internal buffer of size 0xF20
    if ((flag & 1) != 0) {
        allocateBuffer(this, 0xF20);   // FUN_0043b960: allocates memory relative to this? 
    }

    return this;
}