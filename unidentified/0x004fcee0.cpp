// FUN_004fcee0: CoreObject::constructor
int __thiscall CoreObject::constructor(byte flags)
{
    // Call base initialization (FUN_004fc9f0)
    baseInit();
    // If flag bit 0 is set, call additional initialization (FUN_009c8eb0)
    if ((flags & 1) != 0) {
        extendedInit();
    }
    return (int)this;
}