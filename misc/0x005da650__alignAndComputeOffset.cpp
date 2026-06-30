// FUNC_NAME: alignAndComputeOffset
// Address: 0x005da650
// Role: Aligns input value to 256-byte boundary and computes an offset based on a division by 0x28 (40).
// Called from FUN_005da180, likely part of buffer/array management (EA EARS engine).
// Note: in_EAX and unaff_EDI are registers set by caller, treated as implicit parameters.
int alignAndComputeOffset(uint param_1) {
    uint originalValue;
    int reg_EAX;    // implicit from caller (in_EAX)
    int reg_EDI;    // implicit from caller (unaff_EDI)
    
    originalValue = param_1;
    param_1 = param_1 & 0xffffff00; // Align to 256-byte boundary (clear low byte)
    
    // Call helper function with 4 args: original, aligned, 0, aligned
    // Likely a logging or validation function
    FUN_005da9c0(originalValue, param_1, 0, param_1);
    
    // Return reg_EDI + ((reg_EAX - originalValue) / 0x28) * 0x28
    // This rounds (reg_EAX - originalValue) down to nearest multiple of 0x28 (40)
    // Added to reg_EDI (base offset)
    return reg_EDI + ((int)(reg_EAX - originalValue) / 0x28) * 0x28;
}