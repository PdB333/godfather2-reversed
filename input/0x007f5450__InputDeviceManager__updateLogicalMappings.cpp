// FUNC_NAME: InputDeviceManager::updateLogicalMappings
// Function address: 0x007f5450
// Reconstructed from Ghidra decompile of The Godfather 2 (EA EARS engine, x86)

#include <cstdint>

// Global references used in the function (likely constants or configuration)
extern uint32_t DAT_00d71c38; // Some sensitivity/calibration value for group 0
extern uint32_t DAT_00d5cf70; // Calibration value for group 1
extern uint32_t DAT_00d71c34; // Calibration value for group 2

// Forward declarations of callees
int32_t __fastcall isGameRunning();            // 0x004603f0
int32_t __fastcall getNumControllers();        // 0x005589e0
uint32_t* __fastcall getControllerState(int32_t controllerIndex); // 0x00558b00
void __fastcall onAllSlotsMapped(void* callback, uint32_t* mappingGroup0); // 0x00558400

class InputDeviceManager {
    // Fields (offsets relative to this)
    // +0x630: uint32_t logicalMappingGroup0;
    // +0x634: uint8_t analogDeadZone0[4]; // 0x634-0x637? Actually pattern: byte at 0x634,0x635,0x636, then 0xff 4 bytes
    // +0x638: uint8_t unused0;
    // +0x63c: uint32_t calibrationGroup0;
    // +0x640: uint32_t logicalMappingGroup1;
    // +0x644: uint8_t analogDeadZone1[4]; // similar
    // +0x64c: uint32_t calibrationGroup1;
    // +0x650: uint32_t logicalMappingGroup2;
    // +0x654: uint8_t analogDeadZone2[4]; // similar
    // +0x65c: uint32_t calibrationGroup2;
    // +0x660: uint32_t controllerStateStorage[23]; // raw state per logical slot (0..22)
    // +0x6a0: uint32_t rawStateForSlot_0x6a0; // Unknown, maybe axis value
    // +0x6b4: uint32_t rawStateForSlot_0x6b4;
    // +0x6b8: uint32_t rawStateForSlot_0x6b8;
    // +0x6bc: int8_t logicalSlotToControllerIndex[23]; // mapped controller index for each logical slot (-1 = unassigned)

public:
    void __thiscall updateLogicalMappings();
};

// Helper: Convert raw state to byte value (right shift by 2)
inline uint8_t stateToByte(uint32_t rawState) {
    return static_cast<uint8_t>(rawState >> 2);
}

