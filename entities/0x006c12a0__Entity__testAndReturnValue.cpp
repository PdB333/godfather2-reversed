// FUNC_NAME: Entity::testAndReturnValue
uint Entity::testAndReturnValue(uint value) {
    int result = 0;

    // Call virtual function at vtable+0x10: tests validity of 'value' and optionally stores auxiliary info in 'result' (unused here)
    bool isValid = ((bool (*)(uint, int*))(*((uint*)this + 0x10)))(value, &result);

    // Return the original value if valid, otherwise 0.
    return isValid ? value : 0;
}