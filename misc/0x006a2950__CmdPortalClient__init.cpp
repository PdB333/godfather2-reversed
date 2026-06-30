// FUNC_NAME: CmdPortalClient::init
bool __fastcall CmdPortalClient::init(CmdPortalClient* this)
{
    // Check if already initialized (module handle at +0x90)
    if (this->hModule != 0) {
        return true;
    }

    // Load the CmdPortalClient DLL
    HMODULE hModule = LoadLibraryA("CmdPortalClient.DLL");
    this->hModule = hModule;
    if (hModule == 0) {
        return false;
    }

    // Retrieve function pointers from the DLL
    this->pfnConnect = (ConnectFunc)GetProcAddress(hModule, "Connect");
    this->pfnDisconnect = (DisconnectFunc)GetProcAddress(hModule, "Disconnect");
    this->pfnIsConnected = (IsConnectedFunc)GetProcAddress(hModule, "IsConnected");
    this->pfnItemEnumPatches = (ItemEnumPatchesFunc)GetProcAddress(hModule, "ItemEnumPatches");
    this->pfnItemInstallStartBatch = (ItemInstallStartBatchFunc)GetProcAddress(hModule, "ItemInstallStartBatch");

    // Verify all function pointers were obtained
    if (this->pfnConnect != 0 &&
        this->pfnDisconnect != 0 &&
        this->pfnIsConnected != 0 &&
        this->pfnItemEnumPatches != 0 &&
        this->pfnItemInstallStartBatch != 0) {
        return true;
    }

    // Cleanup on failure
    cleanupCmdPortalClient(); // FUN_006a25a0
    return false;
}