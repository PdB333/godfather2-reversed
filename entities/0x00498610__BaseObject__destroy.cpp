// FUNC_NAME: BaseObject::destroy
int __thiscall BaseObject::destroy(BaseObject* this, byte flags)
{
    // Release the object stored at offset +0x30
    releaseObject(*reinterpret_cast<void**>(reinterpret_cast<intptr_t>(this) + 0x30));
    
    // If the low bit of flags is set, deallocate this object's memory
    if (flags & 1)
    {
        freeMemory(this);
    }
    
    return this;
}