void __thiscall InputDeviceManager::updateLogicalMappings() {
    if (!isGameRunning()) {
        return;
    }

    int32_t numControllers = getNumControllers();
    if (numControllers <= 0) {
        return;
    }

    // Update raw state storage for each logical slot from actual controllers
    for (int32_t controllerIdx = 0; controllerIdx < numControllers; ++controllerIdx) {
        uint32_t* pControllerState = getControllerState(controllerIdx);
        uint32_t stateValue = *pControllerState;

        // Valid state: lower 2 bits zero and any other bit set
        if ((stateValue & 0xFFFFFFFC) != 0 && (stateValue & 3) == 0) {
            // Find which logical slot this controller is assigned to
            for (uint32_t slotIdx = 0; slotIdx < 23; ++slotIdx) {
                if (logicalSlotToControllerIndex[slotIdx] == static_cast<int8_t>(controllerIdx)) {
                    controllerStateStorage[slotIdx] = stateValue;
                    break;
                }
            }
        }
    }

    uint32_t calibration0 = DAT_00d71c38;
    uint32_t mappingMaskGroup0 = 0;
    uint32_t mappingMaskGroup1 = 0;
    uint32_t mappingMaskGroup2 = 0;

    // Build mapping masks for each group by iterating logical slots
    for (uint32_t slotIdx = 0; slotIdx < 23; ++slotIdx) {
        int8_t controllerIndex = logicalSlotToControllerIndex[slotIdx];
        if (controllerIndex < 0) {
            continue; // slot not assigned
        }

        // Check if this slot belongs to group 0 (mask 0x2709e0)
        if ((1 << (slotIdx & 0x1F) & 0x2709E0) != 0) {
            mappingMaskGroup0 |= (1 << (controllerIndex & 0x1F));
        }

        // Check if this slot belongs to group 1 (mask 0x588618)
        if ((1 << (slotIdx & 0x1F) & 0x588618) != 0) {
            mappingMaskGroup1 |= (1 << (controllerIndex & 0x1F));
        }

        // Check if this slot belongs to group 2 (mask 0xF00F)
        if ((1 << (slotIdx & 0x1F) & 0xF00F) != 0) {
            mappingMaskGroup2 |= (1 << (controllerIndex & 0x1F));
        }
    }

    // Write group 0 mapping block
    logicalMappingGroup0 = mappingMaskGroup0;
    analogDeadZones0[0] = stateToByte(rawStateForSlot_0x6b4); // at offset 0x634
    analogDeadZones0[1] = stateToByte(rawStateForSlot_0x678); // at offset 0x635
    analogDeadZones0[2] = stateToByte(rawStateForSlot_0x6a0); // at offset 0x636
    analogDeadZones0[3] = 0xFF; // dead zone terminator? (0x637)
    analogDeadZones0[4] = 0xFF; // (0x638)
    analogDeadZones0[5] = 0xFF; // (0x639)
    analogDeadZones0[6] = 0xFF; // (0x63a)
    unused0 = 0;                 // (0x63b)
    calibrationGroup0 = calibration0;

    // Write group 1 mapping block
    logicalMappingGroup1 = mappingMaskGroup1;
    analogDeadZones1[0] = stateToByte(rawStateForSlot_0x6b8); // at offset 0x646? Wait, check offsets:
    // From decompiled: *(char *)(param_1 + 0x644) = (char)(*(uint *)(param_1 + 0x688) >> 2);
    // *(char *)(param_1 + 0x646) = (char)(*(uint *)(param_1 + 0x6b8) >> 2);
    // So group1: 0x644 = from 0x688, 0x645? Actually sequence: 
    // At 0x640: uVar6 (mask)
    // At 0x644: from 0x688
    // At 0x645: from 0x6b0
    // At 0x646: from 0x6b8
    // Then 0x647-0x64a = 0xff, 0x64b=0, 0x64c = DAT_00d5cf70
    // We need to map correctly.
    analogDeadZones1[0] = stateToByte(*(uint32_t*)(this + 0x688)); // at 0x644
    analogDeadZones1[1] = stateToByte(*(uint32_t*)(this + 0x6B0)); // at 0x645
    analogDeadZones1[2] = stateToByte(*(uint32_t*)(this + 0x6B8)); // at 0x646
    analogDeadZones1[3] = 0xFF;
    analogDeadZones1[4] = 0xFF;
    analogDeadZones1[5] = 0xFF;
    analogDeadZones1[6] = 0xFF;
    unused1 = 0;                 // at 0x64b
    calibrationGroup1 = DAT_00d5cf70;

    // Write group 2 mapping block
    logicalMappingGroup2 = mappingMaskGroup2;
    analogDeadZones2[0] = stateToByte(*(uint32_t*)(this + 0x668)); // at 0x654
    analogDeadZones2[1] = stateToByte(*(uint32_t*)(this + 0x698)); // at 0x655
    analogDeadZones2[2] = stateToByte(*(uint32_t*)(this + 0x690)); // at 0x657? Wait, offsets: 0x654,0x655,0x656,0x657. From decompiled:
    // *(char *)(param_1 + 0x654) = (char)(*(uint *)(param_1 + 0x668) >> 2);
    // *(char *)(param_1 + 0x655) = (char)(*(uint *)(param_1 + 0x698) >> 2);
    // *(char *)(param_1 + 0x657) = (char)(*(uint *)(param_1 + 0x690) >> 2);
    // Note: 0x656 is missing? Actually decompiled shows:
    // *(char *)(param_1 + 0x656) = (char)(*(uint *)(param_1 + 0x660) >> 2);
    // So there are four bytes: 0x654,0x655,0x656,0x657. The code sets 0x656 from 0x660.
    analogDeadZones2[0] = stateToByte(*(uint32_t*)(this + 0x668));
    analogDeadZones2[1] = stateToByte(*(uint32_t*)(this + 0x698));
    analogDeadZones2[2] = stateToByte(*(uint32_t*)(this + 0x660)); // from 0x656
    analogDeadZones2[3] = stateToByte(*(uint32_t*)(this + 0x690)); // from 0x657
    analogDeadZones2[4] = 0xFF;
    analogDeadZones2[5] = 0xFF;
    analogDeadZones2[6] = 0xFF;
    analogDeadZones2[7] = 0xFF;
    unused2 = 1;                 // at 0x65b (different from groups 0 and 1 which had 0)
    calibrationGroup2 = DAT_00d71c34;

    // If all 23 bits are set in the combined masks, call a callback
    if ((mappingMaskGroup0 | mappingMaskGroup1 | mappingMaskGroup2) == 0x7FFFFF) {
        onAllSlotsMapped(reinterpret_cast<void*>(0x00558fb0), &logicalMappingGroup0);
    }
}