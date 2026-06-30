// FUNC_NAME: SurfaceManager::copySurface

#include <d3dx9.h>  // For D3DXLoadSurfaceFromSurface and IDirect3DSurface9

// Global data – actual names from game's symbol map
extern int32_t g_surfaceEntryIndex;              // DAT_012058a4
extern uint8_t g_surfaceEntryPool[];             // DAT_011a0f28 (array of 0x38-byte entries)
extern void* g_renderSurfaceManager;             // DAT_01205750

// Structure of an entry in the pool (size 0x38)
struct SurfaceEntry {
    char    unknown_0x00[0x14];                  // +0x00
    IDirect3DSurface9* surface;                  // +0x14
    // remaining 0x24 bytes...
};

void SurfaceManager::copySurface() {
    // Locate the appropriate entry in the surface pool
    SurfaceEntry* entry = nullptr;
    if (g_surfaceEntryIndex < 0x1000) {
        entry = reinterpret_cast<SurfaceEntry*>(
            &g_surfaceEntryPool + g_surfaceEntryIndex * 0x38
        );
    }

    // Retrieve the source surface from the entry
    IDirect3DSurface9* srcSurface = entry ? entry->surface : nullptr;

    // Call a virtual method on the source surface (e.g., Prepare, Lock, or GetSurfaceDesc)
    // vtable offset 0x48
    (*(void (__thiscall**)(IDirect3DSurface9*))(
        *(uintptr_t*)srcSurface + 0x48
    ))(srcSurface);

    // Acquire a destination surface from the global render surface manager
    IDirect3DSurface9* dstSurface = nullptr;
    // vtable offset 0x48, signature: (this, 0, 0, 0, &outSurface)
    (*(void (__thiscall**)(void*, uint32_t, uint32_t, uint32_t, IDirect3DSurface9**))(
        *(uintptr_t*)g_renderSurfaceManager + 0x48
    ))(g_renderSurfaceManager, 0, 0, 0, &dstSurface);

    // Perform the actual surface copy using D3DX
    D3DXLoadSurfaceFromSurface(
        dstSurface,         // destination surface
        nullptr,            // destination palette
        nullptr,            // destination rectangle (full)
        srcSurface,         // source surface
        nullptr,            // source palette
        nullptr,            // source rectangle (full)
        D3DX_FILTER_NONE,   // filter mode
        0                   // color key (disabled)
    );

    // Release the destination surface or adjust reference count
    // Two virtual calls at offset 0x08 on the manager (likely Release/AddRef pair or double release)
    (*(void (__thiscall**)(void*))(*(uintptr_t*)g_renderSurfaceManager + 8))(g_renderSurfaceManager);
    (*(void (__thiscall**)(void*))(*(uintptr_t*)g_renderSurfaceManager + 8))(g_renderSurfaceManager);
}