// FUNC_NAME: AttributeSync::updateSynchronizedValue
void __thiscall AttributeSync::updateSynchronizedValue(void* this) {
    int* valueStruct;
    int delta;

    // +0xC4: sync mode (0 = current value, 1 = maximum value)
    if (*(int*)((char*)this + 0xC4) == 0) {
        // Get pointer to current value struct from provider handle at +0x38
        valueStruct = getCurrentValueFromProvider(*(void**)((char*)this + 0x38));
        if (valueStruct != nullptr) {
            // Compare current value (at offset +4) with previously sent value stored at +0xC8
            delta = *(int*)((char*)valueStruct + 4) - *(int*)((char*)this + 0xC8);
            if (delta != 0) {
                *(int*)((char*)this + 0xC8) = *(int*)((char*)valueStruct + 4); // Sync stored value
                // Notify delta change via handle at +0x40
                sendDeltaUpdate(*(void**)((char*)this + 0x40), this, delta);
            }
        }
    } else if (*(int*)((char*)this + 0xC4) == 1) {
        // Get pointer to maximum value struct from provider handle at +0x38
        valueStruct = getMaximumValueFromProvider(*(void**)((char*)this + 0x38));
        if (valueStruct != nullptr) {
            // Compare maximum value (at offset +8) with stored value
            delta = *(int*)((char*)valueStruct + 8) - *(int*)((char*)this + 0xC8);
            if (delta != 0) {
                *(int*)((char*)this + 0xC8) = *(int*)((char*)valueStruct + 8);
                sendDeltaUpdate(*(void**)((char*)this + 0x40), this, delta);
            }
        }
    }
}