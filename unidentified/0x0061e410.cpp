// FUN_0061e410: SomeClass::updateCumulativeTotal
void __thiscall SomeClass::updateCumulativeTotal(void) {
    int count = *(int *)(this + 0x28);   // number of elements to process
    int *accumulator = (int *)(this + 0x38); // cumulative total

    for (int i = 0; i < count; i++) {
        int value = getPerElementValue(); // FUN_0061d720
        *accumulator += value;
    }
}