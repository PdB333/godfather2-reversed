// FUNC_NAME: BaseObject::BaseObject
// 0x008437a0: Constructor for BaseObject, calls base initialization and optionally allocates memory if flag's low bit is set
BaseObject* __thiscall BaseObject::BaseObject(byte allocationFlag)
{
    // Base initialization (FUN_00843630) – likely calls base class constructor or setup
    this->baseInit();

    // If the allocation flag has its low bit set, perform additional memory allocation or setup (FUN_009c8eb0)
    if ((allocationFlag & 1) != 0)
    {
        this->allocateMemory();
    }

    return this;
}