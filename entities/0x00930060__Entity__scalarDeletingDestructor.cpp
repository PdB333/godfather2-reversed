// FUNC_NAME: Entity::scalarDeletingDestructor
int __thiscall Entity::scalarDeletingDestructor(Entity *thisPtr, byte deleteFlag)
{
    // +0x58: m_refOrFlag (possibly reference count or flag)
    // +0x4c: m_subObject2 (pointer to dynamically allocated sub-object)
    if (*(int *)((int)thisPtr + 0x58) != 0) {
        FUN_009c8f10(*(int *)((int)thisPtr + 0x4c)); // freed object at +0x4c, condition checks +0x58
    }
    if (*(int *)((int)thisPtr + 0x4c) != 0) {
        FUN_009c8f10(*(int *)((int)thisPtr + 0x4c));
    }
    // Static/base cleanup routine
    FUN_005c16e0();
    // If deleteFlag & 1, deallocate the object memory
    if ((deleteFlag & 1) != 0) {
        FUN_005c4480(thisPtr);
    }
    return (int)thisPtr;
}