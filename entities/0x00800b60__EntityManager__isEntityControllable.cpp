// FUNC_NAME: EntityManager::isEntityControllable
int __thiscall EntityManager::isEntityControllable(EntityManager* thisPtr) {
    int entityHandle; // [esp+0h] [ebp-4h]
    int entityIndex; // [esp+0h] [ebp-4h]

    // +0x74c: current entity handle (e.g., slot index or pointer offset)
    // +0x8e0: bitfield flags (bit 10 = controllable flag)
    if ((*(int*)((int)thisPtr + 0x74c) != 0) &&
        (*(int*)((int)thisPtr + 0x74c) != 0x48)) {
        if (*(int*)((int)thisPtr + 0x74c) == 0) {
            entityIndex = 0;
        } else {
            entityIndex = *(int*)((int)thisPtr + 0x74c) - 0x48;
        }
        // +0x1a8 in entity data: byte flag indicating "active"
        if (((*(char*)(entityIndex + 0x1a8) == 1) &&
             (*(int*)((int)thisPtr + 0x74c) != 0) &&
             (*(int*)((int)thisPtr + 0x74c) != 0x48)) &&
            ((*(unsigned int*)((int)thisPtr + 0x8e0) >> 10 & 1) != 0)) {
            return FUN_00701050(); // returns success code (likely 1)
        }
    }
    return 0;
}