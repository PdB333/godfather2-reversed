// FUNC_NAME: CmdPortalManager::loadDLL
#include <windows.h>

// Represents an interface to CmdPortalClient.DLL for online services.
// Offsets relative to 'this':
// +0x90 : HMODULE m_hModule
// +0x94 : FARPROC m_connectProc
// +0x98 : FARPROC m_disconnectProc
// +0x9c : FARPROC m_isConnectedProc
// +0xa0 : FARPROC m_itemEnumPatchesProc
// +0xa4 : FARPROC m_itemInstallStartBatchProc
__declspec(naked) bool CmdPortalManager::loadDLL()
{
    __asm
    {
        mov eax, [ecx+0x90]  // m_hModule
        test eax, eax
        jnz alreadyLoaded
        push offset "CmdPortalClient.DLL"
        call LoadLibraryA
        mov [ecx+0x90], eax  // store module handle
        test eax, eax
        jz loadFailed
        push offset "Connect"
        push eax
        call GetProcAddress
        mov [ecx+0x94], eax  // m_connectProc
        push offset "Disconnect"
        push dword ptr [ecx+0x90]
        call GetProcAddress
        mov [ecx+0x98], eax  // m_disconnectProc
        push offset "IsConnected"
        push dword ptr [ecx+0x90]
        call GetProcAddress
        mov [ecx+0x9c], eax  // m_isConnectedProc
        push offset "ItemEnumPatches"
        push dword ptr [ecx+0x90]
        call GetProcAddress
        mov [ecx+0xa0], eax  // m_itemEnumPatchesProc
        push offset "ItemInstallStartBatch"
        push dword ptr [ecx+0x90]
        call GetProcAddress
        mov [ecx+0xa4], eax  // m_itemInstallStartBatchProc
        // Validate all required function pointers
        cmp dword ptr [ecx+0x94], 0
        je cleanupAndFail
        cmp dword ptr [ecx+0x98], 0
        je cleanupAndFail
        cmp dword ptr [ecx+0x9c], 0
        je cleanupAndFail
        cmp dword ptr [ecx+0xa0], 0
        je cleanupAndFail
        cmp dword ptr [ecx+0xa4], 0
        je cleanupAndFail
        mov eax, 1
        ret
    cleanupAndFail:
        // Call helper to unload DLL and reset pointers
        push ecx
        call FUN_006a25a0
        add esp, 4
    loadFailed:
        xor eax, eax
        ret
    alreadyLoaded:
        mov eax, 1
        ret
    }
}