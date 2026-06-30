// FUNC_NAME: EARS::InterpolationValue::advance
// Function at 0x00581f60: Advances an interpolation/timer value by a delta, handling wrapping and events.
// Modifies state based on bit flags and returns a status code.
// Parameters: this (param_1), param_2 likely an output struct with delta at +4, result at +8, range at +0xc.

int __thiscall InterpolationValue::advance(int thisPtr, OutputStruct* output) {
    float sentinel = DAT_00e2b1a4;  // global constant (likely 0 or max float)
    
    // Zero out velocity/acceleration terms and reset them to sentinel
    *(float*)(thisPtr + 0x40) = 0.0f;
    *(float*)(thisPtr + 0x44) = 0.0f;
    *(float*)(thisPtr + 0x48) = 0.0f;
    *(float*)(thisPtr + 0x4c) = sentinel;
    
    *(float*)(thisPtr + 0x50) = 0.0f;
    *(float*)(thisPtr + 0x54) = 0.0f;
    *(float*)(thisPtr + 0x58) = 0.0f;
    *(float*)(thisPtr + 0x5c) = sentinel;
    
    uint flags = *(uint*)(thisPtr + 0x10);  // +0x10: bitfield flags
    uint temp = (flags >> 3) & 0xffffff01;  // extract flags byte
    // Clear specific bits: 0xf7fdfff4 -> clear bits 2, 12, and some others
    *(uint*)(thisPtr + 0x10) = flags & 0xf7fdfff4;
    
    if ((char)temp == 0) {
        float currentValue = *(float*)(thisPtr + 0x1c);  // +0x1c: current time/value
        float startValue   = *(float*)(thisPtr + 0x20);  // +0x20: start of range
        float endValue     = *(float*)(thisPtr + 0x24);  // +0x24: end of range (or period)
        
        // Reset start and store end
        *(float*)(thisPtr + 0x20) = currentValue;
        *(float*)(thisPtr + 0x28) = endValue;  // backup end value
        
        if (*(int*)(thisPtr + 0x2c) != 2) {  // state not 2 (maybe 'inactive')
            float delta = *(float*)(output + 4);  // delta time or step to add
            float newValue = currentValue + delta;
            int integerPart;
            float fractionalPart;
            float range = endValue - sentinel;
            
            if (endValue == sentinel) {
                // No range: treat as integer wrapping
                integerPart = (int)newValue;
                fractionalPart = newValue - (float)integerPart;
            } else {
                // Normal wrapping when range > 0
                if (range < newValue) {
                    integerPart = (int)(newValue / range);
                    fractionalPart = newValue - (float)integerPart * range;
                } else {
                    integerPart = 0;
                    fractionalPart = newValue;
                }
            }
            
            // Update current value with fractional part (wrap/loop)
            *(float*)(thisPtr + 0x1c) = fractionalPart;
            
            // Determine if we crossed a boundary
            int resultByte;  // 0 or 1 indicating event
            if (delta < range) {
                resultByte = 0;
            } else {
                resultByte = 1;
            }
            
            // Check for completion condition
            if (startValue <= fractionalPart && resultByte == 0) {
                // No boundary crossing: return the integer part encoding
                return integerPart << 8;
            }
            
            // Boundary crossed: set event flag
            *(uint*)(thisPtr + 0x10) = flags & 0xf7fdfff4 | 1;  // set bit 0
            *(float*)(output + 8) = *(float*)(thisPtr + 0x1c);   // current value after wrap
            *(float*)(output + 0xc) = startValue - range;        // adjusted start
            
            if (((*(char*)(thisPtr + 0x30) == 0) || (*(int*)(thisPtr + 0x2c) == 0)) &&
                (*(float*)(thisPtr + 0x1c) = range, range < *(float*)(thisPtr + 0x20))) {
                // If no clamp flag or state is 0, and range < start, update start to range
                *(float*)(thisPtr + 0x20) = range;
            }
            
            // Return with low byte = 1 (event triggered)
            return (integerPart >> 8) | 1;  // note: integerPart is shifted up, low byte 1
        }
    }
    
    // No update performed: return flags from upper bits
    return (flags >> 0xb) << 8;
}