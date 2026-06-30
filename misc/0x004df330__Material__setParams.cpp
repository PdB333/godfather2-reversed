// FUNC_NAME: Material::setParams
// Function address: 0x004df330
// Role: Wrapper function that packs material parameters into a temporary structure
//        and delegates to Material::setParamsInternal (0x004df270).
// Takes up to 8 parameters; param_8 is an optional pointer to a 3-uint material data block.

// Global material constant (used as default 4th field)
extern uint32_t g_materialDefault; // DAT_00e2b1a4

// Called function declaration (actual implementation at 0x004df270)
uint32_t __thiscall Material::setParamsInternal(uint32_t this, uint32_t param2, uint32_t param3, 
                                                uint32_t param4, uint32_t param5, MaterialTempArgs* pArgs);

// Temporary argument structure – packed before calling internal function
struct MaterialTempArgs {
    uint32_t field0;          // +0x00
    uint32_t field1;          // +0x04
    uint32_t field2;          // +0x08
    uint32_t field3;          // +0x0C – always set to g_materialDefault
    uint32_t field4;          // +0x10 – from param_6
    uint32_t field5;          // +0x14 – from param_7
    uint32_t type;            // +0x18 – set to 2
};

uint32_t __thiscall Material::setParams(uint32_t this, uint32_t param2, uint32_t param3, 
                                        uint32_t param4, uint32_t param5, uint32_t param6, 
                                        uint32_t param7, uint32_t* param8) {
    MaterialTempArgs args;

    // If param8 is non-null, copy first three dwords from the source material block
    if (param8 != nullptr) {
        args.field0 = param8[0];
        args.field1 = param8[1];
        args.field2 = param8[2];
    } else {
        // Clear the copied fields? Not explicitly – but likely undefined before call.
        // The actual code only copies when param8 != NULL; otherwise local variables are uninitialized.
    }

    // Always set default value and extra parameters
    args.field3 = g_materialDefault;   // +0x0C
    args.field4 = param6;              // +0x10
    args.field5 = param7;              // +0x14
    args.type = 2;                     // +0x18 – operation type (e.g., set material, bind shader)

    // Compute conditional address of the copied data (may be used for debugging or alignment)
    // local_14 = -(uint)(param8 != 0) & (uint)&args.field0;  // not used in the call.

    // Call internal setup function with packed arguments
    Material::setParamsInternal(this, param2, param3, param4, param5, &args);

    return this;
}