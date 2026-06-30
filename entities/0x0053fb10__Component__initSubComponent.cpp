// FUNC_NAME: Component::initSubComponent
void Component::initSubComponent(void)
{
    // +0x10: some state flag
    *(int*)(this + 0x10) = 0;

    // Base class initialization steps
    baseInit1(); // FUN_0053fc40
    baseInit2(); // FUN_0053fcc0

    // Allocate 8-byte sub-object: vtable pointer + one field
    SubObj* subObj = (SubObj*)new(8); // FUN_009c8e50
    if (subObj != nullptr)
    {
        // +0x00: vtable pointer
        subObj->vtable = (void*)&SubObjVTable; // PTR_LAB_00e39178
        // +0x04: copy value from this+0x24
        subObj->field_0x04 = *(int*)(this + 0x24);
        // Store at this+0x58
        *(SubObj**)(this + 0x58) = subObj;
        subObj->init(); // FUN_009e76a0
    }
    else
    {
        *(int*)(this + 0x58) = 0;
        // Pass null to init function
        initNullSubObj(); // FUN_009e76a0(0)
    }
    return;
}