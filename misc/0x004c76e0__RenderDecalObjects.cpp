// FUNC_NAME: RenderDecalObjects
// Function address: 0x004c76e0
// This function renders a list of decal/effect objects. It iterates over an array of object pointers,
// checks a flag, and for each active object, sets up rendering state, draws the object, and restores state.
// It also manages a global transform stack and a context pointer.

#include <cstdint>

// Forward declarations of called functions (assumed from EA EARS engine)
void ProfilerPushScope(int scopeId); // 0x00613440
void ProfilerPopScope(int scopeId);  // 0x00613570
void MatrixMultiply(float* out, float* a, float* b); // 0x00609500 (assumed)
void UpdateCameraTransform(); // 0x004236f0 (assumed)
void UpdateLighting();        // 0x00424470 (assumed)
void DebugDrawEnable(bool enable); // 0x00614ab0 (assumed)
void DebugDrawDisable();      // 0x00614a50 (assumed)
void ClearBuffer(void* buf, int value, size_t size); // 0x006124c0 (assumed)
bool IsObjectVisible();       // 0x004166b0 (assumed)
void BeginDrawObject(uint32_t objectId, int pass, int shaderId); // 0x0049e2f0 (assumed)
void EndDrawObject(uint32_t objectId, int pass, int shaderId);   // 0x0049e4c0 (assumed)
void SetRenderState(int state, uint32_t param1, uint8_t param2, int param3, int param4, int param5, int param6); // 0x0060c8d0 (assumed)
void SetRenderState2(uint16_t state, uint32_t param1, uint32_t param2, uint16_t param3, uint16_t param4); // 0x0060cb70 (assumed)
void SetGlobalTransform(int index, int value); // 0x0060c8d0 variant? Not sure.

// Global variables (from Ghidra)
extern int DAT_01163ee4;       // Current index or pointer
extern int DAT_01163ee0;       // Base of object pointer array
extern int DAT_01163edc;       // Number of objects in array
extern int DAT_012058b0;       // Current transform index
extern int DAT_01205838;       // Last used transform index
extern int DAT_01205750;       // Pointer to some manager (vtable)
extern int DAT_011da800;       // Flag for some state
extern int DAT_011da804;       // Another flag
extern int DAT_0120546c;       // Lock flag
extern int DAT_012058d0;       // Some min/max clamp value
extern int DAT_00f15988;       // Another clamp value
extern int DAT_011f39f4;       // Some state flag
extern int DAT_011f3a10;       // Another state flag
extern int DAT_011f3a44;       // Another state flag
extern int DAT_011f7430;       // Debug flag (bit 0)
extern int DAT_00e36570;       // Some data (4 bytes)
extern int DAT_00e2b1a4;       // Some constant (likely zero)
extern int DAT_011f6be8[2];    // Context pointer array (indexed by TLS flag)
extern float DAT_011f3928[6];  // Transform array (6 floats per entry, stride 0x18)
extern float DAT_011f3920[6];
extern float DAT_011f3918[6];
extern float DAT_011f391c[6];
extern float DAT_011f392c[6];
extern float DAT_011f3924[6];
extern float DAT_011f6bb8[3];  // Another transform array (3 floats per entry, stride 0xC)
extern float DAT_011f6bbc[3];

// Structure for a decal object (inferred from offsets)
struct DecalObject {
    uint8_t unknown[8];      // +0x00
    uint8_t flags;           // +0x08 (bit 2 = active)
    uint8_t index;           // +0x07 (used for array indexing)
    uint32_t objectId;       // +0x54
    uint32_t param1;         // +0x64 (0x64? Actually +0x60? Wait, offsets: +0x54, +0x7, +0x26, +0x27, +0x3c, +0x60, +0x34, +0x30, +0x40, +0x42)
    // Let's map properly:
    // +0x07: byte index
    // +0x08: flags
    // +0x26: byte (some parameter)
    // +0x27: byte (another parameter)
    // +0x30: uint32_t
    // +0x34: uint32_t
    // +0x3c: uint16_t
    // +0x40: uint16_t
    // +0x42: uint16_t
    // +0x54: uint32_t objectId
    // +0x60: uint32_t param1
    // +0x6c: uint32_t pointer (maybe another object)
    // Offsets are approximate; we'll use the decompiled offsets.
    uint8_t byteIndex;       // +0x07
    uint8_t flags2;          // +0x08
    uint8_t byteParam1;      // +0x26
    uint8_t byteParam2;      // +0x27
    uint32_t uintParam1;     // +0x30
    uint32_t uintParam2;     // +0x34
    uint16_t shortParam1;    // +0x3c
    uint16_t shortParam2;    // +0x40
    uint16_t shortParam3;    // +0x42
    uint32_t objectId2;      // +0x54
    uint32_t param1;         // +0x60
    int* extraObject;        // +0x6c (pointer to another object)
};

