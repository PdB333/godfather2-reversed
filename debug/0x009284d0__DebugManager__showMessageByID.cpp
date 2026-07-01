// FUNC_NAME: DebugManager::showMessageByID
void __fastcall DebugManager::showMessageByID(DebugManager* this)
{
    // +0x5c: message ID (int)
    int msgID = *(int*)((char*)this + 0x5c);
    switch(msgID)
    {
        case 0:
            // Display message for ID 0
            FUN_00402050(&DAT_01130300, 0);
            return;
        case 1:
            FUN_00402050(&DAT_011303c0, 0);
            return;
        case 2:
            FUN_00402050(&DAT_01130280, 0);
            return;
        case 3:
            FUN_00402050(&DAT_011301c8, 0);
            return;
        case 4:
            FUN_00402050(&DAT_011301a0, 0);
            return;
        case 5:
            FUN_00402050(&DAT_011304c0, 0);
            return;
        case 6:
            FUN_00402050(&DAT_01130250, 0);
            return;
        case 7:
            FUN_00402050(&DAT_011304b8, 0);
            return;
        case 8:
            FUN_00402050(&DAT_011302d8, 0);
            return;
        case 9:
            FUN_00402050(&DAT_011304e0, 0);
            return;
        case 10:
            FUN_00402050(&DAT_01130490, 0);
            break; // fall through? Actually break after call; follow original
        case 0xffffffff:
            FUN_00402050(&DAT_01130278, 0);
            return;
    }
    return;
}