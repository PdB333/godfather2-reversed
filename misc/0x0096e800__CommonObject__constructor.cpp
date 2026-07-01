// FUNC_NAME: CommonObject::constructor
int __thiscall CommonObject::constructor(CommonObject* this, byte flags)
{
    // Base class initialization (likely vtable setup and default member values)
    this->commonInit(); // FUN_005c16e0

    // If the low bit of flags is set, perform additional initialization
    // (e.g., allocate resources, register with manager)
    if (flags & 1)
    {
        this->createResources(); // FUN_005c4480
    }

    return reinterpret_cast<int>(this);
}