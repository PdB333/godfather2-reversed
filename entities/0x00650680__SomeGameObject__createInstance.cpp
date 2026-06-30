// FUNC_NAME: SomeGameObject::createInstance
void SomeGameObject::createInstance(int param1, int param2) // param1 appears unused; param2 stored at +0x20
{
    // Allocate 0x24 bytes for the object
    int* newObj = (int*)AllocMemory(0x24); // FUN_009c8e50
    if (newObj != nullptr)
    {
        // Initialize fields
        newObj[1] = 0; // +0x04: field1
        newObj[2] = 0; // +0x08: field2
        newObj[4] = 0; // +0x10: field4
        newObj[3] = 1; // +0x0C: field3, initially 1
        *newObj = (int)&PTR_LAB_00e42fc0; // +0x00: primary vtable
        newObj[6] = (int)&PTR_LAB_00e42fec; // +0x18: secondary vtable
        newObj[7] = (int)&LAB_00652760; // +0x1C: callback/function pointer
        newObj[5] = (int)(newObj + 6); // +0x14: pointer to secondary vtable pointer (self-relative)
        newObj[8] = param2; // +0x20: store param2
        // Call base constructor
        BaseClassConstructor(newObj); // FUN_0064ef60
    }
    else
    {
        // Error path: store param2 to global and call base constructor with null
        g_someGlobal = param2; // uRam00000020
        BaseClassConstructor(nullptr); // FUN_0064ef60(0)
    }
}