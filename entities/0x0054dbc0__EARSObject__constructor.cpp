// FUNC_NAME: EARSObject::constructor

uint32_t __thiscall EARSObject::constructor(uint32_t this, uint8_t flags)
{
    // Call base class or initializer at 0x54eed0
    FUN_0054eed0();
    
    // If bit 1 of flags is set, perform additional cleanup or deallocation (9c8eb0 likely operator delete)
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }
    
    return this;
}