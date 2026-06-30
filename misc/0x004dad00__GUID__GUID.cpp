// FUNC_NAME: GUID::GUID
// Function address: 0x004dad00
// Constructs a GUID from either a hardcoded null GUID, from another GUID source, or from a registry-like system.
// The GUID structure consists of: 4-byte type at offset 0x00, 16-byte GUID data at offset 0x04,
// flags at offsets 0x0B (byte), 0x13 (dword), and pointer at offset 0x50.

#include <cstdint>

// Forward declarations of internal helpers (not shown)
extern bool isGuidAvailable(); // FUN_004da910
extern void guidFromRegistryData(void* dest, uint32_t* src1, uint32_t src2); // FUN_004d9080
extern void loadGuidFromRegistry(char* buffer); // FUN_004d9d60
extern void processGuid(); // FUN_004d9ff0
extern void cleanupGuid(); // FUN_004da530
extern void releaseMemory(void* ptr); // FUN_009c8eb0
extern void finalizeGuid(); // FUN_004d8be0

class GUID {
public:
    // Constructor: this = param_1, pOtherGuid = param_2
    GUID(GUID* pOtherGuid = nullptr) {
        // Step 1: Pre-fill with hardcoded invalid GUID string
        // "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}" 
        // This is a known "bad" UUID for EA EARS engine.
        const char* pSrc = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}";
        // Copy the 48-byte GUID string into the data area (starting at offset +4)
        // The loop copies 9 times 4 bytes, then 2 more bytes, then 1 more byte.
        int* pDst = reinterpret_cast<int*>(this);
        for (int i = 0; i < 9; ++i) {
            *(pDst + 1) = *reinterpret_cast<const int*>(pSrc);
            pSrc += 4;
            pDst++;
        }
        // Write the last 3 bytes
        *reinterpret_cast<uint16_t*>(pDst + 0) = *reinterpret_cast<const uint16_t*>(pSrc);
        *reinterpret_cast<char*>(reinterpret_cast<char*>(pDst) + 6) = pSrc[2];

        // Set flag at offset 0x0B to 1 (part of the GUID data area)
        *(reinterpret_cast<char*>(this) + 0x0B) = 1;
        // Set unknown dword at offset 0x13 (19) to 0
        *(reinterpret_cast<int*>(this) + 0x13) = 0;  // Actually offset 0x4C if int* arithmetic

        if (pOtherGuid == nullptr) {
            // Null or default GUID: type = 2, and store a static pointer
            *(reinterpret_cast<int*>(this) + 0x00) = 2;               // GUID type: 2 means null
            *(reinterpret_cast<int*>(this) + 0x14) = 0x00e36e5c;      // Pointer to a static "null" GUID data
        } else {
            // Check availability of GUID source
            if (isGuidAvailable()) {
                // Source found: mark as type 0 and copy data from the source
                *(reinterpret_cast<int*>(this) + 0x00) = 0;           // GUID type: 0 means from source
                // Use provided source to construct GUID data
                // FUN_004d9080 writes to a local buffer; then copy into this
                char localBuffer[20];
                guidFromRegistryData(&localBuffer, pOtherGuid->data, pOtherGuid->data[1]);
                // Copy the 16 GUID bytes from localBuffer to this's data area (starting at offset +4)
                int* pSrc2 = reinterpret_cast<int*>(&localBuffer);
                int* pDst2 = reinterpret_cast<int*>(this) + 1;  // offset of data
                for (int i = 0; i < 9; ++i) {
                    *pDst2 = *pSrc2;
                    pDst2++;
                    pSrc2++;
                }
                *reinterpret_cast<uint16_t*>(pDst2) = *reinterpret_cast<uint16_t*>(pSrc2);
                *reinterpret_cast<char*>(reinterpret_cast<char*>(pDst2) + 2) 
                    = *reinterpret_cast<char*>(reinterpret_cast<char*>(pSrc2) + 2);
            } else {
                // No source available: mark as type 1 (random or generated)
                *(reinterpret_cast<int*>(this) + 0x00) = 1;           // GUID type: 1
                // Load default GUID from registry-like data
                loadGuidFromRegistry(reinterpret_cast<char*>(this) + 4); // assumes write to data area
                processGuid(); // possibly finalize or set extra flags
                // If a temporary allocation exists, free it
                int* pTemp = reinterpret_cast<int*>(&localBuffer[0x10]); // offset used for temp pointer
                if (*pTemp != 0) {
                    cleanupGuid();
                    releaseMemory(reinterpret_cast<void*>(*pTemp));
                }
            }
            // Final cleanup: free a previously stored pointer at offset 0x2C
            int* pAlloc = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x2C);
            if (*pAlloc != 0) {
                finalizeGuid();
                releaseMemory(reinterpret_cast<void*>(*pAlloc));
            }
        }
    }

private:
    // Layout (offsets from this):
    // +0x00: uint32_t type;  // 0, 1, or 2
    // +0x04: uint8_t guidData[16]; // actual bytes
    // +0x0B: part of guidData (byte flag set to 1)
    // +0x13: uint32_t unknownFlag; // set to 0
    // +0x14: uint32_t* staticDataPtr; // for type 2
    // +0x2C: void* allocation; // for cleanup
    // Note: The actual offsets might differ; this is a best reconstruction.
};