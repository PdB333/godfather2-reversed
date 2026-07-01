// FUNC_NAME: GameManager::GameManager
undefined4* __thiscall GameManager::GameManager(GameManager* this, undefined4 initParam1, undefined4 initParam2)
{
    int singletonPtr;
    undefined4* singletonObj;

    // Call base class constructor or initialization
    FUN_007ab5e0(initParam1, initParam2);

    // Set vtable pointer
    *this = &PTR_LAB_00d6f784;

    // Set flag at offset 0x249c from member at this+0x58 (this[0x16])
    // This likely enables or marks some system as active
    *(uint*)(this[0x16] + 0x249c) |= 0x80000000;

    // Get singleton from FUN_007ab150() (likely a global manager)
    singletonPtr = FUN_007ab150();
    this[0x1d] = *(undefined4*)(singletonPtr + 4);

    // Get another singleton pointer and call a method via vtable (ID = 2)
    singletonObj = (undefined4*)FUN_007ab150();
    (*(code**)(*singletonObj))[2](2);

    return this;
}