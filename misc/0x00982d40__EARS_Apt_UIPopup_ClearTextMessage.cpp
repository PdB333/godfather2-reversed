// Xbox PDB: EARS_Apt_UIPopup_ClearTextMessage
// FUNC_NAME: NPCDialogManager::clearPendingDialog
void __thiscall clearPendingDialog(NPCDialogManager* thisPtr)
{
    // Offset +0x91: pendingDialogFlag (byte)
    thisPtr->pendingDialogFlag = 0;

    // Register clear text message event
    // Parameters: eventName, param2, someGlobal, param4
    registerEvent("ClearTextMessage", 0, &DAT_00d90628, 0);

    undefined4 local_c = DAT_01130480;
    undefined4 local_8 = 0;
    undefined4 local_4 = 0;
    memClear(&local_c, 0); // likely clears some temporary struct

    // Check flags at +0x68, +0x6c, +0x7c (offsets 0x1a, 0x1b, 0x1f * 4)
    if ((thisPtr->dialogActiveFlag1 == 0) && 
        (thisPtr->dialogActiveFlag3 == 0) && 
        (thisPtr->dialogActiveFlag2 == 0)) 
    {
        // Set callback to label (likely a function pointer table entry)
        setCallback(thisPtr + 4, &LAB_00982b20, 1);

        // Call virtual function at vtable offset 0x2c (index 11)
        (thisPtr->vtable[11])();
    }
}