void RenderDecalObjects() {
    ProfilerPushScope(3); // Begin profiling scope

    int currentIndex = DAT_01163ee4; // Save current index
    int* tlsBase = *(int**)(__readfsdword(0x2C)); // Get TLS base (FS:0x2C)
    int tlsFlag = (*(int*)(tlsBase + 0x34) != 0) ? 1 : 0; // Check TLS flag
    int savedContext = DAT_011f6be8[tlsFlag]; // Save current context
    DAT_011f6be8[tlsFlag] = DAT_01163ee4; // Set new context

    int transformIndex = DAT_012058b0; // Current transform index
    // Save current transform (6 floats) from array at index transformIndex
    float savedTransform[6];
    savedTransform[0] = DAT_011f3928[transformIndex * 6]; // Actually stride 0x18 = 6 floats
    savedTransform[1] = DAT_011f3920[transformIndex * 6];
    savedTransform[2] = DAT_011f3918[transformIndex * 6];
    savedTransform[3] = DAT_011f391c[transformIndex * 6];
    savedTransform[4] = DAT_011f392c[transformIndex * 6];
    savedTransform[5] = DAT_011f3924[transformIndex * 6];

    // Also save another transform (3 floats) from array indexed by currentIndex
    float savedTransform2[3];
    savedTransform2[0] = DAT_011f6bbc[currentIndex * 3];
    savedTransform2[1] = DAT_011f6bb8[currentIndex * 3]; // Note: order swapped in code? Actually code uses (&DAT_011f6bbc)[iVar13*3] and (&DAT_011f6bb8)[iVar13*3]
    // Let's follow the code: uVar1 = (&DAT_011f6bbc)[iVar13*3]; uVar4 = (&DAT_011f6bb8)[iVar13*3];
    // So we save those.

    // Now set the transform array at transformIndex to the saved values from currentIndex
    DAT_011f3924[transformIndex * 6] = savedTransform[5]; // Actually the code writes back in a specific order
    DAT_011f3920[transformIndex * 6] = savedTransform[1];
    DAT_011f3918[transformIndex * 6] = savedTransform[2];
    DAT_011f391c[transformIndex * 6] = savedTransform[3];
    DAT_011f3928[transformIndex * 6] = savedTransform2[1]; // uVar4 (from DAT_011f6bb8)
    DAT_011f392c[transformIndex * 6] = savedTransform2[0]; // uVar1 (from DAT_011f6bbc)

    // Multiply transforms? (FUN_00609500)
    MatrixMultiply(&DAT_011f3924[transformIndex * 6], &savedTransform2[0]); // Not sure about arguments

    UpdateCameraTransform(); // 0x004236f0

    // Copy some data to global (maybe a constant)
    DAT_011f6b60 = DAT_00e36570;
    *(uint64_t*)&DAT_011f6b64 = *(uint64_t*)&DAT_00e36574; // 8 bytes copy

    UpdateLighting(); // 0x00424470

    // Debug drawing
    if ((DAT_011f7430 & 1) != 0) {
        DebugDrawEnable(true); // 0x00614ab0
    }

    // Clamp some values
    if (DAT_012058d0 < 7) DAT_012058d0 = 7;
    if (DAT_00f15988 > 7) DAT_00f15988 = 7;
    DAT_011f39f4 = 1;

    if (DAT_012058d0 < 14) DAT_012058d0 = 14;
    if (DAT_00f15988 > 14) DAT_00f15988 = 14;
    DAT_011f3a10 = 0;

    if (DAT_012058d0 < 27) DAT_012058d0 = 27;
    if (DAT_00f15988 > 26) DAT_00f15988 = 27; // Note: condition is 0x1a < DAT_00f15988, so if >26 set to 27
    DAT_011f3a44 = 1;

    // Clear a local buffer (4 floats) to zero
    float clearBuffer[4];
    clearBuffer[0] = DAT_00e2b1a4;
    clearBuffer[1] = DAT_00e2b1a4;
    clearBuffer[2] = DAT_00e2b1a4;
    clearBuffer[3] = DAT_00e2b1a4;
    ClearBuffer(clearBuffer, 0, sizeof(clearBuffer)); // 0x006124c0

    DAT_0120546c = 1; // Set lock

    int objectArrayBase = DAT_01163ee0;
    int objectCount = DAT_01163edc;
    uint32_t i = 0;
    if (objectCount != 0) {
        do {
            DecalObject* obj = *(DecalObject**)(objectArrayBase + i * 8); // Array of pointers
            if ((obj->flags2 & 2) != 0) { // Check bit 2
                bool visible = IsObjectVisible(); // 0x004166b0
                if (visible && ((DAT_011f7430 & 1) != 0)) {
                    DebugDrawDisable(); // 0x00614a50
                }
                BeginDrawObject(obj->objectId2, 2, 0xe1); // 0x0049e2f0
                int newIndex = *(int*)(&DAT_01164014 + (uint)(obj->byteIndex) * 8); // Some array lookup
                if (DAT_01205838 != newIndex) {
                    // Call a virtual function on some manager (vtable+0x15c)
                    (**(code**)(*(int*)DAT_01205750 + 0x15c))(DAT_01205750, newIndex);
                    DAT_01205838 = newIndex;
                }
                // Set render state for main object
                SetRenderState(0, obj->param1, obj->byteParam1, 0, 0, 0, 1); // 0x0060c8d0
                if (obj->extraObject != 0) {
                    SetRenderState(1, *(int*)(obj->extraObject + 0x6c), obj->byteParam2, 0, 0, 0, 1); // 0x0060c8d0
                }
                SetRenderState2(obj->shortParam1, obj->uintParam2, obj->uintParam1, obj->shortParam2, obj->shortParam3); // 0x0060cb70
                if (obj->extraObject != 0) {
                    if (DAT_011da800 != 1) {
                        // Call virtual function (vtable+0x198)
                        (**(code**)(*(int*)DAT_01205750 + 0x198))(DAT_01205750, 1, 1);
                        DAT_011da800 = 1;
                    }
                    if (DAT_011da804 != 0) {
                        // Call virtual function (vtable+0x190)
                        (**(code**)(*(int*)DAT_01205750 + 400))(DAT_01205750, 1, 0, 0, 0);
                        DAT_011da804 = 0;
                    }
                }
                EndDrawObject(obj->objectId2, 2, 0xe1); // 0x0049e4c0
                objectArrayBase = DAT_01163ee0; // Reload base (maybe modified)
            }
            i++;
        } while (i < objectCount);
    }

    DAT_0120546c = 0; // Clear lock

    if (DAT_012058e8 != 0) {
        // Call virtual function on another manager (vtable+0x20)
        (**(code**)(*(int*)DAT_012058e8 + 0x20))();
    }

    // Restore clamps and flags
    if (DAT_012058d0 < 7) DAT_012058d0 = 7;
    if (DAT_00f15988 > 7) DAT_00f15988 = 7;
    DAT_011f39f4 = 1;

    if (DAT_012058d0 < 14) DAT_012058d0 = 14;
    if (DAT_00f15988 > 14) DAT_00f15988 = 14;
    DAT_011f3a10 = 1;

    if (DAT_012058d0 < 27) DAT_012058d0 = 27;
    if (DAT_00f15988 > 26) DAT_00f15988 = 27;
    DAT_011f3a44 = 0;

    // Restore context
    DAT_011f6be8[tlsFlag] = savedContext;

    // Restore transform
    int idx = DAT_012058b0 * 6;
    DAT_011f391c[idx] = savedTransform[3];
    DAT_011f3918[idx] = savedTransform[2];
    DAT_011f3920[idx] = savedTransform[1];
    DAT_011f3924[idx] = savedTransform[5];
    DAT_011f3928[idx] = savedTransform[0];
    DAT_011f392c[idx] = savedTransform[4];

    MatrixMultiply(&DAT_011f3924[idx], &savedTransform[4]); // Not sure about arguments

    UpdateCameraTransform(); // 0x004236f0

    ProfilerPopScope(3); // End profiling scope
    // 0x00614910 is called at the end? Actually the decompiled shows FUN_00614910() after pop. Let's include it.
    // The last call is FUN_00614910() which might be a finalization.
    // We'll call it as FinalizeRender();
    FinalizeRender(); // 0x00614910
}