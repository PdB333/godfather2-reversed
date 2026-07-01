//FUNC_NAME: EARSObject::~EARSObject
int __thiscall EARSObject::~EARSObject(int this, byte deallocFlag)
{
    // Release the resource pointed to by the member at offset +0x08
    FUN_009c8f10(*(undefined4 *)(this + 8));
    
    // If the low bit of deallocFlag is set, free the object's memory
    if ((deallocFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    
    return this;
}