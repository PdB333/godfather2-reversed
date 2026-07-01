//FUNC_NAME: GodfatherGameManager::handleMessage
void __thiscall GodfatherGameManager::handleMessage(int thisPtr, int param2, int param3)
{
    char isValid;
    int allocHandle;
    undefined8* pData;
    // Stack-based message structure
    struct {
        undefined4 field_0;      // local_30
        undefined*** field_4;    // local_2c
        undefined1 field_8;      // local_28
        undefined** field_c;     // local_24
        undefined4 field_10;     // local_20
        int field_14[2];         // local_1c
        undefined8 field_1c;     // local_14
        undefined4 field_24;     // local_c
        undefined1 field_28;     // local_8
        undefined4 field_2c;     // local_4
    } msgStruct;

    // Check message ID and target
    if ((param3 == -0x30039ce1) && (param2 != 0)) {
        // Allocate something (size 2)
        allocHandle = FUN_008c6d20(2);
        isValid = FUN_0043c6c0(param2, allocHandle);
        if ((isValid != '\0') && (*(int*)(thisPtr + 0x2c64) != 0)) {
            // Initialize message structure
            msgStruct.field_24 = 0;
            msgStruct.field_1c = 0;
            msgStruct.field_c = &PTR_FUN_00d5dbbc;  // Function pointer table
            msgStruct.field_14[0] = 0;
            msgStruct.field_14[1] = 0;
            msgStruct.field_28 = 0;
            msgStruct.field_2c = DAT_01205228;       // Global data
            msgStruct.field_10 = 0x4fc909c8;         // Magic constant (message type?)

            // Get singleton data
            pData = (undefined8*)FUN_00788340();
            msgStruct.field_28 = 1;
            msgStruct.field_1c = *pData;
            msgStruct.field_24 = *(undefined4*)(pData + 1);

            // Set up pointer chain
            msgStruct.field_4 = &msgStruct.field_c;
            msgStruct.field_0 = DAT_0112ad8c;        // Another global
            msgStruct.field_8 = 0;

            // Process the message (param2+0x3c is likely a sub-object offset)
            FUN_00408bf0(&msgStruct.field_0, param2 + 0x3c, 0);

            // Cleanup if needed
            if (msgStruct.field_14[0] != 0) {
                FUN_004daf90(msgStruct.field_14);
            }
        }
    }
    return;
}