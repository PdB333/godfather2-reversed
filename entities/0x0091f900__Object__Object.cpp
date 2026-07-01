// FUNC_NAME: Object::Object
// Function address: 0x0091f900
// Constructor with optional destructive cleanup flag (bit 0 of flags).
// Calls base initialization (likely base class constructor) and if bit0 set,
// calls a finalization/destructor routine (e.g., for conditional self-destruction).
Object* __thiscall Object::Object(byte flags)
{
    // Call base class initialization / constructor at 0x0091f820
    this->baseConstruct();

    // If flags bit 0 is set, call the cleanup/destructor routine (could be for preallocated objects)
    if ((flags & 1) != 0) {
        this->finalizeDestruct(); // Likely a destructor-like cleanup at 0x005c4480
    }

    return this;
}