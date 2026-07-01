// FUNC_NAME: CrewManager::CrewManager (constructor)
undefined4 * __thiscall CrewManager::CrewManager(undefined4 *thisObj, undefined4 param_2, undefined4 param_3)
{
    int gameManager;
    undefined4 *managerPtr;

    // Call base class constructor (likely Entity or Manager base)
    BaseClass::BaseClass(param_2, param_3);

    // Set vtable pointer for this class
    *thisObj = &PTR_LAB_00d6e610;  // vtable for CrewManager

    // Initialize flag byte at offset +0x1d to 0
    *(uint8_t *)(thisObj + 0x1d) = 0;

    // Get global manager instance (e.g., GameManager::getInstance)
    gameManager = GameManager::getInstance();
    // Store something from manager's offset +4 into thisObj's offset +0x78
    thisObj[0x1e] = *(undefined4 *)(gameManager + 4);

    // Re-get manager pointer and call a vtable function with argument 63
    managerPtr = (undefined4 *)GameManager::getInstance();
    (*(code *)(*managerPtr))(0x3f);  // calls Manager::setSomeState(63)

    // Check a flag in an object pointed to by thisObj[0x16] (offset +0x58)
    // The flag is at offset 0x238 * 4 = 0x8E0 in that object, bit 10
    if (((uint)((int *)thisObj[0x16])[0x238] >> 10 & 1) != 0) {
        // If bit is set, call another vtable function at offset 0x260 on that object
        (*(code *)(*(int *)thisObj[0x16] + 0x260))();
        // Set the flag byte at +0x1d to 1
        *(uint8_t *)(thisObj + 0x1d) = 1;
    }

    return thisObj;
}