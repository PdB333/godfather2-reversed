// FUNC_NAME: Entity::getComponentByType
int __thiscall Entity::getComponentByType(int thisPtr, int param2)
{
    int componentPtr;
    
    switch(*(int*)(thisPtr + 0x84)) // +0x84: component type/ID
    {
    case 1:
    case 4:
        if (param2 == 0)
            return 0;
        componentPtr = thisPtr->getOwner(); // FUN_00718480
        return componentPtr;
    case 2:
    case 5:
        componentPtr = thisPtr->getOwner();
        if (componentPtr != 0)
            componentPtr = findComponentByHash(componentPtr, 0x383225a1); // FUN_006c9470
        return componentPtr;
    case 3:
    case 6:
        if (param2 == 0)
            return 0;
        componentPtr = SimManager::getInstance(g_pSimManager); // FUN_0043b870(DAT_01131074)
        if (componentPtr != 0)
            componentPtr = getActiveComponent(componentPtr); // FUN_007631c0
        break;
    case 7:
    case 8:
        if (param2 == 0)
            return 0;
        componentPtr = GameManager::getInstance(g_pGameManager); // FUN_0043b870(DAT_01131040)
        if (componentPtr == 0)
            return 0;
        if (*(int*)(componentPtr + 0x1c) != 0) // +0x1c: some pointer field
            return *(int*)(componentPtr + 0x1c) - 0x48; // back to containing struct
    }
    return 0;
}