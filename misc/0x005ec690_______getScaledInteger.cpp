// FUNC_NAME: ???::getScaledInteger
void __thiscall SomeClass::getScaledInteger(int unusedParam, int* outValue, int param4, int param5)
{
    float value = 0.0f;
    // Calls internal function to compute a float based on this, param4, param5
    this->computeFloat(&value, param4, param5);
    // Scale by global conversion factor (e.g., game units per second) and round to int
    *outValue = (int)(value * _DAT_00e44670);
}