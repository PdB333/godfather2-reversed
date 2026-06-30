// FUNC_NAME: EARSObject::scalarDeletingDestructor
undefined4 __thiscall EARSObject::scalarDeletingDestructor(EARSObject *this, byte deletionFlag) {
    // Call the actual destructor (base class or class-specific cleanup)
    this->~EARSObjectBase();                    // FUN_006828a0: base destructor

    // If the low bit is set, free the memory via operator delete
    if ((deletionFlag & 1) != 0) {
        operator delete(this);                  // FUN_009c8eb0: memory deallocation
    }

    // Return the this pointer (uncommon; may be used for reinitialization or chaining)
    return (undefined4)this;
}