// FUNC_NAME: EARSObject::~EARSObject(byte)
void __thiscall EARSObject::~EARSObject(byte deletingFlag)
{
    // Call base destructor (likely EARS::Framework::Object)
    ((EARS::Framework::Object*)this)->~Object(); // FUN_006bcd70

    // If the deleting flag is set (heap-allocated), free the memory
    if (deletingFlag & 1) {
        // operator delete with size 0x80 (128 bytes)
        operator delete(this, 0x80); // FUN_0043b960
    }
}