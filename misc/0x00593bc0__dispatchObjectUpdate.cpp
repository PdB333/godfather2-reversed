// FUNC_NAME: dispatchObjectUpdate
// Address: 0x00593bc0
// This function appears to process an update or dispatch for two objects pointed by ESI and EDI.
// It uses a descriptor-based dispatch where a type field selects a handler function,
// then potentially constructs a temporary structure and calls another function.

// The exact class is unknown, but the pattern suggests EA's generic object/manager system.
// Offsets are inferred from the decompiled code.

#include <cstdint>

// Forward declarations of the handler functions (return uint8_t)
extern "C" uint8_t FUN_00580230(void);
extern "C" uint8_t FUN_0057e300(void);
extern "C" uint8_t FUN_0057a900(void);
extern "C" uint8_t FUN_0057cfe0(void);

// Function that takes a temporary struct and an additional value
extern "C" void FUN_00586df0(void* stackStruct, uint32_t extraValue);

// Descriptor structure for the first object (pointed by ESI)
struct FirstObjectDescriptor {
    // Likely vtable or type info
    // +0x00: unknown (but we read offset +0x04 from descriptor)
    uint32_t field_0x00;
    // +0x04: version/type byte (low byte checked against 10)
    uint32_t versionAndFlags;
    // +0x20: pointer or value for version < 10
    uint32_t dataLowVersion;   // +0x20
    // +0x28: pointer or value for version >= 10
    uint32_t dataHighVersion;  // +0x28
    // +0x08 to +0x1F: other fields (not used here)
};

// The main function
uint8_t dispatchObjectUpdate(void) {
    uint8_t result = 0;
    // First object (ESI-based)
    // unaff_ESI is the base of the first object (passed in ESI register)
    // At offset +4 from that object is a pointer to its descriptor
    FirstObjectDescriptor* desc1 = *(FirstObjectDescriptor**)((uint8_t*)unaff_ESI + 4);

    // Determine which data field to use based on version byte
    uint32_t selector;
    if ((desc1->versionAndFlags & 0xFF) < 10) {
        selector = desc1->dataLowVersion;   // +0x20
    } else {
        selector = desc1->dataHighVersion;  // +0x28
    }
    selector &= 0x0FFFFFFF; // mask to 28 bits

    // Dispatch based on masked value
    if (selector == 0) {
        result = FUN_00580230();
    } else if (selector == 1) {
        result = FUN_0057e300();
    } else if (selector == 3) {
        result = FUN_0057a900();
    } else if (selector == 4) {
        result = FUN_0057cfe0();
    }

    // Second object (EDI-based)
    // unaff_EDI is the base of the second object (passed in EDI register)
    // At offset +4 is a byte (version) treated as a uint32_t (low byte valid)
    uint32_t version2 = *(uint32_t*)((uint8_t*)unaff_EDI + 4) & 0xFF;

    // Determine a signed index/value based on version
    int32_t indexValue;
    if (version2 < 10) {
        indexValue = *(int32_t*)((uint8_t*)unaff_EDI + 0x10);
    } else {
        indexValue = *(int32_t*)((uint8_t*)unaff_EDI + 0x24);
    }

    if (indexValue >= 0) {
        // Build a temporary structure on the stack
        // The structure seems to contain two quaternions or two vec4s
        // DAT_00e2b1a4 is some constant (likely 0.0f or identity quaternion component)
        // We define a struct for clarity
        struct TemporaryStruct {
            float field1; // local_30 (first component)
            float field2; // local_2c
            float field3; // local_28
            float field4; // local_24 (from DAT_00e2b1a4)
            float field5; // local_20
            float field6; // local_1c
            float field7; // local_18
            float field8; // local_14 (from DAT_00e2b1a4)
        };

        // Initialize part of the struct with constants
        // local_24 and local_14 are set to DAT_00e2b1a4 (floating point constant, possibly 0)
        extern float DAT_00e2b1a4; // from a data reference

        TemporaryStruct tempStruct;
        tempStruct.field1 = 0.0f;
        tempStruct.field2 = 0.0f;
        tempStruct.field3 = 0.0f;
        tempStruct.field4 = DAT_00e2b1a4;
        tempStruct.field5 = 0.0f;
        tempStruct.field6 = 0.0f;
        tempStruct.field7 = 0.0f;
        tempStruct.field8 = DAT_00e2b1a4;

        // Obtain the extra value from the second object based on version
        uint32_t extraValue;
        if (version2 < 10) {
            extraValue = *(uint32_t*)((uint8_t*)unaff_EDI + 0x0C);
        } else {
            extraValue = *(uint32_t*)((uint8_t*)unaff_EDI + 0x20);
        }

        // Call the function with the temporary struct and the extra value
        FUN_00586df0(&tempStruct, extraValue);
    }

    return result;
}