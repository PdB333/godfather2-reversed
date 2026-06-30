// FUNC_NAME: setNewValue
void __thiscall setNewValue(void *this, uint newValue)
{
    // Store the new value at offset +0xC4 (e.g., currentValue)
    *(uint *)((uint8_t *)this + 0xC4) = newValue;
    // If newValue is smaller than the stored minimum at +0xC0, update the minimum
    if (newValue < *(uint *)((uint8_t *)this + 0xC0)) {
        *(uint *)((uint8_t *)this + 0xC0) = newValue;
    }
}