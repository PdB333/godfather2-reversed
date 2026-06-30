// FUNC_NAME: StreamPlayer::updateStream
// Address: 0x0059acf0
// Role: Updates the stream playback state by checking stream data type and dispatching to controller methods.

class StreamPlayer {
public:
    // Offsets are relative to 'this' (param_1)
    // +0x08: m_pStreamData (pointer to stream data structure)
    // +0x1C0: m_pController (pointer to controller object, likely a vtable-based class)

    void __thiscall updateStream();

private:
    struct StreamData {
        short m_type;          // +0x02: Type identifier (expected value 0x1C)
        int m_pBuffer;         // +0x04: Buffer pointer (non-null indicates active data)
        int m_field_0x08;      // +0x08: Some parameter
        int m_field_0x0C;      // +0x0C: Parameter 1
        int m_field_0x10;      // +0x10: Parameter 2
        int m_field_0x14;      // +0x14: Parameter 3
    };

    // Controller vtable layout (assumed __thiscall)
    struct ControllerVTable {
        void (__thiscall *method0x48)(void* this);          // +0x48: No-argument method (e.g., stop/reset)
        void (__thiscall *method0x4C)(void* this, int param1, int param2, int param3, int param4); // +0x4C: Parameterized method (e.g., start/play)
    };
};

// Global function pointer from DAT_01205590+4 (likely error/fallback)
extern void (*g_errorHandler)(void);

void __thiscall StreamPlayer::updateStream() {
    void* pController = *(void**)((char*)this + 0x1C0); // m_pController
    if (pController != nullptr) {
        StreamData* pData = *(StreamData**)((char*)this + 0x08); // m_pStreamData
        // Check if stream data type is 0x1C (expected type)
        if (pData->m_type != 0x1C) {
            // Type mismatch, call error/fallback handler
            g_errorHandler();
        }

        // Re-read data pointer after possible error handling
        pData = *(StreamData**)((char*)this + 0x08);
        if (pData->m_pBuffer != 0) {
            // If buffer is active, call controller's stop/reset method
            void* controllerVTable = *(void**)pController;
            void (*method)(void*) = *(void(**)(void*))((char*)controllerVTable + 0x48);
            method(pController);
            return;
        }

        // Otherwise, start playback with parameters from stream data
        void* controllerVTable = *(void**)pController;
        void (*method)(void*, int, int, int, int) = *(void(**)(void*, int, int, int, int))((char*)controllerVTable + 0x4C);
        method(pController,
               pData->m_field_0x0C,
               pData->m_field_0x10,
               pData->m_field_0x14,
               pData->m_field_0x08);
    }
}