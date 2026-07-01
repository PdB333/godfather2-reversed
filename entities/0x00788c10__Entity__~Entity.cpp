// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity(void) {
    // Call base destructor (common cleanup)
    FUN_00788b40(this);
    
    // If the pointer at offset 0x18 is non-null, destroy the subobject
    if (*(int *)(this + 0x18) != 0) {
        // subobject destructor (likely frees memory and resets pointer)
        FUN_004daf90(this + 0x18);
    }
    
    // Virtual destructor chain: call the appropriate delete operator
    // (*(void (__thiscall**)(void*, int))(*(int*)(DAT_0112aa1c + 0x2c40) + 4))(this, 0);
}