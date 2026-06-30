// FUNC_NAME: queueOrExecuteRenderOperation

#include <cstdint>

// Global data (addresses from Ghidra)
extern void* g_RenderStack;           // DAT_01206880
extern void* g_CurrentViewport;        // DAT_011f38f0
extern int g_CurrentViewportIndex;     // DAT_011f38f4
extern void* g_RenderObject;           // DAT_01205750
extern void* g_RenderCallbacks;        // DAT_01205748, _DAT_00f15a68, DAT_0120574c
extern void* g_ObjectTable;            // DAT_011a0f28 (array of 0x38-byte entries)
extern void* g_UnknownFloat;           // DAT_012052f0, DAT_012052f4 (two floats?)
extern void* g_ThreadCheck;            // from FS:0x2c + 0x34

// Forward declarations of callees (internal engine functions)
void SetTransformMatrix(void* param1, void* param2, void* param3, int a, float scale, int b); // FUN_00609730
void SetViewportAndProjection(int unused, int vpX, int vpY);                                // FUN_00609340
void SetColorAndDepthState(int unused, int a, int b, float r, float g);                     // FUN_0060db60
void ProcessObject(uint32_t objectId, void* objectData);                                    // FUN_00606830

void __cdecl queueOrExecuteRenderOperation(uint32_t param1, uint32_t param2, uint32_t param3)
{
    // Check if we are in the main render thread (TLS flag at FS:0x2c + 0x34)
    if (*(int*)(**(int**)((uintptr_t)(__readfsdword(0x2c)) + 0x34)) == 0)
    {
        // Not in main thread: queue the parameters for later execution
        // g_RenderStack + 0x14 is a dynamic buffer pointer
        int* bufferPtr = (int*)((char*)g_RenderStack + 0x14);
        *(void**)bufferPtr = &LAB_0110b148;  // pointer to label (likely for function return)
        *bufferPtr += 4;
        uint32_t* slot = (uint32_t*)*bufferPtr;
        slot[0] = param1;
        slot[1] = param2;
        slot[2] = param3;
        *bufferPtr = (int)(slot + 3);
        return;
    }

    // Main thread: execute the render operation directly
    SetTransformMatrix((void*)param1, (void*)param2, (void*)param3, 0, 1.0f, 0);

    // Two viewports (e.g., left/right eye for stereo)
    uint32_t viewportParams[2];
    viewportParams[0] = *(uint32_t*)g_UnknownFloat;       // DAT_012052f0
    viewportParams[1] = *(uint32_t*)((char*)g_UnknownFloat + 4); // DAT_012052f4

    for (uint32_t viewportIdx = 0; viewportIdx < 2; ++viewportIdx)
    {
        uint32_t currentViewport = viewportParams[viewportIdx];
        for (int layerIdx = 0; layerIdx < 6; ++layerIdx)
        {
            // Set current viewport/layer state
            int oldViewport = *(int*)g_CurrentViewport;
            int oldIndex    = *(int*)&g_CurrentViewportIndex; // actually DAT_011f38f4
            *(uint32_t*)g_CurrentViewport = currentViewport;
            *(int*)&g_CurrentViewportIndex = layerIdx;

            SetViewportAndProjection(0, oldViewport, oldIndex); // restore? Not sure
            SetColorAndDepthState(0, 0, 0, 1.0f, 1.0f);

            // Draw the main object (likely render scene)
            void* renderObj = g_RenderObject; // DAT_01205750
            (*(void(**)(void*, int, void*, int, void*, void*, void*))(*(uintptr_t*)renderObj + 0xAC))
                (renderObj, 1, &LAB_011d91d8, 1, g_RenderCallbacks, g_UnknownFloat, g_RenderCallbacks); // second callbacks?

            // Draw up to 5 additional objects (e.g., overlays, gizmos, HUD)
            for (int objIdx = 0; objIdx < 5; ++objIdx)
            {
                if (objIdx == 4) continue; // skip index 4? suspicious
                uint32_t objectId = *(uint32_t*)((char*)g_CurrentViewport + objIdx * 8); // array interleaved?
                if (objectId == 0) continue;

                void* objectData;
                if (objectId < 0x1000)
                {
                    objectData = (char*)g_ObjectTable + objectId * 0x38;
                }
                else
                {
                    objectData = nullptr;
                }
                ProcessObject(objectId, objectData);
            }
        }
    }

    // Reset transform matrix after rendering
    SetTransformMatrix(nullptr, nullptr, nullptr, 0, 1.0f, 0);
}