// FUNC_NAME: EARSObject::getCachedValue
int __fastcall EARSObject::getCachedValue(int this) {
    // Call update function (likely processes pending changes)
    updateState();

    // Check if dirty flag at offset +0x270 is set
    if (*(int*)(this + 0x270) != 0) {
        // Recalculate current value via external function
        return recalculateValue();
    }

    // Return cached value at offset +0x274
    return *(int*)(this + 0x274);
}