// FUNC_NAME: FogSettingsController::FogSettingsController

// Function at 0x00944c80
// Reconstruction: Constructor for FogSettingsController.
// Creates a new FogSettingsController that allocates and initializes an internal FogSettingsData object.
// param_2: likely a region or ID for the fog settings.
// param_3: pointer to another object (e.g., a FogManager or Scene) that provides a default value via a virtual function at vtable+0x0C.

class FogSettingsController {
public:
    // Vtable pointer at +0x00
    // Field +0x04: some ID (passed as param_2)
    // Field +0x08: next? (set to 0)
    // Field +0x0C: pointer to allocated FogSettingsData object

    // +0x00: vtable
    // +0x04: field (param_2)
    // +0x08: field (0)
    // +0x0C: pFogSettingsData (internal shared object)

    // FogSettingsData structure (allocated 0x50 bytes):
    // +0x00: vtable
    // +0x04: refCount (initial 0, incremented)
    // +0x10: field (0)
    // +0x14: field (0)
    // +0x18: field (0)
    // +0x20: four fields (words 4-7) set from global default (_DAT_00d5780c)
    // +0x2C: three fields (words 0xB-0xD) set from global default
    // +0x38: field (0)
    // +0x40: result from virtual call (default handle)

    // Constructor
    void __thiscall FogSettingsController(uint32_t this, uint32_t param_2, int *param_3) {
        // Set vtable for this
        *(this) = &PTR_FUN_00d8b42c; // Vtable for FogSettingsController
        *(this + 4) = param_2;       // Store ID
        *(this + 8) = 0;             // Clear next pointer

        // Allocate FogSettingsData (size 0x50, alignment 0x10)
        void *pData = FUN_004eb390(0x50, 0x10); // Likely operator new with alignment
        uint32_t defaultVal = _DAT_00d5780c;    // Global default (e.g., 0.0f or 1.0f)

        if (pData) {
            // Initialize reference count fields
            *(pData + 4) = 0;        // word1: refCount = 0
            *(pData + 0x20) = 0;     // word8: field at +0x20 = 0
            *(pData + 0x24) = 0;     // word9: field at +0x24 = 0
            *(pData + 0x28) = 0;     // word10: field at +0x28 = 0

            // Fill fields with default value
            *(pData + 0x2C) = defaultVal; // word11 (offset 0x2C)
            *(pData + 0x30) = defaultVal; // word12 (offset 0x30)
            *(pData + 0x34) = defaultVal; // word13 (offset 0x34)
            *(pData + 0x38) = 0;          // word14 (offset 0x38) = 0

            // More default fills (words 4,5,6,7 at offsets 0x10-0x1C)
            *(pData + 0x10) = defaultVal; // word4
            *(pData + 0x14) = defaultVal; // word5
            *(pData + 0x18) = defaultVal; // word6
            *(pData + 0x1C) = defaultVal; // word7

            // Set vtable for the data object
            *(pData) = &PTR_FUN_00d8b41c; // Vtable for FogSettingsData
        }

        // Call virtual function on param_3 object (vtable+0x0C) to get a default handle
        uint32_t handle = (**(code **)(*param_3 + 0xC))();
        if (pData) {
            *(pData + 0x40) = handle; // Store handle at word16 (offset 0x40)
        }

        // Store pointer to data object in this
        *(this + 0x0C) = pData;

        // Increment reference count on data object (word1)
        if (pData) {
            *(pData + 4) += 1; // refCount++
        }

        return this;
    }
};