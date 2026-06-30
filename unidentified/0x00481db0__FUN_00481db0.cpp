extern "C" void __thiscall FUN_00481db0(void* this_, std::uint32_t param_2)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    auto* const attachedObject = *reinterpret_cast<std::uint8_t**>(self + 0x0c);
    std::uint32_t dispatchContext = 0;

    if (attachedObject != nullptr) {
        dispatchContext = DAT_01205a20;
    }

    if (dispatchContext != 0) {
        using ShouldUseImmediatePathFn = char (__thiscall*)(void*);
        auto* const vtable = *reinterpret_cast<void***>(this_);
        auto* const shouldUseImmediatePath =
            reinterpret_cast<ShouldUseImmediatePathFn>(vtable[0x0e]); // +0x38

        if (shouldUseImmediatePath(this_) != '\0') {
            auto* eventObject = static_cast<std::uint8_t*>(FUN_009c8e50(0x40));
            if (eventObject == nullptr) {
                eventObject = nullptr;
            } else {
                eventObject = static_cast<std::uint8_t*>(FUN_004819b0());
            }

            const std::int32_t sequenceValue =
                *reinterpret_cast<std::int32_t*>(attachedObject + 0x50);

            *reinterpret_cast<std::uint32_t*>(attachedObject + 0x50) = 0;
            *reinterpret_cast<std::int32_t*>(eventObject + 0x3c) = sequenceValue + 1;
            *reinterpret_cast<std::uint32_t*>(eventObject + 0x38) = param_2;

            FUN_0064ef60(eventObject);

            *reinterpret_cast<std::uint32_t*>(attachedObject + 0x3c) =
                *reinterpret_cast<std::uint32_t*>(attachedObject + 0x3c) | 1;

            FUN_0064d670();
            FUN_004a8900(dispatchContext);
            FUN_00454770(this_);
            return;
        }

        auto* eventObject = static_cast<std::uint8_t*>(FUN_009c8e50(0x40));
        if (eventObject == nullptr) {
            eventObject = nullptr;
        } else {
            eventObject = static_cast<std::uint8_t*>(FUN_004817a0());
        }

        FUN_0064ef60(eventObject);
        *reinterpret_cast<std::uint32_t*>(eventObject + 0x38) = param_2;
    }
}