// FUNC_NAME: Sentient::setAction
void Sentient::setAction(float duration, int actionId, int param) {
    // duration stored at +0x158 (likely animation speed or time factor)
    *(float *)((uint8_t *)this + 0x158) = duration;

    // If actionId is larger than 0xFFFF, it's considered an error;
    // call a global error handler (vtable function at index 1 of a global object)
    if ((unsigned int)actionId > 0xFFFF) {
        (*(void (**)())(*(uint32_t *)g_pGlobalHandler + 4))();
    }

    // Lower 16 bits of actionId are used as the actual ID
    if ((short)actionId != 0) {
        // Current action block at +0xF0 (16 bytes)
        *(uint32_t *)((uint8_t *)this + 0xF0) = 0;          // +0xF0: action start time
        *(uint16_t *)((uint8_t *)this + 0xF4) = 1;          // +0xF4: active flag
        *(int16_t  *)((uint8_t *)this + 0xF6) = (short)actionId;  // +0xF6: action ID
        *(uint32_t *)((uint8_t *)this + 0xFC) = param;      // +0xFC: action parameter (target, sub‑ID, etc.)
        *(uint16_t *)((uint8_t *)this + 0xF8) = 0;          // +0xF8: sub‑state or timer
    }

    // Clear the "action requested" bit (bit 9) in the flags at +0x7C
    *(uint32_t *)((uint8_t *)this + 0x7C) &= ~0x200;
}