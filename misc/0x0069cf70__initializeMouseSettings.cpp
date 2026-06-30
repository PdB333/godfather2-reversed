// FUNC_NAME: initializeMouseSettings
void initializeMouseSettings(void)
{
    uint32_t mouseKeys = DAT_00e50b4c; // +0x00: Mouse parameters (e.g., threshold/speed)
    if ((DAT_00e50b50 & 1) == 0)       // Check if not yet initialized (bit0 clear)
    {
        uint32_t flags = DAT_00e50b50 & 0xFFFFFFF3; // Clear bits 2 and 3 (unused?);
        // Set mouse parameters (SPI_SETMOUSE with 8-byte structure)
        SystemParametersInfoA(0x3b, 8, &mouseKeys, 0);
    }
}