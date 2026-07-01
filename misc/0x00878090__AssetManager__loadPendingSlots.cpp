// FUNC_NAME: AssetManager::loadPendingSlots
//
// Function address: 0x00878090
// This method iterates over a list of asset GUID slots and loads any
// unloaded assets (except for null or sentinel GUIDs). Returns the total
// number of slots that are either already loaded or newly loaded.
//
// Class layout (offsets from this):
// +0x2BC : m_numSlots (uint32)
// +0xA4C : m_slotPtrs[] (array of int, each is handle to loaded asset)
// +0xA5C : m_slotGUIDs[] (array of 128-bit GUIDs, each 4 ints)
// The constant sentinel GUID (0xBAEBDBBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911)
// and the all-zero GUID are skipped.
//
// Callees (fastcall):
//   FUN_00446100 (ResolveGUID) – takes pointer to GUID, returns something
//   FUN_00792900 (GetAssetFromGUID) – takes (resolveResult + 0x50), returns asset handle
//   FUN_00790110 (NotifyAssetLoaded) – increments a reference count or similar

#include <cstdint>

int __fastcall AssetManager::loadPendingSlots(int thisPtr)
{
    int count = 0;
    int numSlots = *(int*)(thisPtr + 0x2BC);

    if (numSlots != 0)
    {
        int* slotPtrs = (int*)(thisPtr + 0xA4C);           // array of loaded asset handles
        int* guidBase = (int*)(thisPtr + 0xA5C);           // base of 16‑byte GUID array

        // Sentinels: a specific non‑zero GUID and the all‑zero GUID
        const int sentinelGUID[4] = {
            -0x45245246,  // 0xBAEBDBBA
            -0x41104111,  // 0xBEEFBEEF
            -0x153EA5AB,  // 0xEAC15A55
            -0x6EEFF6EF   // 0x91100911
        };

        for (uint32_t i = 0; i < (uint32_t)numSlots; i++)
        {
            int* guid = guidBase + i * 4;   // each GUID is 4 ints

            if (slotPtrs[i] == 0)
            {
                // Check if this GUID is one of the two sentinels
                bool isSentinel = (guid[0] == sentinelGUID[0] && guid[1] == sentinelGUID[1] &&
                                   guid[2] == sentinelGUID[2] && guid[3] == sentinelGUID[3]);
                bool isZero = (guid[0] == 0 && guid[1] == 0 && guid[2] == 0 && guid[3] == 0);

                if (!isSentinel && !isZero)
                {
                    int resolveResult = FUN_00446100(guid, 0);   // resolve GUID → some handle
                    if (resolveResult != 0)
                    {
                        int assetHandle = FUN_00792900(resolveResult + 0x50);
                        if (assetHandle != 0)
                        {
                            slotPtrs[i] = assetHandle;
                            FUN_00790110(1);                          // notify load completed
                            *(uint32_t*)(assetHandle + 0x5C) |= 0x100000; // set some flag
                            count++;
                        }
                    }
                }
            }
            else
            {
                count++;
            }
        }
    }

    return count;
}