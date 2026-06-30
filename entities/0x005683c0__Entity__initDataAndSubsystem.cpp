// FUNC_NAME: Entity::initDataAndSubsystem
void Entity::initDataAndSubsystem(void)
{
    // Call virtual function at offset 0x3c from vtable at +0x34 to create/get data object
    // vtable at +0x34 (likely an interface vtable for data provider)
    int *pDataVtable = *(int **)(this + 0x34);
    int *pDataObject = (int *)(**(code **)(pDataVtable + 0x3c))();  // virtual at slot 15 (0x3c/4)
    *(int **)(this + 0x8) = pDataObject;  // m_pDataObject

    // Call helper function (likely a static initialization step)
    FUN_005684b0();

    // Call virtual function at offset 0x64 on the data object (100 = 0x64, slot 25)
    int *pDataVtable2 = *(int **)pDataObject;
    (**(code **)(pDataVtable2 + 0x64))();  // init/setup

    // Call virtual function at offset 0x90 on the data object (144 = 0x90, slot 36)
    int handle = (**(code **)(pDataVtable2 + 0x90))();  // returns handle
    *(int *)(this + 0x30) = handle;  // m_handle

    // Call virtual function at offset 0x24 from the first vtable to get subsystem pointer
    int *pSubSystem = (int *)(**(code **)(pDataVtable + 0x24))();  // virtual at slot 9 (0x24/4)
    *(int **)(this + 0xc) = pSubSystem;  // m_pSubSystem

    // Call virtual function at offset 0x74 on the subsystem object with argument 1
    int *pSubVtable = *(int **)pSubSystem;
    (**(code **)(pSubVtable + 0x74))(1);  // enable/register subsystem? (arg 1 means active)
    return;
}