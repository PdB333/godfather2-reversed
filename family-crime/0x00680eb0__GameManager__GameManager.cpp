// FUNC_NAME: GameManager::GameManager
int __thiscall GameManager::GameManager(GameManager *this, unsigned char constructorFlags)
{
    undefined4 *vtablePtr;

    if (this == (GameManager *)0x0) {
        vtablePtr = (undefined4 *)0x0;
    } else {
        vtablePtr = (undefined4 *)((int)this + 0x20);
    }
    *vtablePtr = &s_vtable_0x00d580fc;          // Set vtable at +0x20 (derived class vtable)
    g_initializedFlag = 0;                       // Reset global initialization flag
    BaseClass::BaseClass();                      // Call base class constructor (FUN_007edfb0)
    if ((constructorFlags & 1) != 0) {
        GameManager::postConstruct(this);        // Second-stage initialization (FUN_009c8eb0)
    }
    return (int)this;
}