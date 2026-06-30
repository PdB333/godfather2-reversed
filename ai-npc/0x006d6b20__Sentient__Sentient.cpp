// FUNC_NAME: Sentient::Sentient
// Function address: 0x6d6b20
// Constructor for Sentient class. Calls base Entity constructor, then optionally performs vtable setup
// if the parameter flag (bit0) is set (indicates heap allocation).
Sentient* __thiscall Sentient::Sentient(Sentient* this, byte flags)
{
    // Call base Entity constructor (0x6d6490)
    Entity::Entity();
    // If heap-allocation flag is set, run custom initialization (likely placement new / vtable setup)
    if ((flags & 1) != 0) {
        // Allocate or initialize the object's memory (size = 0xF4 = 244 bytes) via function at 0x43b960
        allocateOrInit(this, 0xF4);
    }
    return this;
}