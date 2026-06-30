// FUNC_NAME: Entity::initialize
int __thiscall Entity::initialize(void *thisPtr, char isManaged) {
    int *manager; // eax, from global
    manager = DAT_01205228; // g_EntityManager or similar global singleton

    if (thisPtr != 0) {
        *(int *)((int)thisPtr + 0x2c) = (int)manager; // store manager pointer at +0x2c
        FUN_0071bfd0(manager); // likely manager->addRef() or registerObject()
        *(unsigned short *)((int)thisPtr + 0x3c) |= 2; // set flag bit 1 (e.g., kInitialized)
        if (isManaged != 0) {
            *(unsigned short *)((int)thisPtr + 0x3c) |= 8; // set flag bit 3 (e.g., kManaged)
        }
    }
    return (int)thisPtr;
}