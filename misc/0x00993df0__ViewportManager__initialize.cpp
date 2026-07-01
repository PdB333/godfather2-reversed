// FUNC_NAME: ViewportManager::initialize
// Function address: 0x00993df0
// Initializes the viewport manager, sets up display resolution, creates render target, and registers a callback.

#include <cstdint>

// Forward declarations for external functions
extern void* getDisplaySettings(); // FUN_0060d850
extern int* getDisplayModeInfo(void* settings); // FUN_00606370
extern uint32_t createRenderTarget(int type, uint32_t flags, int width, int height, int mipLevels, int format); // FUN_00606c80
extern void registerCallback(int id, void* callback, int size); // FUN_00607ca0

// Global data (from Ghidra)
extern uint32_t* g_pViewportManager; // DAT_0113094c
extern uint8_t* g_pMemoryStack; // DAT_01206880 (base of memory stack)
extern uint32_t g_hRenderTarget; // DAT_01130944

// External float constants (from data section)
extern float g_fScreenScaleX; // DAT_00e44610
extern float g_fScreenScaleY; // _DAT_00e576cc (maybe)
extern float g_fSomeConstant1; // _DAT_00e576c0
extern float g_fSomeConstant2; // _DAT_00e576c4
extern float g_fSomeConstant3; // _DAT_00e576c8
extern float g_fSomeConstant4; // DAT_00e44584

// Vtable pointers (from data section)
extern void* g_vtableViewportManager; // PTR_FUN_00d92234
extern void* g_vtableViewportManager2; // PTR_LAB_00d92220
extern void* g_vtableViewportManager3; // PTR_LAB_00d92230
extern void* g_vtableRenderTarget; // PTR_LAB_00e576d0
extern void* g_vtableRenderTarget2; // PTR_LAB_00e57720

// Callback function (address 0x00993a50)
extern void viewportCallback(); // LAB_00993a50

// Reconstructed class (simplified)
class ViewportManager {
public:
    // Vtable pointer at offset 0
    void* vtable;
    // Another vtable pointer at offset 4
    void* vtable2;
    // Screen width (float) at offset 8
    float screenWidth;
    // Screen height (float) at offset 12
    float screenHeight;
    // Additional members may follow

    // Constructor / initializer
    void* initialize() {
        // Set vtable pointers
        this->vtable2 = &g_vtableViewportManager2; // +0x04
        g_pViewportManager = this; // Store global singleton

        this->vtable = &g_vtableViewportManager; // +0x00
        this->vtable2 = &g_vtableViewportManager3; // +0x04 (overwrites previous)

        // Get display settings and extract resolution
        void* displaySettings = getDisplaySettings();
        int* displayModeInfo = getDisplayModeInfo(displaySettings);
        this->screenWidth = (float)*(uint16_t*)(displayModeInfo + 2); // +0x08
        this->screenHeight = (float)*(uint16_t*)(displayModeInfo + 4); // +0x0C

        // Push vtable and this pointer onto memory stack (object registration)
        int* stackPtr = (int*)(g_pMemoryStack + 0x14);
        *(void**)(g_pMemoryStack + 0x14) = &g_vtableRenderTarget;
        *stackPtr = *stackPtr + 4;
        *(void**)*stackPtr = this;
        *stackPtr = *stackPtr + 4;

        // Create render target (type 3, flags 0x200080, 4x4, mip 1, format -1)
        g_hRenderTarget = createRenderTarget(3, 0x200080, 4, 4, 1, 0xFFFFFFFF);

        // Push another vtable and the render target handle onto stack
        int base = (int)g_pMemoryStack;
        float fScaleY = g_fScreenScaleY; // _DAT_00e576cc
        float fScaleX = g_fScreenScaleX; // DAT_00e44610
        float fVar1 = fScaleY * fScaleX;

        *(void**)(base + 0x14) = &g_vtableRenderTarget2;
        *(int*)(base + 0x14) = *(int*)(base + 0x14) + 4;
        stackPtr = (int*)(base + 0x14);
        *(void**)(base + 0x14) = (void*)g_hRenderTarget;
        *stackPtr = *stackPtr + 4;

        // Compute packed color value (RGBA?)
        int local_8 = (int)(long long)(fVar1 + 0.5f); // ROUND
        int iVar4 = local_8 * 0x100;
        local_8 = (int)(long long)(g_fSomeConstant1 * fScaleX + 0.5f);
        iVar4 = iVar4 + local_8;
        local_8 = (int)(long long)(fScaleX * g_fSomeConstant2 + 0.5f);
        iVar4 = iVar4 * 0x100 + local_8;
        local_8 = (int)(long long)(g_fSomeConstant3 * g_fSomeConstant4 + 0.5f);
        *(int*)*stackPtr = local_8 + iVar4 * -0x100;
        *stackPtr = *stackPtr + 4;

        // Register callback (id 0, function at 0x00993a50, size 0x80)
        registerCallback(0, &viewportCallback, 0x80);

        return this;
    }
};