//FUNC_NAME: GodfatherGameManager::updateEntityListWithFlag
void __thiscall GodfatherGameManager::updateEntityListWithFlag(int thisPtr, char isActive)
{
    uint index = 0;
    extern bool g_bUpdateFlag; // global flag set based on comparison

    if (isActive != '\0') {
        int currentId = FUN_00977420(); // likely returns current player/entity ID
        g_bUpdateFlag = true;
        if (*(int *)(thisPtr + 0x2c78) == currentId) // +0x2c78: stored entity ID
            goto LAB_00785dd8;
    }
    g_bUpdateFlag = false;

LAB_00785dd8:
    if (*(int *)(thisPtr + 0x1a3c) != 0) { // +0x1a3c: count of entities in list
        int* entityList = (int*)(thisPtr + 0x193c); // +0x193c: array of entity pointers
        do {
            int entityValue = FUN_00784ec0(*entityList); // get some value from entity
            FUN_00788990(g_bUpdateFlag, entityValue); // apply flag to entity
            index++;
            entityList++;
        } while (index < *(uint *)(thisPtr + 0x1a3c));
    }
}