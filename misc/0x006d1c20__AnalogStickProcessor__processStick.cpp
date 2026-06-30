// FUNC_NAME: AnalogStickProcessor::processStick
void __thiscall AnalogStickProcessor::processStick(int thisPtr, float* outX, float* outY, int controllerIndex, float param5) {
    // Initialize outputs to zero
    *outX = 0.0f;
    *outY = 0.0f;

    // Get controller device pointer from global input manager array
    // DAT_012233a0 + 4 points to an array of controller slots, each slot 4 bytes (pointer)
    int* controllerDevice = *(int**)(*(int*)(DAT_012233a0 + 4) + controllerIndex * 4);
    
    // Validate device pointer and check a busy/active flag at offset 0x570 (0x15c * 4)
    if (controllerDevice != nullptr && controllerDevice != (int*)0x1f30) {
        // Bit 20 (>> 0x14 & 1) at offset 0x570 – check if device is enabled/connected
        if (((uint)controllerDevice[0x15c] >> 0x14 & 1) == 0) {
            // Call virtual function at vtable+8 – returns a handle/state object
            uint stateHandle = (*(code**)(*controllerDevice + 8))();
            
            // Get raw axis values from the state handle
            int rawStatePtr = FUN_00410540(stateHandle);
            if (rawStatePtr != 0) {
                // Check if input is digital vs analog
                char isDigital = FUN_00410d80();
                
                float rawX = *(float*)(rawStatePtr + 8);
                float rawY = *(float*)(rawStatePtr + 0xC);
                
                if (isDigital == 0) {
                    // Analog mode: apply deadzone and curve
                    // Apply deadzone: threshold DAT_00d58cbc, using bitwise trick
                    if ((float)((uint)rawX & DAT_00e44680) <= DAT_00d58cbc) {
                        rawX = 0.0f;
                    }
                    if ((float)((uint)rawY & DAT_00e44680) <= DAT_00d58cbc) {
                        rawY = 0.0f;
                    }
                    
                    // Clamp and apply cubic/square curves
                    float clampedX = DAT_00d5ccf8;
                    if (DAT_00d5ccf8 < rawX && _DAT_00d5780c <= rawX) {
                        clampedX = _DAT_00d5780c;
                    } else if (DAT_00d5ccf8 < rawX) {
                        clampedX = rawX;
                    }
                    // Note: Original code had potentially flawed logic; we reconstruct as-is
                    
                    float clampedY = DAT_00d5ccf8;
                    if (DAT_00d5ccf8 < rawY && _DAT_00d5780c <= rawY) {
                        clampedY = _DAT_00d5780c;
                    } else if (DAT_00d5ccf8 < rawY) {
                        clampedY = rawY;
                    }
                    
                    *outX = clampedX * clampedX * clampedX;   // cubic
                    *outY = clampedY * clampedY;              // square
                } else {
                    // Digital mode: scale by sensitivity
                    float scale = DAT_00d5f374 / param5;
                    *outX = rawX * scale;
                    *outY = rawY * scale;
                }
            }
        }
    }
    
    // Apply global inversion flags
    float maxValue = DAT_00e44564;
    if (DAT_0112a7a4 != 0) {  // Invert Y axis
        *outY = maxValue - *outY;
    }
    if (DAT_0112a7a5 != 0) {  // Invert X axis
        *outX = maxValue - *outX;
    }
    
    // Check if deadzone smoothing is enabled
    char smoothingEnabled = FUN_00410eb0();
    float smoothFactor = DAT_00e5115c;
    uint bitmask = DAT_00e44680;
    
    if (smoothingEnabled == 0) {
        // Smooth interpolation with previous values stored at +0x60 (X) and +100 (Y)
        float oneMinusSmooth = _DAT_00d5780c - smoothFactor;
        
        // Only smooth if current magnitude is less than stored previous magnitude (bitwise compare)
        if ((float)((uint)*outX & bitmask) < (float)((uint)*(float*)(thisPtr + 0x60) & bitmask)) {
            *outX = *(float*)(thisPtr + 0x60) * oneMinusSmooth + *outX * smoothFactor;
        }
        if ((float)((uint)*outY & bitmask) < (float)((uint)*(float*)(thisPtr + 100) & bitmask)) {
            *outY = *(float*)(thisPtr + 100) * oneMinusSmooth + *outY * smoothFactor;
        }
        
        // Apply final deadzone threshold DAT_00e44640
        float deadzoneThreshold = DAT_00e44640;
        if ((float)((uint)*outX & bitmask) < deadzoneThreshold) {
            *outX = 0.0f;
        }
        if ((float)((uint)*outY & bitmask) < deadzoneThreshold) {
            *outY = 0.0f;
        }
        
        // Store smoothed values for next frame
        *(float*)(thisPtr + 0x60) = *outX;
        *(float*)(thisPtr + 100) = *outY;
        return;
    } else {
        // Digital smoothing disabled: clear stored values
        *(float*)(thisPtr + 0x60) = 0.0f;
        *(float*)(thisPtr + 100) = 0.0f;
        return;
    }
}