// FUNC_NAME: Entity::registerWithManager
void __fastcall Entity::registerWithManager(Entity* thisObj)
{
    int localResult;
    int* piVar1;
    int iVar2;
    char cVar3;
    int uVar4;
    uint uVar6;
    int local_4;

    iVar2 = gWorldManager; // DAT_0112aa9c
    local_4 = 0;
    cVar3 = Entity::canRegister(thisObj); // FUN_006f9180
    if (cVar3 != '\0') {
        uVar4 = Entity::allocateHandle(*(int*)(thisObj + 0xc), &local_4); // FUN_006fb2b0
        *(int*)(thisObj + 0x2c) = uVar4;
        // Expand the array if full
        if (*(int*)(iVar2 + 0x20) == *(int*)(iVar2 + 0x24)) { // size == capacity
            int newCapacity;
            if (*(int*)(iVar2 + 0x24) == 0) {
                newCapacity = 1;
            } else {
                newCapacity = *(int*)(iVar2 + 0x24) * 2;
            }
            WorldManager::resizeArray(newCapacity); // FUN_006f9120
        }
        piVar1 = (int*)(*(int*)(iVar2 + 0x1c) + *(int*)(iVar2 + 0x20) * 4); // &array[size]
        *(int*)(iVar2 + 0x20) = *(int*)(iVar2 + 0x20) + 1; // size++
        if (piVar1 != (int*)0x0) {
            *piVar1 = (int)thisObj;
        }
        // Set handle flags
        HandleSystem::setFlag(*(int*)(thisObj + 0xc), 2, (int)thisObj); // FUN_004035f0
        HandleSystem::setFlagMask(*(int*)(thisObj + 0xc), 0x40, gWorldManager); // FUN_004035c0
        HandleSystem::setFlag(*(int*)(thisObj + 0xc), 4, gWorldManager); // FUN_004035f0
        // Process child list
        uVar6 = 0;
        if (*(int*)(thisObj + 0x24) != 0) { // childCount
            do {
                iVar2 = *(int*)(*(int*)(thisObj + 0x20) + uVar6 * 8); // childArray[i]
                if ((iVar2 != 0) && (iVar2 != 0x48)) {
                    Entity::notifyChild(*(int*)(thisObj + 0x2c), local_4); // FUN_0072cf20
                }
                uVar6 = uVar6 + 1;
            } while (uVar6 < *(uint*)(thisObj + 0x24));
        }
    }
    return;
}