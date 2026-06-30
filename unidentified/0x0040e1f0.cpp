// Reconstructed from Ghidra export: 0x0040e1f0
//
// Applies a runtime mode toggle, mirrors it into the engine command stream,
// and briefly rebases thread-local runtime state while the transition is being
// broadcast. The function emits several stream markers that appear to notify
// subsystems about the new mode and the currently relevant scene object.

#include <cstddef>
#include <cstdint>
#include <intrin.h>

struct EngineCommandStream
{
    std::uint8_t reserved[0x14];
    std::uint32_t* writeCursor; // Offset 0x14 in the original structure.
};

struct DispatchQuery
{
    std::uint32_t id;
    std::uint32_t reserved;
    std::uint8_t active;
    std::uint8_t padding[3];
};

struct Vec4f
{
    float x;
    float y;
    float z;
    float w;
};

struct ThreadRuntimeState
{
    std::uint32_t pad0;
    void* previousContext;      // +0x04
    std::uint8_t pad1[0x1c];
    void* currentObject;        // +0x24
    std::uint8_t pad2[0x0c];
    std::uint32_t contextFlags; // +0x34
};

extern "C"
{
    extern EngineCommandStream* DAT_01206880;
    extern std::uint32_t DAT_01206960;
    extern std::uint32_t DAT_01206968;
    extern std::uint32_t DAT_01206970;
    extern std::uint32_t DAT_01206978;
    extern std::uint32_t DAT_01206980;
    extern std::uint8_t DAT_012051fb;
    extern std::uint8_t DAT_0120535b;
    extern std::uint8_t DAT_012054e8;
    extern std::uint8_t DAT_0110ae74;
    extern std::uint8_t DAT_01223394;
    extern void* DAT_0122339c;
    extern float DAT_00e2b1a4;

    extern std::uint8_t PTR_LAB_0110afa0;
    extern std::uint8_t PTR_LAB_0110afc8;
    extern std::uint8_t PTR_LAB_0110b640;
    extern std::uint8_t PTR_LAB_0110afdc;
    extern std::uint8_t PTR_LAB_0110b018;
    extern std::uint8_t PTR_LAB_0110aff0;
    extern std::uint8_t PTR_LAB_0110b02c;
    extern std::uint8_t PTR_LAB_0110b054;
    extern std::uint8_t PTR_LAB_0110b040;
    extern std::uint8_t PTR_LAB_0110b004;
    extern std::uint8_t PTR_LAB_0110b068;
    extern std::uint8_t PTR_LAB_0110b07c;
    extern std::uint8_t PTR_LAB_0110b090;
    extern std::uint8_t PTR_LAB_0110afb4;

    void FUN_00408a00(std::uint32_t* param_1, char param_2);
    void FUN_0040b900(void);
    void FUN_0040e0a0(Vec4f* outAnchor);
    void FUN_00413b10(void);
    void FUN_004a6bf0(void);
}

static inline ThreadRuntimeState* GetThreadRuntimeState()
{
    // The engine stores a thread-local pointer array under fs:[0x2c].
    auto* const tlsSlots = *reinterpret_cast<ThreadRuntimeState***>(__readfsdword(0x2c));
    return tlsSlots[0];
}

static inline void PushMarker(EngineCommandStream* stream, const std::uint8_t* marker)
{
    *reinterpret_cast<std::uint32_t*>(stream->writeCursor) =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(marker));
    stream->writeCursor += 1;
}

static inline void PushPointer(EngineCommandStream* stream, void* value)
{
    *reinterpret_cast<void**>(stream->writeCursor) = value;
    stream->writeCursor += 1;
}

static inline void PushFlagByte(EngineCommandStream* stream, std::uint8_t value)
{
    *reinterpret_cast<std::uint8_t*>(stream->writeCursor) = value;
    stream->writeCursor = reinterpret_cast<std::uint32_t*>(
        (reinterpret_cast<std::uintptr_t>(stream->writeCursor) + 4u) & ~0x3u
    );
}

static inline void PushVec4(EngineCommandStream* stream, const Vec4f& value)
{
    *reinterpret_cast<Vec4f*>(stream->writeCursor) = value;
    stream->writeCursor += 4;
}

