// FUNC_NAME: AssetManager::loadAssetWithCallback
// Function address: 0x005f7ce0
// Attempts to load or retrieve an asset by resourceId (param_2). On success, invokes callback->vtable+0x10 with handle and extra data.
// On failure, calls internal error handler and returns 0.

// Assumed callback interface with virtual method at vtable offset 0x10
struct AssetLoadCallback {
    void** vtable; // +0x00
    // virtual void onAssetLoaded(int handle, int extraData) = 0; // at vtable[4] (0x10)
};

// Forward declarations of helper functions
int __thiscall AssetManager::internalLoadAsset(uint32_t resourceId, int* outExtraData); // FUN_005f79a0
void __thiscall AssetManager::handleLoadError(int errorCode); // FUN_005f7e50

class AssetManager {
public:
    // __thiscall, this in ecx
    int __thiscall loadAssetWithCallback(uint32_t resourceId, AssetLoadCallback* callback) {
        int extraData = 0;
        int handle = internalLoadAsset(resourceId, &extraData);
        if (handle != 0) {
            // Call virtual method at vtable offset 0x10
            typedef void (__thiscall* OnLoadFunc)(AssetLoadCallback*, int, int);
            OnLoadFunc onLoad = (OnLoadFunc)(callback->vtable[4]); // vtable[4] == offset 0x10
            onLoad(callback, handle, extraData);
            return 1;
        }
        handleLoadError(0);
        return 0;
    }
};