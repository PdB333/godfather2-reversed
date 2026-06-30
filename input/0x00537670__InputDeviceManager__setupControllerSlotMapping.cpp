// FUNC_NAME: InputDeviceManager::setupControllerSlotMapping
void __fastcall InputDeviceManager::setupControllerSlotMapping(int slotIndex, int playerIndex)
{
    // Set the global controller data pointer for the given slot (slotIndex * 4)
    s_controllerSlotData = *(int*)(s_controllerDataBase + slotIndex * 4); // DAT_0121b640
    // Set the global player-specific data pointer for the given playerIndex
    s_playerActiveData = *(int*)(s_playerDataBase + playerIndex * 4);    // DAT_0121b6b8

    // For extra player indices (beyond the first 16), allocate additional structures
    if (playerIndex > 15) {
        s_extraPlayerState = (ExtraPlayerState*)(s_extraPlayerStateBase + playerIndex * 0x5c); // DAT_01219e64
        s_extraPlayerInfo  = (ExtraPlayerInfo*)(s_extraPlayerInfoBase  + playerIndex * 0x14); // DAT_0121a8a4
    }

    // Set the main player configuration block (size 0x2c)
    s_playerConfig = (PlayerConfig*)(s_playerConfigBase + playerIndex * 0x2c); // DAT_0121ab24

    // Set the controller-specific state block for this slot (size 0x2c)
    s_controllerState = (ControllerState*)(s_controllerStateBase + slotIndex * 0x2c); // DAT_0121b0b0

    // Clear the initialization flag (or next slot pointer)
    s_nextSlot = 0; // DAT_0121b63c
}