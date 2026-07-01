// FUNC_NAME: EARSObject::EARSObject
__thiscall EARSObject* EARSObject::EARSObject(EARSObject* this, byte flags) {
    // Call base class constructor/initializer
    EARSObject::baseInitialize(); // FUN_00943710
    
    // If the flags indicate dynamic allocation (bit 0 set), perform post-construction setup
    if (flags & 1) {
        EARSObject::registerWithManager(this); // FUN_005c4480
    }
    
    return this;
}