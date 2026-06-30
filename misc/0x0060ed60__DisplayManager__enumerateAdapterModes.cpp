// FUNC_NAME: DisplayManager::enumerateAdapterModes
// Address: 0x0060ed60
// Role: Enumerates all display modes for a given adapter and format, sorts them, and returns the last HRESULT.

#include <d3d9.h>
#include <cstdlib>

// Global Direct3D9 interface (stored at 0x012058cc)
IDirect3D9* g_pD3D9 = nullptr;

// Comparator for sorting D3DDISPLAYMODE by width, then height
static int __cdecl compareDisplayModes(const void* a, const void* b) {
    const D3DDISPLAYMODE* modeA = (const D3DDISPLAYMODE*)a;
    const D3DDISPLAYMODE* modeB = (const D3DDISPLAYMODE*)b;
    if (modeA->Width != modeB->Width)
        return modeA->Width - modeB->Width;
    return modeA->Height - modeB->Height;
}

// Main enumeration function
uint DisplayManager::enumerateAdapterModes(UINT adapter, D3DFORMAT format) {
    // Ensure the D3D9 object is created (thunk to Direct3DCreate9)
    if (g_pD3D9 == nullptr) {
        g_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION); // D3D_SDK_VERSION = 0x20
    }

    // Get the number of available modes (vtable offset 0x18)
    uint modeCount = g_pD3D9->GetAdapterModeCount(adapter, format);

    // Local structure that the binary uses to hold the mode list.
    // Offsets based on decompilation: +0x08 = modes pointer, +0x0c = count
    struct ModeList {
        char pad0[0x08];      // unknown padding
        D3DDISPLAYMODE* modes; // +0x08
        uint count;            // +0x0c
    } modeList;

    modeList.modes = nullptr;
    modeList.count = 0;

    uint result = 5; // initial value (possibly a success constant, later overwritten)

    if (modeCount != 0) {
        // Allocate array for modes
        modeList.modes = new D3DDISPLAYMODE[modeCount];
        modeList.count = modeCount;

        // Enumerate each mode (vtable offset 0x1c)
        for (uint i = 0; i < modeCount; ++i) {
            HRESULT hr = g_pD3D9->EnumAdapterModes(adapter, format, i, &modeList.modes[i]);
            result = hr; // store last HRESULT (the binary uses unaff_ESI)
        }
    }

    // Sort modes if more than one (qsort at 0x00b9a370)
    if (modeList.count > 1) {
        qsort(modeList.modes, modeList.count, sizeof(D3DDISPLAYMODE), compareDisplayModes);
    }

    return result;
}