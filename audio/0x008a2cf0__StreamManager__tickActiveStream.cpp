// FUNC_NAME: StreamManager::tickActiveStream
// Function address: 0x008a2cf0
// Calls GetStreamManager() (singleton at 0x00ad8d40), then retrieves active stream via virtual at vtable+0x30,
// and calls its update via virtual at vtable+0x38.
// This is likely part of the audio/stream subsystem (EARS engine).

// Declarations for involved classes (vtable layout assumption)
class IActiveStream {
public:
    virtual void __thiscall update(void) = 0; // vtable offset +0x38
};

class StreamManager {
public:
    virtual IActiveStream* __thiscall getActiveStream(void) = 0; // vtable offset +0x30
};

// External singleton getter (defined elsewhere)
StreamManager* __cdecl GetStreamManager(void); // FUN_00ad8d40

void __cdecl FUN_008a2cf0(void)
{
    StreamManager* pMgr = GetStreamManager();
    if (pMgr != nullptr) {
        IActiveStream* pStream = pMgr->getActiveStream();
        if (pStream != nullptr) {
            pStream->update();
        }
    }
}