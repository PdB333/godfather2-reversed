// FUNC_NAME: Entity::Entity
// Address: 0x0064b650
// Role: Constructor for Entity class with optional full initialization flag.
// Calls base class constructor (0x64b440) and, if flag bit 0 set, additional initialization (0x9c8eb0).

void __thiscall Entity::Entity(byte flags)
{
    // Call base class constructor
    this->baseConstructor();

    // If flags indicates full initialization (bit 0 set), perform additional setup
    if ((flags & 1) != 0) {
        this->additionalInit();
    }
    // Constructor returns this implicitly; the exported function returns param_1 (this).
}