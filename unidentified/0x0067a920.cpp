// FUN_0067a920: AnalogController::applyDeadzoneCalibration()

#include <cstdint>

// This function calibrates deadzone thresholds for an analog input (likely an analog stick or wheel).
// It initializes the deadzone bounds based on raw input or calculated values.
// Offsets (from 'this'):
// +0x24 : bool isConnected? (0 or non-zero)
// +0xb8 : some data, used to set +0x124
// +0x100 : pointer to struct containing raw input buffer at offs +0xc
// +0x108 : short count of raw samples
// +0x10c : int scale factor (e.g., max raw range)
// +0x110 : int deadzone size (set to 0x20=32 eventually)
// +0x114 : int positive deadzone breakpoint
// +0x118 : int negative deadzone breakpoint
// +0x11c : int positive threshold after calibration? (center offset?)
// +0x120 : int always 0 (deadband)
// +0x124 : copy of +0xb8 (unknown)
// +0x1ec : uint8 flag (from FUN_0067bb50)

// External functions (assumed signatures):
// int FUN_0067b8f0(int mode, short* outA, short* outB, short* outC); // read raw analog data
// uint32_t FUN_0067bb50(short* outFlag); // read some digital input, returns byte
// int FUN_0067aba0(); // check something
// void FUN_00678240(); // trigger feedback/rumble

void AnalogController::applyDeadzoneCalibration() {
    short localA, localB, localC, localD;
    int result;

    // Initialize temporary calibration values to large range
    localA = 0x7FFF;          // +32767 (max positive)
    localB = (short)0xFFFF8001; // -32767 (min negative) - note: this is (short)0x8001?
    localC = 0x7FFF;          // +32767
    localD = 0;               // 0

    // Reset persistent calibration fields
    *(int*)(this + 0x110) = 0;
    *(int*)(this + 0x114) = 0x7FFF;
    *(int*)(this + 0x118) = (int)0xFFFF8001; // -32767
    *(int*)(this + 0x11C) = 0x7FFF;

    // Check if controller is connected (0x24 != 0)
    if (*(int*)(this + 0x24) == 0) {
        // Not connected: attempt to read raw with mode 7
LAB_0x67A989:
        if (*(int*)(this + 0x24) == 0) goto LAB_0x67A9E6;
        result = FUN_0067b8f0(7, &localA, &localB, &localD);
        if (result != 0) goto LAB_0x67A9E6;
    } else {
        // Connected: read raw with mode 2
        result = FUN_0067b8f0(2, &localA, &localB, &localD);
        if (result != 0) goto LAB_0x67A989;
    }

    // Store the raw readings as calibrated values (sign-inverted for negative axis)
    *(int*)(this + 0x114) = (int)localA;               // positive axis
    *(int*)(this + 0x118) = -(int)localB;              // negative axis (inverted)
    *(int*)(this + 0x11C) = (int)localC;               // positive threshold
    *(int*)(this + 0x120) = (int)localD;               // deadband (always 0)

LAB_0x67A9E6:
    // Copy over some existing value
    *(int*)(this + 0x124) = *(int*)(this + 0xB8);

    // Zero out raw input buffer if there are samples
    uint32_t count = (uint32_t)*(short*)(this + 0x108);
    if (count > 0) {
        uint32_t idx = 0;
        do {
            // Access raw buffer: *(this+0x100) -> struct, +0x12? Wait, offset 0xc from pointed struct
            short* buffer = (short*)(*(int*)(*(int*)(this + 0x100) + 0xC));
            buffer[idx] = 0;
            idx++;
        } while ((int)idx < (int)*(short*)(this + 0x108));
    }

    // Handle case where positive breakpoint is still at max (calibration not done)
    if (*(int*)(this + 0x114) == 0x7FFF) {
        short flag = 0;
        uint32_t resultByte = FUN_0067bb50(&flag);
        *(uint8_t*)(this + 0x1EC) = (uint8_t)(resultByte & 0xFF);
        if ((short)flag != 0) {
            int check = FUN_0067aba0();
            if (check != 0) {
                *(int*)(this + 0x114) = 0; // reset positive breakpoint
                FUN_00678240();            // trigger feedback
            }
        }
    }

    // Handle case where negative breakpoint is still at min
    if (*(int*)(this + 0x118) == (int)0xFFFF8001) { // -32767
        short flag = 0;
        uint32_t resultByte = FUN_0067bb50(&flag);
        *(uint8_t*)(this + 0x1EC) = (uint8_t)(resultByte & 0xFF);
        if ((short)flag != 0) {
            int check = FUN_0067aba0();
            if (check != 0) {
                *(int*)(this + 0x118) = 0; // reset negative breakpoint
                FUN_00678240();            // trigger feedback
            }
        }
    }

    // Set deadzone size
    *(int*)(this + 0x110) = 0x20; // 32 (deadzone)

    // If still at default, compute proportional breakpoints using scale factor at +0x10C
    if (*(int*)(this + 0x114) == 0x7FFF) {
        int scale = *(int*)(this + 0x10C);
        // Compute floor(scale * 0.75) with rounding toward zero
        int temp = scale * 3;
        *(int*)(this + 0x114) = (temp + ((temp >> 31) & 3)) >> 2;
    }

    if (*(int*)(this + 0x118) == (int)0xFFFF8001) {
        int scale = *(int*)(this + 0x10C);
        // Compute -floor(scale / 4) with rounding toward zero
        int temp = scale + ((scale >> 31) & 3);
        *(int*)(this + 0x118) = -(temp >> 2);
    }

    // Compute the positive threshold if still at default
    if (*(int*)(this + 0x11C) == 0x7FFF) {
        *(int*)(this + 0x11C) = (*(int*)(this + 0x10C) - *(int*)(this + 0x114)) + *(int*)(this + 0x118);
    }

    // Clamp to zero if negative
    if (*(int*)(this + 0x11C) < 0) {
        *(int*)(this + 0x11C) = 0;
    }
}