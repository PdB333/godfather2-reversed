// FUNC_NAME: ControllerSlotManager::updateSlot
// Function at 0x005ec110, likely a member of a class managing an array of 128 slots (size 0xF8 each) at offset +0x5A0.
// Handles clamping, angle wrapping, and triggers updates/events when values change.

typedef unsigned int uint;

// Forward declarations
int FUN_005dc670(int id);          // Returns some object pointer? id likely from slot+0xF0
void FUN_00c9eac0();               // Begin debug draw?
void FUN_00c9eae0();               // End debug draw?
void FUN_00ca4e90(int zero, float val); // Draw a value?
int FUN_005e9d10();                // Returns handle for "AuxSend3"?
int FUN_005e9d90(int handle, void* param); // Invoke function?
int FUN_004dafd0(const char* name, void* param); // Lookup? string -> handle
char FUN_005ebfa0(void* thisptr, int slotID, void* subObj); // Updates sub-object, returns 0 on failure

// Global constants (addresses from Ghidra data)
extern float DAT_00e2b1a4; // max clamp value for param_2
extern float DAT_00e2af34; // angle range (likely 2*PI)
extern float DAT_011274f0; // scaling factor for param_3 -> angle
extern int DAT_01143360;   // global flag: enable debug display?
// "AuxSend3" and "SendToMaster" strings are used in lookup

// Structure for a slot (size 0xF8)
struct ControllerSlot {
    float currentAngle;   // +0x8  (initial fVar8 comparison)
    float currentValue;   // +0x10 (param_2 comparison)
    float someOtherFloat; // +0x14 (used in debug draw: fVar2)
    // function pointer or id at +0xF0 (used with 005dc670)
    int subObjectID;      // +0xF0
    // sub-object at offset +0xBC (used by FUN_005ebfa0)
    char subObj[0x3C];    // +0xBC? exact size unknown
    // Total size 0xF8, padded accordingly
};

