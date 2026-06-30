//FUNC_NAME: AptManager::loadAptFile
// Function at 0x005a03a0: Loads an APT file and initializes an AptInstance structure.
// Parameters: param_1 - resource ID or filename (int/string), param_2 - output AptInstance pointer
// Returns: 1 on success, 0 on failure

#include <cstdint>

// Forward declarations of called functions (assumed from EA EARS engine)
int AptCreate(int a1, int resourceId, int a3, int a4); // FUN_0059e2f0
int AptGetInstance(int aptHandle, int a2, int resourceId, int a4, int a5); // FUN_005aea60
int AptGetRenderer(); // FUN_0059c3b0
int AptGetTextureManager(); // FUN_0059c810
void AptSetTexture(int renderer, int texture); // FUN_005b5340

// Global variables (from decompiled data)
extern int g_bAptIsInitialized; // DAT_012055b0 - flag indicating APT system is initialized
extern int g_assertEnabled; // DAT_01128f5c - assertion enable flag
extern int g_someAptHandle; // DAT_0119cbbc - some global handle for comparison

// Assertion macro simulation (EA style)
#define EA_ASSERT(expr, msg, file, line) \
    do { \
        if (!(expr)) { \
            if (g_assertEnabled) { \
                /* Trigger debug break */ \
                __debugbreak(); \
            } \
        } \
    } while(0)

int AptManager::loadAptFile(int resourceId, AptInstance* outInstance)
{
    // If APT system is already initialized, skip assertion
    if (g_bAptIsInitialized != 0)
        goto mainLogic;

    // Assertion check: bAptIsInitialized must be true
    {
        const char* assertMsg = "bAptIsInitialized";
        const char* assertFile = "..\\source\\Apt\\Apt.cpp";
        int assertLine = 0x353; // 851 decimal
        int assertLevel = 2; // severity
        // The assertion macro would check a global flag and possibly trigger break
        if (g_assertEnabled == 0)
            goto mainLogic;
        // In debug builds, this would call the assertion handler
        // For reconstruction, we simulate with EA_ASSERT
        EA_ASSERT(g_bAptIsInitialized != 0, assertMsg, assertFile, assertLine);
    }

mainLogic:
    // Create APT object
    int aptHandle = AptCreate(0, resourceId, 1, 1);
    if (aptHandle == 0)
        return 0;

    // Get instance from handle
    int instanceHandle = AptGetInstance(aptHandle, 0, resourceId, 1, 1);
    if (instanceHandle == 0 || instanceHandle == g_someAptHandle)
        return 0;

    // Get renderer and texture manager
    int renderer = AptGetRenderer();
    if (renderer == 0)
        return 0;

    int textureManager = AptGetTextureManager();
    if (textureManager == 0)
        return 0;

    // Set texture for renderer
    AptSetTexture(renderer, textureManager);

    // Copy dimensions from instance to output structure
    outInstance->width = *(int*)(textureManager + 0x44);  // +0x44: width
    outInstance->height = *(int*)(textureManager + 0x48); // +0x48: height

    return 1;
}