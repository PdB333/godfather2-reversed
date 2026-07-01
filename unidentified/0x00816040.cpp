// FUN_00816040: Component::processFlagUpdate

void __thiscall Component::processFlagUpdate(int param_2, int param_3, int param_4) {
    // Begin update on sub-component at +0x10 (likely a state machine context or lock)
    beginUpdate(reinterpret_cast<void*>(this + 0x10));

    // Evaluate condition and get mask byte
    byte mask = evaluateCondition(param_2, param_3, param_4);

    // Apply mask to flag byte at +0xc
    *reinterpret_cast<byte*>(this + 0xc) &= mask;

    // End update
    endUpdate();
}