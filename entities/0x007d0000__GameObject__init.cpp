// FUNC_NAME: GameObject::init
void __thiscall GameObject::init()
{
    // Call base class initializer (likely sets up vtable and core fields)
    FUN_007f8980();
    
    // Zero out fields at +0x74 and +0x94 – probably component pointers or state flags
    this->field_0x74 = 0;
    this->field_0x94 = 0;
    
    // Reset two sub-objects (e.g., state machines or timers) to their default (0) state
    FUN_007ac4f0(0);
    FUN_007ac510(0);
}