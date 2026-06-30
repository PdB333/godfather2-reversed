// FUNC_NAME: PresentationManager::openScreenOnce
void PresentationManager::openScreenOnce(void)
{
    int32_t screenId;
    
    // Check if screen has already been opened (bit 2 at offset 0x4a)
    if ((*(uint8 *)((uintptr_t)this + 0x4a) & 4) == 0)
    {
        // Call virtual method at vtable index 1 (vtable ptr at +0x10) to get screen ID
        screenId = (**(code **)(*(int *)((uintptr_t)this + 0x10) + 4))();
        
        // Store screen ID as big-endian bytes in global buffer
        g_screenDataBuffer[0] = (screenId >> 24) & 0xFF;
        g_screenDataBuffer[1] = (screenId >> 16) & 0xFF;
        g_screenDataBuffer[2] = (screenId >> 8) & 0xFF;
        g_screenDataBuffer[3] = screenId & 0xFF;
        g_screenDataBuffer[4] = 0; // null-terminate for string safety
        
        // Open the screen with name "OpenScreen" on layer 0, root "_root", flag 1, passing screen data
        UI_OpenScreen("OpenScreen", 0, "_root", 1, &g_screenDataBuffer);
        
        // Mark screen as opened (set bit 2 at offset 0x4a)
        *(uint16 *)((uintptr_t)this + 0x4a) |= 4;
    }
    return;
}