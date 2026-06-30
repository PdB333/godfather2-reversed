// FUN_00682800: MetaModelInstance::~MetaModelInstance

void __thiscall MetaModelInstance::~MetaModelInstance(MetaModelInstance* this)
{
    // Call base class destructor (likely EARSObject or similar)
    FUN_0043e900();

    // Retrieve pointer at offset +0x1c (child object or allocated data)
    int* childObj = *(int**)(this + 0x1c);
    if (childObj != 0)
    {
        // Release child: call its destructor/release method
        FUN_00680f50(childObj);
        // Free memory for child object
        FUN_009c8eb0(childObj);
    }

    // Nullify the pointer at +0x1c
    *(int**)(this + 0x1c) = 0;

    return;
}