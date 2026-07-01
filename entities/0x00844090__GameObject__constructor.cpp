// FUNC_NAME: GameObject::constructor
// Address: 0x00844090
// Role: Constructor for a game object, sets vtable and optionally calls destructor based on flag

void * __thiscall GameObject::constructor(GameObject *this, byte param_2) {
    // Call base constructor (likely EARS::Framework::Object or similar)
    FUN_00598ec0();

    // Set vtable pointer to class-specific table (at 0x00d74620)
    this->vtable = &PTR_LAB_00d74620;

    // If flag bit 0 is set, call a cleanup/destructor function
    if ((param_2 & 1) != 0) {
        FUN_00840230(this);
    }

    return this;
}