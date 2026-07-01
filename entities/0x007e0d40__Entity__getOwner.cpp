// FUNC_NAME: Entity::getOwner
int __fastcall Entity::getOwner(void* this) // 0x007e0d40
{
    // +0x114: pointer to some subobject of the owner (e.g., a base class or component)
    void* subobjectPtr = *(void**)((char*)this + 0x114);
    if (subobjectPtr != 0) {
        // Owner object is 0x48 bytes before the subobject pointer
        return (int)((char*)subobjectPtr - 0x48);
    }
    return 0;
}