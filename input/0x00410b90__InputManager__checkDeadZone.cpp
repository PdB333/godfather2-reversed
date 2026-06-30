// FUNC_NAME: InputManager::checkDeadZone
#include <cstdint>

// Global constants from the binary (likely threshold and bitmask)
extern float gDeadZoneThreshold; // DAT_00e35654
extern uint32_t gAnalogMask;     // DAT_00e44680 (mask for analog values, likely to extract lower bits)

// Forward declaration of the helper function that reads raw input data
int readControllerRaw(uint32_t slotIndex, uint16_t maxVal, int mode); // FUN_00410280

// This function checks if all analog thumbsticks are within dead zone for a given controller slot.
// slotIndex (param_1) is a controller slot index (0-15 typically).
// Returns a combined status (low byte from readControllerRaw, but if all axes are below dead zone,
// the low byte is zeroed and the high byte is preserved).
int InputManager::checkDeadZone(uint32_t slotIndex) {
    int rawStatus = readControllerRaw(slotIndex, 0xFFFF, 2);
    
    // Check if the raw status low byte (device response) is zero
    if ((char)rawStatus == 0) {
        // Pointer to the controller slot data (0x44 bytes per slot)
        uint8_t* slotData = reinterpret_cast<uint8_t*>(this) + (slotIndex & 0xFF) * 0x44;
        
        // Four analog axis values at offsets +0x2c, +0x30, +0x34, +0x38
        // They are masked and compared to dead zone threshold
        float axis0 = static_cast<float>(*(uint32_t*)(slotData + 0x2C) & gAnalogMask);
        float axis1 = static_cast<float>(*(uint32_t*)(slotData + 0x30) & gAnalogMask);
        float axis2 = static_cast<float>(*(uint32_t*)(slotData + 0x34) & gAnalogMask);
        float axis3 = static_cast<float>(*(uint32_t*)(slotData + 0x38) & gAnalogMask);
        
        if (axis0 <= gDeadZoneThreshold && axis1 <= gDeadZoneThreshold &&
            axis2 <= gDeadZoneThreshold && axis3 <= gDeadZoneThreshold) {
            // All axes in dead zone: return the high byte of rawStatus (shifted back to high position)
            // This effectively zeros the low byte while preserving the upper status bits.
            return (rawStatus >> 8) << 8;
        }
        // If not all axes are in dead zone, fall through to return rawStatus unchanged (with low byte set to 1? Actually the code sets iVar1 = CONCAT31(uVar2,1) but that path is NOT taken here!
        // Wait, the decompilation shows that after the if, there is iVar1 = CONCAT31(uVar2,1); but that line appears outside the if block? Actually the decompiled code is ambiguous.
        // Given the original:
        //   iVar1 = FUN_00410280(...)
        //   if ((char)iVar1 == 0) {
        //       ... compute ...
        //       if (all axes <= threshold) { return (uint)uVar2 << 8; }
        //       iVar1 = CONCAT31(uVar2,1);
        //   }
        //   return iVar1;
        // So if the axes are NOT all in dead zone, it sets iVar1 to (uVar2 with low byte = 1) and returns that.
        // That means the low byte is forced to 1 (indicating active movement?).
        rawStatus = (rawStatus & 0xFFFFFF00) | 0x01;  // Set low byte to 1
    }
    return rawStatus;
}