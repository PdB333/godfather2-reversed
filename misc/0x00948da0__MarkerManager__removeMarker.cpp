// FUNC_NAME: MarkerManager::removeMarker
void __fastcall MarkerManager::removeMarker(MarkerManager* this) {
    // Check if marker is active (bit 17 at offset 0x11c)
    if ((*(uint32_t*)((uint8_t*)this + 0x11c) >> 0x11) & 1) {
        // Send command to remove the marker
        FUN_005a04a0("RemoveMarker", 0, &DAT_00d8b2cc, 1, (uint8_t*)this + 8);
        // Clear the marker active flag
        *(uint32_t*)((uint8_t*)this + 0x11c) &= 0xFFFDFFFF;
    }
}