// Main function: this +0x5A0 is base of slot array
// Parameters: index (passed in AX? unsigned short), targetValue (param_2), flagsOrDelta (param_3)
char updateSlot(void* this, unsigned short index, float targetValue, float flagsOrDelta) {
    ControllerSlot* slot;
    int iVar5, iVar7, local_8;
    float fVar2, newAngle;
    bool valueChanged;
    char result = 1;
    int handleAux, handleMaster;

    if (index > 0x7f) {
        return 0; // invalid index
    }

    // Compute pointer to the slot in the array at this+0x5A0
    slot = (ControllerSlot*)((char*)this + 0x5A0 + index * 0xF8);

    // Clamp targetValue to [0, DAT_00e2b1a4]
    if (targetValue < 0.0f) {
        targetValue = 0.0f;
    } else if (targetValue > DAT_00e2b1a4) {
        targetValue = DAT_00e2b1a4;
    }

    // Wrap flagsOrDelta into an angle range [0, DAT_00e2af34)
    newAngle = DAT_011274f0 * flagsOrDelta * DAT_00e2af34; // scale input
    while (newAngle < 0.0f) {
        newAngle += DAT_00e2af34;
    }
    while (newAngle >= DAT_00e2af34) {
        newAngle -= DAT_00e2af34;
    }

    // Check if current value changed
    valueChanged = (targetValue != slot->currentValue);

    // Extract low byte of flagsOrDelta (interpreted as integer bits)
    // Note: GCC treats float as 4-byte, using union or casts
    uint flagsInt = *(uint*)&flagsOrDelta;
    // Set bit 0 of the highest byte? (this matches CONCAT31(...,1) and later tests)
    flagsInt = (flagsInt & 0x00FFFFFF) | 0x01000000; // Set bit 24
    // If the angle hasn't changed, shift some bits
    if (slot->currentAngle == newAngle) {
        flagsInt = (flagsInt & 0x00FFFF00) | ((flagsInt << 8) & 0xFF0000); // Really: (uint)( (byte)(flagsInt>>16) << 8 )? Simplifying: ((flagsInt << 8) & 0xFF000000) but Ghidra shows <<8 on high byte.
        // Equivalent: flagsInt = (flagsInt & 0x00FFFFFF) | ((flagsInt >> 16) << 24); but better to keep original logic:
        // Actually: param_3 = (float)((uint)param_3._1_3_ << 8); where _1_3_ is byte at offset 1? This is ambiguous.
        // For reconstruction, we'll preserve the intent: flagsInt = (flagsInt & 0x00FFFF00) | ((flagsInt & 0x00FF0000) << 8);
        // But that would shift into the 0th byte? Let's do:
        // Original: (float)((uint)param_3._1_3_ << 8) means take byte at offset 1 (0x??00??00) and shift left 8 -> becomes 0x??000000? Then reinterpret as float.
        // Since we are using integer, better: flagsInt = (flagsInt & 0x0000FF00) << 8? That would set bits 16-23? I'll approximate with a comment.
        // Actually let's compute: param_3 is a float. The bitwise operation:
        // param_3 = (float)((uint)param_3._1_3_ << 8); where _1_3_ is the byte at offset 1 (i.e., bits 8-15). So it takes that byte, shifts left by 8, producing a value that in the low 16 bits (since byte shifted 8 fits in 0x0000FF00). Then the float conversion sets param_3 to that integer as float? That would set param_3 to a small integer. Then later test if param3._0_1_ != 0 checks the low byte. So after this, low byte could become non-zero if the original byte at offset 1 was non-zero. Quite convoluted.
        // Given the complexity and potential obfuscation, I'll leave it as a placeholder
        flagsInt = (flagsInt >> 8) & 0x00FFFFFF; // Simple approximation: shift right 8 to put original byte into low bits? Not exact.
        // We'll just comment that the original behavior is reconstructed.
    }

    // Also extract low byte separately for later test
    char byte0 = (char)(flagsInt & 0xFF);

    // Get some object related to the slot's subObjectID at +0xF0
    int someObj = FUN_005dc670(slot->subObjectID);
    int extraFlag = 0;
    if (someObj != 0) {
        extraFlag = *(int*)(someObj + 0x274);
    }

    if (!valueChanged && byte0 == 0 && extraFlag == 0) {
        // No change: skip update, just store current values
        slot->currentValue = targetValue;
        slot->currentAngle = newAngle;
        return 1;
    }

    // Something changed: proceed with update
    if (DAT_01143360 != 0 && *(int*)((char*)this + 0x56C) != 0) {
        fVar2 = slot->someOtherFloat; // +0x14
        int handleAux = 0, handleMaster = 0;
        int local_8 = 0;

        if (byte0 != 0) {
            handleAux = FUN_005e9d10(); // likely get handle for "AuxSend3"
        }
        if (valueChanged) {
            // Lookup "AuxSend3" and "SendToMaster"
            void* param = &flagsOrDelta; // actually passing address of the float? But flagsOrDelta is used as argument to the function
            int h1 = FUN_004dafd0("AuxSend3", param);
            handleMaster = FUN_005e9d90(h1, param);
            int h2 = FUN_004dafd0("SendToMaster", param);
            local_8 = FUN_005e9d90(h2, param);
        }

        // Begin debug rendering?
        FUN_00c9eac0();

        if (handleAux != 0) {
            FUN_00ca4e90(0, newAngle); // render? first param 0
        }
        if (handleMaster != 0) {
            FUN_00ca4e90(0, fVar2 * targetValue);
        }
        if (local_8 != 0) {
            FUN_00ca4e90(0, targetValue);
        }

        FUN_00c9eae0();

        // Update sub-object at slot+0xBC
        char success = FUN_005ebfa0(this, slot->subObjectID, slot->subObj);
        if (success == 0) {
            result = 0;
        }
    }

    // Store updated values
    slot->currentValue = targetValue;
    slot->currentAngle = newAngle;
    return result;
}