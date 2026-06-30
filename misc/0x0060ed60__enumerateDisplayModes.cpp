// FUNC_NAME: enumerateDisplayModes
// Address: 0x0060ed60
// Enumerates display modes for a given adapter and D3DFORMAT. The modes are sorted using a comparison function at 0x0060e7a0.

#include <windows.h>
#include <d3d9.h>

static IDirect3D9* g_pDirect3D = nullptr; // +0x012058cc

int enumerateDisplayModes(UINT adapterIndex, D3DFORMAT* pFormat)
{
    D3DFORMAT format = *pFormat;

    if (g_pDirect3D == nullptr)
    {
        g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION); // 0x20
    }

    UINT modeCount = g_pDirect3D->GetAdapterModeCount(adapterIndex, format);
    UINT currentMode = 0;
    int result = 5; // initial value, possibly overwritten in loop

    if (modeCount != 0)
    {
        D3DDISPLAYMODE modeBuffer; // stored temporarily on stack (&stack0xffffffe0)
        do
        {
            if (g_pDirect3D == nullptr)
            {
                g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
            }
            g_pDirect3D->EnumAdapterModes(adapterIndex, format, currentMode, &modeBuffer);
            currentMode++;
            result = 5; // original code used unaff_ESI here (unknown value)
        } while (currentMode < modeCount);
    }

    // Sort display modes if more than one
    // The array pointer and count come from an unknown local variable iStack_4
    // Offsets: iStack_4+8 = pointer to D3DDISPLAYMODE array, iStack_4+0xc = count
    // For reference:
    // if (*(UINT*)(iStack_4 + 0xc) > 1)
    //     qsort(*(void**)(iStack_4 + 8), *(UINT*)(iStack_4 + 0xc), sizeof(D3DDISPLAYMODE), (int(__cdecl*)(const void*, const void*))0x0060e7a0);

    return result;
}