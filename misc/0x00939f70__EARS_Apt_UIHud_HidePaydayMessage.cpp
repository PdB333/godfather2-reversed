// Xbox PDB: EARS_Apt_UIHud_HidePaydayMessage
// FUNC_NAME: UIPaydayManager::hidePaydayMessage
void __thiscall UIPaydayManager::hidePaydayMessage(char hideType) {
    // Select animation data based on hide type
    void* hideAnimationData = (hideType == '\0') ? (void*)&DAT_00e36da0 : (void*)&DAT_00e36d94;

    // Send command to hide the payday message with the chosen animation
    FUN_005a04a0("HidePaydayMessage", 0, &DAT_00d8a64c, 1, hideAnimationData);

    // Retrieve global payday message instance and clean it up
    struct PaydayMessageData {
        int32_t instance; // +0x00 likely pointer or handle
        int32_t padding0; // +0x04
        uint8_t padding1; // +0x08
    } msgData;

    msgData.instance = DAT_011304d0; // global payday message object
    msgData.padding0 = 0;
    msgData.padding1 = 0;

    // Destroy or reset the payday message data
    FUN_00408a00(&msgData, 0);
}