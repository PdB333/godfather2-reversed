// FUN_004383b0: EffectStream::readNextEffect

#include <cstdint>

// Forward declarations of external functions used
int __fastcall FUN_00633990(void* stream);   // Check if current element is valid for type 3
void __fastcall FUN_00627360(void);          // Some error handler (overflow?)
int __fastcall FUN_004dafd0(int rawValue);   // Convert raw value to effect parameter (e.g., color component)
int __fastcall FUN_00636850(int* outValue);  // Decode packed value (e.g., from a bitstream)

// Global effect manager interface (vtable at DAT_01223510)
extern int* gEffectManager;  // Actual pointer to effect manager object

// Structure representing an effect event (size 0x14 or more)
struct EffectEvent {
    int field_0;       // First parameter (e.g., red or alpha)
    int field_4;       // Second parameter (e.g., green)
    int field_8;       // Third parameter (e.g., blue)
    int field_C;       // Fourth parameter (e.g., intensity)
    uint8_t field_10;  // Flags? (unused in this function)
    uint8_t flag1;     // = 1
    uint8_t flag2;     // = 1
    uint8_t flag3;     // = 1
    // total 0x14 bytes? Actually local layout:
    // local_20: field_0 (int)
    // local_1c: field_4 (int) = uVar3
    // local_18: field_8 (int) = local_34
    // local_14: field_C (int)
    // local_10: field_10 (undefined) = 0
    // local_c: flag1 (byte) = 0
    // local_b: flag2 (byte) = 1
    // local_a: flag3 (byte) = 1
    // local_9: flag4 (byte) = 1
};

int __fastcall EffectStream::readNextEffect(void* this) {
    int* currentPtr = *(int**)((char*)this + 0xC);   // stream read position
    int* endPtr = *(int**)((char*)this + 0x8);       // stream end

    EffectEvent event;
    event.field_0 = 0;
    event.field_4 = 0;

    // Read first field (offset +0x00 from current)
    if ((currentPtr < endPtr) && (currentPtr != nullptr)) {
        int type = *currentPtr;
        if ((type == 4) || (type == 3)) {
            if ((currentPtr < endPtr) && (currentPtr != nullptr)) {
                int rawValue;
                if (type == 4) {
                    rawValue = currentPtr[1] + 0x10;  // Direct offset
                } else {
                    if (FUN_00633990(this) != 0) {
                        rawValue = currentPtr[1] + 0x10;
                    } else {
                        rawValue = 0;
                    }
                    // Error check: if buffer overflow, log
                    int* bufInfo = *(int**)((char*)this + 0x10);
                    if (*(uint32_t*)(bufInfo + 8) <= *(uint32_t*)(bufInfo + 0xC)) {
                        FUN_00627360();
                    }
                }
                // Convert and store
                event.field_0 = FUN_004dafd0(rawValue);
            }
        }
    }

    // Read second field (offset +0x08 from current)
    int currentBase = *(int*)((char*)this + 0xC);   // re-read current pointer as int
    int* field2Ptr = (int*)(currentBase + 8);
    if ((field2Ptr < endPtr) && (field2Ptr != nullptr)) {
        int type = *field2Ptr;
        if ((type == 4) || (type == 3)) {
            if ((field2Ptr < endPtr) && (field2Ptr != nullptr)) {
                int rawValue;
                if (type == 4) {
                    rawValue = *(int*)(currentBase + 0xC) + 0x10;
                } else {
                    if (FUN_00633990(this) != 0) {
                        rawValue = *(int*)(currentBase + 0xC) + 0x10;
                    } else {
                        rawValue = 0;
                    }
                    // Error check again
                    int* bufInfo = *(int**)((char*)this + 0x10);
                    if (*(uint32_t*)(bufInfo + 8) <= *(uint32_t*)(bufInfo + 0xC)) {
                        FUN_00627360();
                    }
                }
                event.field_4 = FUN_004dafd0(rawValue);
            }
        }
    }

    // Read third field (offset +0x10 from current)
    int* field3Ptr = (int*)(*(int*)((char*)this + 0xC) + 0x10);
    if ((field3Ptr < endPtr) && (field3Ptr != nullptr)) {
        int type = *field3Ptr;
        if ((type == 4) || (type == 3)) {
            // Try to decode a packed value
            int packedValue;
            if ((field3Ptr < endPtr) && (field3Ptr != nullptr)) {
                if (type == 3) {
                    // type 3: use raw value directly
                } else {
                    // type 4: attempt to decode via FUN_00636850
                    if (FUN_00636850(&packedValue) == 0) {
                        goto LAB_00438501;
                    }
                    int local_30 = 3;      // placeholder
                    int local_2c = packedValue;
                    field3Ptr = &local_30; // override pointer? This is weird.
                    // Actually the code replaces field3Ptr and sets fVar5 from field3Ptr[1]
                }
                float floatVal = (float)field3Ptr[1];
            } else {
LAB_00438501:
                floatVal = 0.0f;
            }
            event.field_8 = (int)floatVal;
        }
    }

    // Read fourth field (offset +0x18 from current)
    int* field4Ptr = (int*)(*(int*)((char*)this + 0xC) + 0x18);
    if (field4Ptr >= endPtr) {
        return 0;
    }
    if (field4Ptr == nullptr) {
        return 0;
    }
    // Sanity check type
    if (*field4Ptr != 3) {
        if (*field4Ptr != 4) {
            return 0;
        }
        int packedValue;
        if (FUN_00636850(&packedValue) == 0) {
            return 0;
        }
    }
    // Read actual value from fourth field (similar to third)
    int* readPtr = (int*)(*(int*)((char*)this + 0xC) + 0x18);
    if ((readPtr < endPtr) && (readPtr != nullptr)) {
        if (*readPtr == 3) {
            // direct value
        } else {
            if ((*readPtr == 4) && (FUN_00636850(&packedValue) != 0)) {
                int local_28 = 3;
                int local_24 = packedValue;
                readPtr = &local_28;
            } else {
                goto LAB_0043859f;
            }
        }
        event.field_C = readPtr[1];
    } else {
LAB_0043859f:
        event.field_C = 0;
    }

    // Assemble event and submit to effect manager
    // Fields already set:
    //   event.field_0 = local_38
    //   event.field_4 = uVar3
    //   event.field_8 = local_34
    //   event.field_C = local_14
    event.field_10 = 0;   // local_10
    event.flag1 = 0;      // local_c = 0? Actually code set local_c=0, but then local_b=1,local_a=1,local_9=1
    event.flag2 = 1;      // local_b
    event.flag3 = 1;      // local_a
    // local_9 = 1 is flag4 but not in struct? We'll treat as extra byte

    // Call effect add function via global vtable
    int vtable = *gEffectManager;
    ((void(__cdecl *)(EffectEvent*))(* (int*)(vtable + 0xC0) ))(&event);

    return 0;
}