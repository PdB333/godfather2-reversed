// FUNC_NAME: GuidObject::guidConstructor
class GuidObject {
public:
    uint32_t type;          // +0x00
    char guid[39];          // +0x04 (null-terminated GUID string)
    uint8_t field_0x2C;     // +0x2C (set to 1 in constructor)
    uint32_t field_0x4C;    // +0x4C (set to 0 in constructor)
    void* defaultData;      // +0x50 (only set when other == NULL)

    GuidObject(GuidObject* other);
};

// Constructor at 0x004dad00
GuidObject::GuidObject(GuidObject* other)
{
    char initResult[20];             // local_40 - buffer for initialization status
    int32_t heapAllocation1;         // local_2c - pointer to allocated memory
    char generatedGuid[39];          // local_28 - buffer for GUID generation (size from copy logic)
    int32_t heapAllocation2;         // local_8  - another allocation pointer

    const char* defaultGuid = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}";

    // Copy the default GUID string into this->guid (skipping the type field at offset 0)
    char* src = (char*)defaultGuid;
    uint32_t* dest = (uint32_t*)(this->guid);
    for (int i = 0; i < 9; i++) {
        *dest = *(uint32_t*)src;
        src += 4;
        dest++;
    }
    *(uint16_t*)dest = *(uint16_t*)src; src += 2;
    *(char*)((uint8_t*)dest + 2) = *src;  // copy last byte (null terminator)

    // Initialize internal fields
    *(uint8_t*)(this->guid + 0x28) = 1;    // offset 0x2C? Actually (param_1+0xb) gives byte at offset 0x2C
    this->field_0x4C = 0;                  // param_1[0x13] = 0

    if (other == NULL) {
        // Default case: set type to 2 and store a static data pointer
        this->type = 2;
        this->defaultData = (void*)0x00e36e5c;  // DAT_00e36e5c (some global data)
    } else {
        // Initialize system/global state (likely prepares initResult)
        FUN_004da910();

        if (initResult[0] == 0x01) {
            // Copy GUID from 'other' object into generatedGuid buffer
            this->type = 0;
            // FUN_004d9080 builds a GUID from two 32-bit parts of other's header
            FUN_004d9080(generatedGuid, other->type, other->guid[0]); // first two dwords of other object

            // Copy generatedGuid into this->guid (starting at offset 4, since type already set)
            uint32_t* srcGuid = (uint32_t*)generatedGuid;
            uint32_t* destGuid = (uint32_t*)(this->guid);
            for (int i = 0; i < 9; i++) {
                *destGuid = *srcGuid;
                srcGuid++;
                destGuid++;
            }
            *(uint16_t*)destGuid = *(uint16_t*)srcGuid;
            *(char*)((uint8_t*)destGuid + 2) = *(char*)((uint8_t*)srcGuid + 2);
        } else {
            // Generate a new GUID via other functions
            this->type = 1;
            FUN_004d9d60(initResult);  // initResult used as seed/state
            FUN_004d9ff0();            // generation step

            // Free any existing heap allocations
            if (heapAllocation2 != 0) {
                FUN_004da530();        // cleanup
                FUN_009c8eb0(heapAllocation2); // operator delete
            }
        }

        // Free additional allocations if present
        if (heapAllocation1 != 0) {
            FUN_004d8be0();           // cleanup
            FUN_009c8eb0(heapAllocation1); // operator delete
        }
    }
}