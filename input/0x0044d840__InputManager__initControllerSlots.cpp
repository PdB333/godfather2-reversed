// FUNC_NAME: InputManager::initControllerSlots

void __thiscall InputManager::initControllerSlots(void)
{
    uint32_t defaultPadState;

    // FUN_0044d750 - base initialization (probably zeros some fields)
    this->initCommon();

    globalDefaultPadState = gInitialPadValue; // DAT_00e2b1a4 - global default value for first field

    // +0x12c: last field of slot3 (offset 300) – zeroed first in decompiled order
    *(uint32_t *)((uint8_t *)this + 0x12c) = 0;

    // Slot0 at offset 0xe0 (20 bytes)
    // +0xe0: field0 = defaultPadState
    // +0xe4: field1 = 0
    // +0xe8: field2 = 0
    // +0xec: field3 = 0
    // +0xf0: field4 = 0
    *(uint32_t *)((uint8_t *)this + 0xe0) = globalDefaultPadState;
    *(uint32_t *)((uint8_t *)this + 0xe4) = 0;
    *(uint32_t *)((uint8_t *)this + 0xe8) = 0;
    *(uint32_t *)((uint8_t *)this + 0xec) = 0;
    *(uint32_t *)((uint8_t *)this + 0xf0) = 0;

    // Slot1 at offset 0xf4 (20 bytes)
    *(uint32_t *)((uint8_t *)this + 0xf4) = globalDefaultPadState;
    *(uint32_t *)((uint8_t *)this + 0xf8) = 0;
    *(uint32_t *)((uint8_t *)this + 0xfc) = 0;
    *(uint32_t *)((uint8_t *)this + 0x100) = 0;
    *(uint32_t *)((uint8_t *)this + 0x104) = 0;

    // Slot2 at offset 0x108 (20 bytes)
    *(uint32_t *)((uint8_t *)this + 0x108) = globalDefaultPadState;
    *(uint32_t *)((uint8_t *)this + 0x10c) = 0;
    *(uint32_t *)((uint8_t *)this + 0x110) = 0;
    *(uint32_t *)((uint8_t *)this + 0x114) = 0;
    *(uint32_t *)((uint8_t *)this + 0x118) = 0;

    // Slot3 at offset 0x11c (20 bytes, last field already zeroed above)
    *(uint32_t *)((uint8_t *)this + 0x11c) = globalDefaultPadState;
    *(uint32_t *)((uint8_t *)this + 0x120) = 0;
    *(uint32_t *)((uint8_t *)this + 0x124) = 0;
    *(uint32_t *)((uint8_t *)this + 0x128) = 0;
    // Note: 0x12c is already 0 from the first assignment
}