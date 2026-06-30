// FUNC_NAME: EarsTransform::synchronizeLocalToWorld
// Address: 0x0047bf10
// Role: Updates engine transform handle and copies local rotation to world rotation.

#include <cstdint>

// Standard vector type for 4 floats (quaternion or similar)
struct Vector4 {
    float x, y, z, w;
};

// Forward declaration of the global engine vtable table.
// DAT_01223510 points to an array of function pointers.
extern void* gEngineVtable[];

// Class representing a transform component in the EARS engine.
// Reconstructed from Ghidra decompilation at 0x0047bf10.
class EarsTransform {
public:
    // Field offsets relative to this pointer:
    // +0x80: Object identifier (e.g., a handle or ID)
    uint32_t m_objectId;
    // +0x84: Previous copy of m_objectId
    uint32_t m_lastObjectId;
    // +0x88–0x90: Possibly unused or padding
    // +0x94: Engine-side transform handle passed to virtual calls
    void* m_engineHandle;
    // +0x98: Local rotation (quaternion or 4-float vector)
    Vector4 m_localRotation;
    // +0xB0: World rotation (copy of local rotation after synchronisation)
    Vector4 m_worldRotation;

    // Synchronises the local rotation to the world rotation and notifies the engine.
    // This function assumes __thiscall convention (this in ECX/ESI).
    void synchronizeLocalToWorld() {
        // Virtual function pointer at global vtable offset 0xBC (index 0xBC/4 = 47)
        // Signature: void __thiscall SetEngineTransform(void* engineHandle, uint32_t objectId)
        // But here it is called as a plain function (no implicit this), so we declare it as __cdecl or __stdcall.
        // Ghidra shows a indirect call: (**(code **)(*DAT_01223510 + 0xbc))(this + 0x94, *(this + 0x80));
        typedef void (__stdcall *SetTransformFunc)(void* handle, uint32_t id);
        SetTransformFunc func = (SetTransformFunc)gEngineVtable[0xBC / 4];
        func(m_engineHandle, m_objectId);

        // Update the cached object ID
        m_lastObjectId = m_objectId;

        // Copy local rotation to world rotation (4 floats)
        m_worldRotation = m_localRotation;
    }
};
```