extern "C" void ApplyRuntimeModeChange(bool enabled)
{
    // If the global scene/system guard is set, let it flush any pending work
    // before the mode transition starts.
    if (DAT_01223394 != 0) {
        FUN_0040b900();
    }

    // This flag is visible to later object-registration code while the mode
    // transition is in progress, then cleared at the end.
    DAT_012054e8 = static_cast<std::uint8_t>(enabled);

    DispatchQuery dispatchQuery{DAT_01206960, 0, 0, {0, 0, 0}};
    FUN_00408a00(&dispatchQuery.id, 0);

    EngineCommandStream* const stream = DAT_01206880;
    PushMarker(stream, &PTR_LAB_0110afa0);
    PushFlagByte(stream, static_cast<std::uint8_t>(enabled));
    PushMarker(stream, &PTR_LAB_0110afc8);

    Vec4f anchor{0.0f, 0.0f, 0.0f, DAT_00e2b1a4};
    FUN_0040e0a0(&anchor);

    ThreadRuntimeState* const runtimeState = GetThreadRuntimeState();
    void* const savedContext = runtimeState->previousContext;

    void* sceneObject = nullptr;
    void* deferredObject = nullptr;

    if (DAT_0122339c != nullptr) {
        auto* const sceneState = reinterpret_cast<std::uint8_t*>(DAT_0122339c);
        if (*reinterpret_cast<std::uint32_t*>(sceneState + 0x154) == 0) {
            sceneObject = runtimeState->currentObject;
        } else {
            sceneObject = *reinterpret_cast<void**>(sceneState + 0x14);
        }

        if (sceneObject != nullptr) {
            // When the global runtime mode is already active, the current object
            // is deferred and restored later instead of being promoted now.
            if (DAT_012051fb != 0 || DAT_0110ae74 == 0) {
                deferredObject = sceneObject;
                sceneObject = nullptr;
            }
        }
    }

    if (sceneObject != nullptr) {
        runtimeState->currentObject = sceneObject;

        if (runtimeState->contextFlags == 0) {
            PushMarker(stream, &PTR_LAB_0110b640);
            PushPointer(stream, sceneObject);
        }
    }

    DispatchQuery activeQuery{DAT_01206980, 0, 0, {0, 0, 0}};
    FUN_00408a00(&activeQuery.id, 0);
    FUN_00413b10();

    PushMarker(stream, &PTR_LAB_0110afdc);
    PushPointer(stream, sceneObject);

    if (sceneObject != nullptr) {
        // Additional notifications are emitted only when a concrete object is
        // being promoted into the active runtime slot.
        FUN_004a6bf0();

        PushMarker(stream, &PTR_LAB_0110b018);
        PushPointer(stream, sceneObject);
        PushPointer(stream, nullptr);

        if (DAT_0120535b == 0) {
            PushMarker(stream, &PTR_LAB_0110aff0);
            PushPointer(stream, sceneObject);
        }

        PushMarker(stream, &PTR_LAB_0110b02c);
    }

    PushMarker(stream, &PTR_LAB_0110b054);
    PushVec4(stream, anchor);
    PushMarker(stream, &PTR_LAB_0110b040);

    if (sceneObject == nullptr) {
        if (deferredObject != nullptr) {
            PushMarker(stream, &PTR_LAB_0110b004);
            PushPointer(stream, deferredObject);
        }
    } else {
        runtimeState->currentObject = sceneObject;

        if (runtimeState->contextFlags == 0) {
            PushMarker(stream, &PTR_LAB_0110b640);
            PushPointer(stream, sceneObject);
        }

        DispatchQuery enableQuery{DAT_01206970, 0, 0, {0, 0, 0}};
        FUN_00408a00(&enableQuery.id, 0);

        PushMarker(stream, &PTR_LAB_0110b068);
        PushFlagByte(stream, 0);
    }

    if (savedContext != nullptr) {
        runtimeState->currentObject = savedContext;

        if (runtimeState->contextFlags == 0) {
            PushMarker(stream, &PTR_LAB_0110b640);
            PushPointer(stream, savedContext);
        }

        DispatchQuery restoreQuery{DAT_01206978, 0, 0, {0, 0, 0}};
        FUN_00408a00(&restoreQuery.id, 0);

        PushMarker(stream, &PTR_LAB_0110b068);
        PushFlagByte(stream, 1);
    }

    DispatchQuery finalQuery{DAT_01206968, 0, 0, {0, 0, 0}};
    FUN_00408a00(&finalQuery.id, 0);

    PushMarker(stream, &PTR_LAB_0110b07c);
    PushMarker(stream, &PTR_LAB_0110b090);
    PushFlagByte(stream, static_cast<std::uint8_t>(DAT_0110ae74 == 0));
    PushMarker(stream, &PTR_LAB_0110afb4);

    DAT_012054e8 = 0;
}
