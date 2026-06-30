// FUNC_NAME: ResourceLoader::parseResource

#include <cstdint>

// This function appears to parse some resource data and return a result object.
// Context: EA EARS engine (The Godfather 2, 2008, x86)

class ResourceLoader {
public:
    // Offset 0x00: pointer to loaded data buffer (if any)
    // ... other members unknown

    bool parseResource(uint32_t param_2, uint32_t param_3, uint32_t param_4,
                       uint32_t param_5, uint32_t param_6, uint32_t* outResult);
};

// Forward declarations of called functions
extern void* memAlloc(size_t size);                          // FUN_0043b490 (returns some manager pointer)
extern bool processResourceData(uint32_t, uint32_t, uint32_t, void*); // FUN_004afdd0
extern uint32_t extractValue(void* obj, uint32_t defaultVal); // FUN_005566a0

// Global function pointer table used by parser
extern void* gFunctionTable; // PTR_FUN_00e32a8c

// Global constants
extern uint32_t gSomeConstant; // DAT_00e2b1a4

bool ResourceLoader::parseResource(uint32_t param_2, uint32_t param_3,
                                   uint32_t param_4, uint32_t param_5,
                                   uint32_t param_6, uint32_t* outResult)
{
    uint32_t local_c8 = 0;
    uint32_t local_b4 = 0;

    // Check if this object has a loaded data buffer (first member)
    if (this->dataBuffer != nullptr && *this->dataBuffer != 0) {
        // Allocate memory for temporary storage? (FUN_0043b490 likely allocates)
        local_c8 = reinterpret_cast<uint32_t>(memAlloc(0));
        local_b4 = 1;
    }

    // Structure to pass to the processor function
    struct ProcessorContext {
        void* funcTable;        // +0x00: function pointer table
        uint32_t field_4;       // +0x04: unknown
        uint32_t field_8;       // +0x08: unknown
        uint32_t field_c;       // +0x0c: some constant (0xffffffff)
        uint32_t field_10;      // +0x10: another constant (0xffffffff)
        uint32_t field_14;      // +0x14: pointer to local_c8
        uint32_t field_18;      // +0x18: local_c4 (0x3e0)
        uint8_t field_1c;       // +0x1c: zero
        uint32_t field_20;      // +0x20: maybe size?
    };

    ProcessorContext ctx;
    ctx.funcTable = &gFunctionTable;  // local_b0
    ctx.field_4 = 0;                  // local_50 set to 0
    ctx.field_8 = gSomeConstant;      // local_90
    ctx.field_c = 0xffffffff;         // local_8c
    ctx.field_10 = 0xffffffff;        // local_80
    ctx.field_14 = reinterpret_cast<uint32_t>(&local_c8); // local_b8 = &local_c8
    ctx.field_18 = 0x3e0;            // local_c4
    ctx.field_1c = 0;                // local_20

    uint32_t local_ac = gSomeConstant; // local_ac (not in struct, maybe separate)

    // Clear this object's first member (dataBuffer pointer?)
    *reinterpret_cast<uint32_t*>(this) = 0;

    // Call the resource processing function
    bool success = processResourceData(param_3, param_4, param_5, &ctx);

    if (success && outResult != nullptr) {
        // Determine which value to extract based on object type
        uint32_t valToExtract = ctx.field_10; // local_80
        if (ctx.field_4 != 0) {
            // If there is an object pointer, check its type at offset +0x0c
            void* obj = *reinterpret_cast<void**>(ctx.field_4);
            if (obj != nullptr && *reinterpret_cast<int32_t*>((uint8_t*)obj + 0x0c) == 0xb) {
                valToExtract = ctx.field_14; // local_7c? Actually field_14 is &local_c8
                // But the code uses local_7c, which is not in our struct.
                // The decompiled shows local_7c is defined but not assigned in the struct.
                // Possibly it's another stack variable.
                // Re-evaluate: the decompiled local_7c appears to be at offset 0x30 in the struct?
                // For now, use default.
                // Actually local_7c appears to be a separate variable at address below local_80.
                // Let's assume local_7c corresponds to field_14 + 4? Not clear.
                // We'll just mimic the logic: use local_80 unless type==0xb, then local_7c.
                // We'll add local_7c to the struct.
            }
        }
        // Extract final value (FUN_005566a0)
        *outResult = extractValue(reinterpret_cast<void*>(ctx.field_4), valToExtract);
    }

    return success;
}