// FUNC_NAME: NetworkManager::sendMessage

#include <cstdint>

// ----------------------------------------------------------------------------
// Forward declarations for functions called within this function
// ----------------------------------------------------------------------------
void __cdecl FUN_006102c0();  // Probably locks or initializes network state
uint32_t __cdecl FUN_0060c9d0(); // Returns a sequence number or status

// ----------------------------------------------------------------------------
// Global data (assumed declared elsewhere as extern)
// ----------------------------------------------------------------------------
extern void* DAT_01205750;         // Pointer to the singleton NetworkManager object
extern uint32_t* DAT_01205848;     // Pointer to current packet sequence number (global)
extern uint32_t  DAT_0120583c;     // Cached sequence number (for comparison)

// ----------------------------------------------------------------------------
// Reconstructed function
// ----------------------------------------------------------------------------
void __cdecl NetworkManager::sendMessage(int messageType, const void* data, int dataSize)
{
    FUN_006102c0();

    void* networkObj = DAT_01205750; // The singleton NetworkManager instance

    if (messageType == 0x0D)          // Special message type 13 (0x0D)
    {
        if (dataSize != 4)            // For non‑4‑byte payloads
        {
            // If the cached sequence number doesn't match the current global one,
            // call a method to update it (offset 0x1A0 → setSequenceNumber maybe)
            if (DAT_0120583c != *DAT_01205848)
            {
                (**(void (__thiscall**)(void*, uint32_t))((uint8_t*)networkObj + 0x1A0))
                    (networkObj, *DAT_01205848);
                DAT_0120583c = *DAT_01205848;
            }

            // Send the data in a fragmented/chunked manner (offset 0x148)
            // Arguments: (networkObj, chunkSize=4, data, offset=0, totalSize, flags=0, chunkCount)
            uint32_t chunkCount = (dataSize * 2) >> 2;  // Equivalent to (dataSize / 2) in DWORDs
            (**(void (__thiscall**)(void*, int, const void*, int, int, int, uint32_t))
                ((uint8_t*)networkObj + 0x148))
                (networkObj, 4, data, 0, dataSize, 0, chunkCount);
            return;
        }
        else
        {
            // For a 4‑byte payload, fall through to the normal send path after
            // changing the message type to 6
            messageType = 6;
        }
    }

    // Normal send path (offset 0x144)
    uint32_t seqOrStatus = FUN_0060c9d0();   // Obtain sequence number or status
    (**(void (__thiscall**)(void*, int, const void*, uint32_t))
        ((uint8_t*)networkObj + 0x144))
        (networkObj, messageType, data, seqOrStatus);
}