// FUNC_NAME: Object::resetStateFields
void __fastcall resetStateFields(void* thisPtr)
{
    // Zero out various state fields
    *(uint8_t*)((uintptr_t)thisPtr + 0xC) = 0;   // +0x0C: byte flag
    *(uint8_t*)((uintptr_t)thisPtr + 0xCC) = 0;  // +0xCC: byte
    *(uint8_t*)((uintptr_t)thisPtr + 0xD4) = 0;  // +0xD4: byte
    *(uint8_t*)((uintptr_t)thisPtr + 0x194) = 0; // +0x194: byte
    *(uint8_t*)((uintptr_t)thisPtr + 0x19C) = 0; // +0x19C: byte
    *(uint8_t*)((uintptr_t)thisPtr + 0x25C) = 0; // +0x25C: byte
    // Clear four consecutive ints at 0x270-0x27C
    *(int32_t*)((uintptr_t)thisPtr + 0x270) = 0;
    *(int32_t*)((uintptr_t)thisPtr + 0x274) = 0;
    *(int32_t*)((uintptr_t)thisPtr + 0x278) = 0;
    *(int32_t*)((uintptr_t)thisPtr + 0x27C) = 0;
    // Clear four consecutive ints at 0x280-0x28C
    *(int32_t*)((uintptr_t)thisPtr + 0x280) = 0;
    *(int32_t*)((uintptr_t)thisPtr + 0x284) = 0;
    *(int32_t*)((uintptr_t)thisPtr + 0x288) = 0;
    *(int32_t*)((uintptr_t)thisPtr + 0x28C) = 0;
    // Clear four consecutive ints at 0x290-0x29C
    *(int32_t*)((uintptr_t)thisPtr + 0x290) = 0;
    *(int32_t*)((uintptr_t)thisPtr + 0x294) = 0;
    *(int32_t*)((uintptr_t)thisPtr + 0x298) = 0;
    *(int32_t*)((uintptr_t)thisPtr + 0x29C) = 0;
    // Clear two bytes at 0x324-0x325
    *(uint8_t*)((uintptr_t)thisPtr + 0x324) = 0;
    *(uint8_t*)((uintptr_t)thisPtr + 0x325) = 0;
}