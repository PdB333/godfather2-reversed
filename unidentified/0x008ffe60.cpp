/*
 * Function address: 0x008ffe60
 * Role: Constructor for a game component or object;
 * calls base initialization (at 0x009f01a0) and initializes a 4-byte field at offset 0x184 to 0.
 */

void __thiscall ComponentBase::constructor(ComponentBase* this)
{
    // Base class constructor / common initialization routine
    FUN_009f01a0(); // TODO: rename based on context (e.g., EntityBase::init)
    // Initialize member variable at +0x184 to 0 (e.g., optional flag, pointer, or counter)
    this->field_0x184 = 0; // +0x184
}