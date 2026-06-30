// FUNC_NAME: InputDeviceManager::setupControllerSlotMapping
// Address: 0x005376e0
// Sets up global pointers to per‑slot data structures based on controller index (ECX) and player index (EDX)

void __fastcall InputDeviceManager::setupControllerSlotMapping(uint32 controllerIndex, uint32 playerIndex)
{
    // Read device ID mappings from global arrays
    // DAT_0121b658: playerIndex -> deviceId     (+0x??)
    // DAT_0121b6b8: controllerIndex -> someId   (+0x??)
    *reinterpret_cast<int*>(0x0121a390) = *reinterpret_cast<int*>(0x0121b658 + playerIndex * 4);
    *reinterpret_cast<int*>(0x0121a394) = *reinterpret_cast<int*>(0x0121b6b8 + controllerIndex * 4);

    // For controllerIndex > 15 (e.g. keyboard/mouse), set large struct pointers
    if (0xF < controllerIndex) {
        // DAT_01219e64: base of large per‑slot array (0x5c bytes each)
        *reinterpret_cast<void**>(0x0121b0a4) = reinterpret_cast<void*>(0x01219e64 + controllerIndex * 0x5c);
        // DAT_0121a8a4: base of small per‑slot array (0x14 bytes each)
        *reinterpret_cast<void**>(0x0121b0a8) = reinterpret_cast<void*>(0x0121a8a4 + controllerIndex * 0x14);
    }

    // Always set pointer to medium per‑slot array based on controllerIndex (0x2c bytes each)
    // DAT_0121ab24: base of medium array
    *reinterpret_cast<void**>(0x0121b0ac) = reinterpret_cast<void*>(0x0121ab24 + controllerIndex * 0x2c);

    // Set pointer to per‑player array based on playerIndex (0x30 bytes each)
    // DAT_0121b1b8: base of player array
    *reinterpret_cast<void**>(0x0121b63c) = reinterpret_cast<void*>(0x0121b1b8 + playerIndex * 0x30);

    // Clear a flag at +0x14 relative to the player array pointer
    *reinterpret_cast<int*>(0x0121b638) = 0;
}