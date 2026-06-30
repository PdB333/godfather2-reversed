// Xbox PDB: EARS::Modules::LuaToEarsAudioGlue::Open
// FUNC_NAME: AudioScriptBindings::registerAllBindings
// Function address: 0x00436580
// Registers all EARS audio engine script bindings (PlayEmx, PlayStream, etc.)
// Uses a stack-based binding registration pattern: each binding has 0x10 bytes
// (two 4-byte function pointer slots), stored on a local stack pointed to by this+0x8.
// The manager at this+0x40 handles the actual binding.

#include <cstdint>
#include <cstring>

// Forward declarations for unknown functions (likely internal engine helpers)
extern void addScriptBindingName(void* obj, const char* name); // FUN_00625ca0
extern void registerScriptBinding(void* manager, void* funcSlot1, void* funcSlot2); // FUN_00633d60

// Structure representing a binding entry (two 4-byte function pointers)
struct BindingEntry {
    void* func1;
    void* func2;
};

// Helper: register a named binding with two function pointers
void registerSingleBinding(void* thisPtr, const char* name, BindingEntry* entry) {
    addScriptBindingName(thisPtr, name);
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(thisPtr) + 8) = entry;
    // Increment stack pointer by 8 (seems to skip first slot, but then we pass entry-0x10 etc.)
    // Actually the pattern: clear, add 8, call with (entry-0x10, entry-8), then subtract 0x10.
    // This suggests the stack pointer is being manipulated to point to the entry.
    // We'll replicate the original logic exactly.
}

void AudioScriptBindings::registerAllBindings(void* thisPtr) {
    // thisPtr+0x8: pointer to current binding stack (grows downward?)
    // thisPtr+0x40: internal binding manager

    // Local variable for the binding manager
    void* manager = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(thisPtr) + 0x40);

    // Helper macro to register one binding (mimics the pattern)
    #define REGISTER_BINDING(name) \
    do { \
        addScriptBindingName(thisPtr, name); \
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(thisPtr) + 8) = nullptr; \
        *(reinterpret_cast<uint8_t*>(thisPtr) + 8) += 8; \
        registerScriptBinding(manager, \
            *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(thisPtr) + 8) - 0x10, \
            *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(thisPtr) + 8) - 0x8); \
        *(reinterpret_cast<uint8_t*>(thisPtr) + 8) -= 0x10; \
    } while(0)

    // Register all audio script bindings
    REGISTER_BINDING("PlayEmx");
    REGISTER_BINDING("PlayEntityEmx");
    REGISTER_BINDING("StopEmx");
    REGISTER_BINDING("SetEmxVolume");
    REGISTER_BINDING("SetEmxPitch");
    REGISTER_BINDING("SetEmxPosition");
    REGISTER_BINDING("SetEmxAzimuth");
    REGISTER_BINDING("PlayStream");
    REGISTER_BINDING("PrimeStream");
    REGISTER_BINDING("StartStream");
    REGISTER_BINDING("StopStream");
    REGISTER_BINDING("SetStreamMixCategory");
    REGISTER_BINDING("SetStreamEmitterLocation");
    REGISTER_BINDING("SetStreamVolume");
    REGISTER_BINDING("SetStreamChannelVolume");
    REGISTER_BINDING("SetStreamEffect");
    REGISTER_BINDING("SetGlobalEffect");
    REGISTER_BINDING("SetPluginEffect");
    REGISTER_BINDING("SetStreamChannelEffectSend");
    REGISTER_BINDING("GetStreamStatus");
    REGISTER_BINDING("GetStreamDuration");
    REGISTER_BINDING("PrimeEarsAudioStream");
    REGISTER_BINDING("PlayEarsAudioStream");
    REGISTER_BINDING("StopEarsAudioStream");
    REGISTER_BINDING("SetEarsAudioStreamStopMessage");
    REGISTER_BINDING("SetStreamPrimeFunction");
    REGISTER_BINDING("SetEnvelopeMap");
    REGISTER_BINDING("GetEnvelopeValue");

    #undef REGISTER_BINDING
}