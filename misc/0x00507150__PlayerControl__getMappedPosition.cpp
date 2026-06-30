// FUNC_NAME: PlayerControl::getMappedPosition
int PlayerControl::getMappedPosition(float &outSecond)
{
    // Retrieve a pointer to the manager object (global singleton).
    int *managerPtr = reinterpret_cast<int *>(FUN_00505c90(g_SomeManager));
    if (managerPtr == nullptr)
        return 0; // No manager available

    // Dereference offset +0x08 to get a data block (likely input state).
    int *dataBlock = reinterpret_cast<int *>(managerPtr[2]); // offset +0x08 (since sizeof(int)=4)
    if (dataBlock == nullptr)
        return -1;

    // Check if the data block is active (byte at +0x1E).
    if (reinterpret_cast<char *>(dataBlock)[0x1E] == 0)
        return -1;

    if (g_useRawMode)
    {
        // Raw mode: convert two byte values (at +0x1C and +0x1D) to scaled floats.
        uint8_t rawX = reinterpret_cast<uint8_t *>(dataBlock)[0x1C];
        uint8_t rawY = reinterpret_cast<uint8_t *>(dataBlock)[0x1D];

        // Write to the first float of this object (offset +0x00).
        m_firstFloat = (static_cast<float>(rawX) + g_constantAdd) * g_scaleX;

        // Write the second float to the caller‑provided reference.
        outSecond = (static_cast<float>(rawY) + g_constantAdd) * g_scaleY;
    }
    else
    {
        // Non‑raw mode: read a pre‑stored float at +0x24.
        m_firstFloat = *reinterpret_cast<float *>(reinterpret_cast<uint8_t *>(dataBlock) + 0x24);
        // outSecond is intentionally left unmodified.
    }
    return 1;
}