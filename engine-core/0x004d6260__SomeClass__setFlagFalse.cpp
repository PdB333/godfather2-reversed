// FUNC_NAME: SomeClass::setFlagFalse
// Function address: 0x004d6260
// Wrapper that forces the third parameter to 0 (false/disabled) when calling the underlying function at 0x004d6160.
void SomeClass::setFlagFalse(int param2, int param4) {
    // Call underlying function with third parameter forced to 0
    this->underlyingFunction(param2, 0, param4);
}