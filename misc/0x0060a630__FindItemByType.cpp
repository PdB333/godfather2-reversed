// FUNC_NAME: FindItemByType
uint FindItemByType(int playerIndex, int targetType)
{
    int *pManager = *(int **)(&g_PlayerManagers + playerIndex * 0x10);
    uint result = 0;
    if (pManager != (int *)0x0) {
        uint count; // local_44
        uint *pData = &count; // puStack_5c
        (**(code **)(*pManager + 0x14))(pManager); // presumably sets count via pData pointer
        if (count != 0) {
            do {
                uint itemId = (**(code **)(**(int **)(&g_PlayerManagers + playerIndex * 0x10) + 0x20))
                             (*(int **)(&g_PlayerManagers + playerIndex * 0x10), 0, uVar4); // 0 might be a constant flag
                // get item data into buffers
                uint dataBuffer[2]; // auStack_4c[8] but we extract fields after
                (**(code **)(**(int **)(&g_PlayerManagers + playerIndex * 0x10) + 0x18))
                         (*(int **)(&g_PlayerManagers + playerIndex * 0x10), itemId, dataBuffer, &pData);
                // Now pData points to a struct: count, uStack_40, uStack_38, uStack_34, bStack_30, iStack_2c
                int itemTypeField = *(int *)(pData + 1);  // uStack_40
                if ((targetType == FUN_0060d740(itemTypeField)) && (result == 0)) {
                    uint field1 = *(uint *)(pData + 2); // uStack_38
                    uint field2 = *(uint *)(pData + 3); // uStack_34
                    byte field3 = *(byte *)(pData + 4); // bStack_30
                    int flags = *(int *)(pData + 5);   // iStack_2c
                    if ((flags != 1) && (flags != 2)) {
                        result = ((uint)field3 << 8 | field2) << 8 |
                                 -(uint)((&g_PlayerFlags)[playerIndex * 0x10] != '\0') & 0x80000000 |
                                 field1;
                    }
                }
                uVar4++;
            } while (uVar4 < count);
        }
        return result;
    }
    return 0;
}