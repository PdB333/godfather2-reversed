// FUNC_NAME: Entity::Entity

int __thiscall Entity::Entity(Entity* this_, byte constructFlags) {
    undefined4* vtablePtr;
    
    if (this_ != 0) {
        // vtable pointer at offset +0x20 from this
        vtablePtr = (undefined4*)((int)this_ + 0x20);
    } else {
        vtablePtr = (undefined4*)0;
    }
    // Set the vtable to the Entity class vtable
    *vtablePtr = &PTR_LAB_00d580d0;
    
    // Reset a static/global initialization flag
    DAT_011298c0 = 0;
    
    // Call base class initialization (likely sets up base members)
    baseInitialize(); // FUN_007edfb0
    
    // If the low bit of constructFlags is set, perform full construction
    if ((constructFlags & 1) != 0) {
        fullConstruct(this_); // FUN_009c8eb0
    }
    
    return (int)this_;
}