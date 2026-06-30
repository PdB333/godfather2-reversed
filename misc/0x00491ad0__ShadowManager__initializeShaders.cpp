// FUNC_NAME: ShadowManager::initializeShaders

#include <windows.h> // For D3DXHANDLE (or equivalent)

// Forward declarations of external engine functions.
// These are likely part of the EARS render device management.
typedef void* (__fastcall* GetRenderDeviceFunc)(void*); // Actually takes address of global
typedef void* (__fastcall* GetShaderHandleFunc)(void*, const char*);

// Global pointer to render device singleton (from PTR_DAT_0110a07c)
extern void* PTR_DAT_0110a07c;

class ShadowManager {
public:
    // Offsets:
    // +0x14: IDirect3DDevice9* m_pRenderDevice
    // +0x350: D3DXHANDLE m_hThirdShadowSampler   // "g_3rdShadowSampler"
    // +0x354: D3DXHANDLE m_hViewToShadowMatrix   // "g_view_to_3rd_shadow"

    void __thiscall initializeShaders();
};

// External functions (the actual names are unknown, renamed for clarity)
extern void* __fastcall GetRenderDevice(void* pGlobalPtr); // FUN_0060a2e0
extern void  __fastcall SetupShadowMap();                  // FUN_004907a0
extern void  __fastcall SetupViewToShadowMatrix();         // FUN_00491580
extern void* __fastcall GetShaderConstantHandle(void* pDevice, const char* szName); // FUN_0060a580

void __thiscall ShadowManager::initializeShaders() {
    // Obtain the render device from the global manager (singleton pattern).
    void* pDevice = GetRenderDevice(&PTR_DAT_0110a07c);
    *(void**)(this + 0x14) = pDevice; // m_pRenderDevice

    // Initialize shadow map and view-to-shadow matrix settings.
    SetupShadowMap();                // FUN_004907a0
    SetupViewToShadowMatrix();       // FUN_00491580

    // Retrieve shader constant handles for third-person shadow rendering.
    void* hSampler = GetShaderConstantHandle(pDevice, "g_3rdShadowSampler");
    *(void**)(this + 0x350) = hSampler; // m_hThirdShadowSampler

    void* hMatrix = GetShaderConstantHandle(pDevice, "g_view_to_3rd_shadow");
    *(void**)(this + 0x354) = hMatrix;  // m_hViewToShadowMatrix
}