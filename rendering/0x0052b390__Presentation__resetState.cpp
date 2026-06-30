// FUNC_NAME: Presentation::resetState

// Function at 0x0052b390: Resets presentation state, including frame rate limits,
// quality settings, viewport, clear color, and resource cleanup.
// Handles multiple modes based on in_EAX (passed in register):
// 0 - default clear viewport
// 1 - fade to grayscale color (param_1 as intensity) and set viewport (1,14,15)
// 2 - clear with different viewport (3,2,2)
// other - clear with viewport (1,2,1)

#include <cstdint>

// Global state variables (offsets relative to common base)
static uint32_t g_currentContextId = 0; // DAT_01218e58
static uint32_t g_oldContextId = 0; // DAT_011f38f0
static uint32_t g_contextChangeFlag = 0; // DAT_011f38f4

static int32_t g_minFrameRate = 0; // DAT_012058d0
static int32_t g_maxFrameRate = 0; // DAT_00f15988

static int32_t g_qualitySetting1 = 0; // _DAT_011f3a30
static int32_t g_qualitySetting2 = 0; // _DAT_011f3a10
static int32_t g_qualitySetting3 = 0; // _DAT_011f3a3c
static int32_t g_qualitySetting4 = 0; // _DAT_011f3a38
static int32_t g_qualitySetting5 = 0; // _DAT_011f3a14
static int32_t g_qualitySetting6 = 0; // _DAT_011f3a44

// Resource array (stride 0x38 = 56 bytes)
static uint8_t g_resourcePool[?]; // DAT_011a0f28 (base)

struct ResourceEntry {
    uint8_t state;      // +0x00 byte, must be <4 to be valid
    uint8_t _pad0[0x0B];
    uint32_t flags;     // +0x0C
    uint8_t _pad1[0x10];
    void* memoryPtr;    // +0x1C (offset to DAT_011a0f44)
    // total size 0x38
};

// External function declarations
static void setContextMode(uint32_t mode); // FUN_00609890(1)
static void setContextTransition(uint32_t oldCtx, uint32_t newCtx); // FUN_0060df60
static void setClearColor(float r, float g, float b, float a); // FUN_00417f00
static void setViewport(int32_t x, int32_t y, int32_t width, int32_t height); // FUN_00417cf0
static void releaseResource(void* ptr, uint32_t size); // FUN_00606e60
static void updateResourceManager(); // FUN_006189c0
static void updateSomething(); // FUN_00530a60
static void updateSomethingElse(); // FUN_00530df0
static void resetSubsystemA(); // FUN_0052ae50
static void resetSubsystemB(); // FUN_00612e00
static void freeMemory(void* ptr, uint32_t size); // FUN_0060a460

void Presentation::resetState(float param_1)
{
    uint32_t contextId = g_currentContextId;

    // Handle context change
    if ((g_oldContextId == g_currentContextId) && (g_contextChangeFlag == 0))
    {
        setContextMode(1);
    }
    else
    {
        setContextTransition(g_oldContextId, g_currentContextId);
    }

    // Clamp frame rate limits to reasonable values
    if (g_minFrameRate < 22) g_minFrameRate = 22;
    if (g_maxFrameRate > 22) g_maxFrameRate = 22;
    g_qualitySetting1 = 1;
    if (g_minFrameRate < 14) g_minFrameRate = 14;
    if (g_maxFrameRate > 14) g_maxFrameRate = 14;
    g_qualitySetting2 = 0;
    if (g_minFrameRate < 25) g_minFrameRate = 25;
    if (g_maxFrameRate > 25) g_maxFrameRate = 25;
    g_qualitySetting3 = 5;
    if (g_minFrameRate < 24) g_minFrameRate = 24;
    if (g_maxFrameRate > 24) g_maxFrameRate = 24;
    g_qualitySetting4 = 0;
    if (g_minFrameRate < 15) g_minFrameRate = 15;
    if (g_maxFrameRate > 15) g_maxFrameRate = 15;
    g_qualitySetting5 = 0;

    // Handle mode-specific viewport/color settings
    int32_t viewportX, viewportW;
    if (in_EAX == 0)
    {
        viewportW = 2;
        viewportX = 1;
    }
    else if (in_EAX == 1)
    {
        float color = (float)((int)(param_1 * /*0x3F800000?*/g_floatFactor) & 0xFF);
        setClearColor(color, color, color, color);
        setViewport(1, 14, 15, 0); // Note: height passed in eax? Actually signature unknown
        goto afterViewportCall;
    }
    else if (in_EAX == 2)
    {
        viewportW = 2;
        viewportX = 3;
    }
    else
    {
        viewportW = 1;
        viewportX = 1;
    }
    setViewport(viewportX, 2, viewportW, 0);

afterViewportCall:
    // Update display parameters
    g_displayParam1 = g_currentResourceHandle1; // DAT_01219954 = DAT_012198fc
    g_displayParam2 = g_currentResourceHandle2; // DAT_01219950 = DAT_01219900
    g_displayMode = 4; // _DAT_01219a6c = 4

    if (g_somePointer == &g_resourceList) // DAT_012058e8 == &DAT_01219940
    {
        freeMemory(g_currentResourceHandle1, /*size*/);
        freeMemory(g_currentResourceHandle2, /*size*/);
    }

    updateSomething(); // FUN_00530a60

    // Clean up resource entry if valid
    if ((contextId != 0xFFFFFFFF) && (contextId < 0x1000))
    {
        int32_t idx = contextId * 0x38; // stride
        ResourceEntry* entry = reinterpret_cast<ResourceEntry*>(&g_resourcePool) + idx;
        if ((entry != nullptr) && (entry->state < 4))
        {
            if (entry->memoryPtr != nullptr)
            {
                releaseResource(entry->memoryPtr, 0x100000);
            }
            entry->flags = (entry->flags & 0xFC9C8FFF) | 0x100000;
            updateResourceManager();
        }
    }

    updateSomethingElse(); // FUN_00530df0

    // Clamp frame rate and set quality settings again
    if (g_minFrameRate < 27) g_minFrameRate = 27;
    if (g_maxFrameRate > 27) g_maxFrameRate = 27;
    g_qualitySetting6 = 0;

    resetSubsystemA();
    resetSubsystemB();

    g_displayParam2 = 0;
    g_displayParam1 = 0;
    g_extraParam1 = 0;
    g_extraParam2 = 0;

    // Repeat clamping cycle
    if (g_minFrameRate < 22) g_minFrameRate = 22;
    if (g_maxFrameRate > 22) g_maxFrameRate = 22;
    g_qualitySetting1 = 1;
    if (g_minFrameRate < 25) g_minFrameRate = 25;
    if (g_maxFrameRate > 25) g_maxFrameRate = 25;
    g_qualitySetting3 = 7;
    if (g_minFrameRate < 24) g_minFrameRate = 24;
    if (g_maxFrameRate > 24) g_maxFrameRate = 24;
    g_qualitySetting4 = 0;
    if (g_minFrameRate < 15) g_minFrameRate = 15;
    if (g_maxFrameRate > 15) g_maxFrameRate = 15;
    g_qualitySetting5 = 0;
    if (g_minFrameRate < 27) g_minFrameRate = 27;
    if (g_maxFrameRate > 27) g_maxFrameRate = 27;
    g_qualitySetting6 = 0;

    setViewport(1, 5, 6, 0);

    if (g_minFrameRate < 14) g_minFrameRate = 14;
    g_qualitySetting2 = 1;
    if (g_maxFrameRate > 14) g_maxFrameRate = 14;
}