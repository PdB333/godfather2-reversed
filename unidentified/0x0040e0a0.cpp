// Reconstructed from Ghidra export: 0x0040e0a0
// Resolves the active render anchor and writes a 4-float vector to the caller's
// output buffer. In the original binary the output pointer is carried in ESI.

#include <cstdint>
#include <intrin.h>

extern "C" {
    extern std::uint8_t DAT_01205248;
    extern void* DAT_0122339c;
    extern void* DAT_012233a0;
    extern float DAT_00e2b1a4;
}

struct Vec4f {
    float x;
    float y;
    float z;
    float w;
};

using ResolveBaseFn = std::uint8_t* (__thiscall*)(void* thisPtr);

static inline void* GetThreadLocalRuntimeContext()
{
    // The binary reads a runtime pointer out of the TLS block at fs:[0x2c].
    auto* const tlsRoot = *reinterpret_cast<std::uint8_t**>(__readfsdword(0x2c));
    return *reinterpret_cast<void**>(tlsRoot + 0x24);
}

extern "C" void* FUN_0040e0a0(Vec4f* outAnchor)
{
    // Primary path: use the active scene/player context when the render mode flag
    // is enabled and the scene state object is present.
    if (DAT_01205248 != 0 && DAT_0122339c != nullptr) {
        auto* const sceneState = reinterpret_cast<std::uint8_t*>(DAT_0122339c);

        void* activeObject = nullptr;
        if (*reinterpret_cast<std::uint32_t*>(sceneState + 0x154) == 0) {
            activeObject = GetThreadLocalRuntimeContext();
        } else {
            activeObject = *reinterpret_cast<void**>(sceneState + 0x14);
        }

        if (activeObject != nullptr) {
            auto* const activeBytes = reinterpret_cast<std::uint8_t*>(activeObject);
            outAnchor->x = *reinterpret_cast<float*>(activeBytes + 0x70);
            outAnchor->y = *reinterpret_cast<float*>(activeBytes + 0x74);
            outAnchor->z = *reinterpret_cast<float*>(activeBytes + 0x78);
            outAnchor->w = *reinterpret_cast<float*>(activeBytes + 0x7c);
            return activeObject;
        }
    }

    // Fallback path: ask the global manager for its first active entry and read a
    // secondary transform block from the resolved object.
    auto* const entityManager = reinterpret_cast<std::uint8_t*>(DAT_012233a0);
    if (entityManager != nullptr &&
        *reinterpret_cast<std::uint32_t*>(entityManager + 0x0c) != 0) {
        auto* const slotArray = *reinterpret_cast<void***>(entityManager + 0x04);
        if (slotArray != nullptr && slotArray[0] != nullptr) {
            void* const firstEntry = slotArray[0];
            auto* const vtable = *reinterpret_cast<void***>(firstEntry);
            auto* const resolvedBase = reinterpret_cast<std::uint8_t*>(
                (reinterpret_cast<ResolveBaseFn>(vtable[3]))(firstEntry));

            outAnchor->x = *reinterpret_cast<float*>(resolvedBase + 0x100);
            outAnchor->y = *reinterpret_cast<float*>(resolvedBase + 0x104);
            outAnchor->z = *reinterpret_cast<float*>(resolvedBase + 0x108);
            outAnchor->w = *reinterpret_cast<float*>(resolvedBase + 0x10c);
            return resolvedBase + 0xd0;
        }
    }

    // No valid source object. Return a zero vector with homogeneous w = 1.0f.
    outAnchor->x = 0.0f;
    outAnchor->y = 0.0f;
    outAnchor->z = 0.0f;
    outAnchor->w = DAT_00e2b1a4;
    return DAT_012233a0;
}
