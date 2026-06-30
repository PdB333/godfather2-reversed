// FUNC_NAME: AttributeManager::setFloatValue
void __thiscall AttributeManager::setFloatValue(AttributeManager* self, float newValue) {
    // +0x14: current float value, +0x28: dirty flag (byte, 1 if changed)
    if (newValue != *(float*)((uintptr_t)self + 0x14)) {
        *(uint8_t*)((uintptr_t)self + 0x28) = 1;
        *(float*)((uintptr_t)self + 0x14) = newValue;
    }
}