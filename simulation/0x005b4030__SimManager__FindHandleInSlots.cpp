// FUNC_NAME: SimManager::FindHandleInSlots
// Function address: 0x005b4030
// Scans a fixed-size array of 512 int slots at this+0x04 for a specific handle.
// Returns an encoded value: if found, (index & 0xFFFF00) | 1 (low byte = 1, bits[8:15] = block 0 or 1);
// if not found, returns 0x200 (512).

uint __fastcall SimManager::FindHandleInSlots(int this, int handle)
{
    uint index = 0;
    int *slotArray = reinterpret_cast<int *>(reinterpret_cast<uint>(this) + 4); // +0x04: array of 512 int slots

    do
    {
        if (*slotArray == handle)
        {
            // Return success indicator: low bit set, next byte encodes whether index >= 256
            return (index & 0xFFFF00) | 1;
        }
        index++;
        slotArray++;
    } while (index < 0x200);

    // Not found: return 0x200
    return 0x200;
}