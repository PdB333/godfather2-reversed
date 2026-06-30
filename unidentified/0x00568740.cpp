// FUN_NAME: SystemManager::shutdown
void __thiscall SystemManager::shutdown(SystemManager *this)
{
    // Reset global singleton flags
    DAT_0119a5b4 = 0;  // global singleton flag
    DAT_01198e7c = 0;  // another global singleton flag

    // Clear internal state
    this->someFlag = 0;           // +0x08
    // Reset the subsystem pointer
    FUN_00c796e0(this->subsystem, 0, 0, 0); // clear / reset subsystem (likely ResourceManager::clear)
    // Call virtual shutdown hook (vtable offset 0x0c)
    (*(void (__thiscall **)(SystemManager *))(*(int *)this + 0x0c))();
    // Destroy the subsystem
    FUN_00c7a7c0(this->subsystem); // free subsystem memory
    this->subsystem = 0;          // +0x04
    this->anotherFlag = 0;        // +0x0c (or last field)
}