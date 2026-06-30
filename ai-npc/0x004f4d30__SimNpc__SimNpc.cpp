// FUNC_NAME: SimNpc::SimNpc
undefined4 __thiscall SimNpc::SimNpc(SimNpc* this, byte flags)
{
    // Call the base class (or internal) initializer
    this->initSimNpc();
    // If the lowest bit of flags is set, deallocate the object (e.g., from a memory pool)
    if ((flags & 1) != 0) {
        deallocateSimNpc(this);
    }
    return (undefined4)this;
}