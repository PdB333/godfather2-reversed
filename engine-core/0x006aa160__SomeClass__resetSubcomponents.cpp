// FUNC_NAME: SomeClass::resetSubcomponents
void resetSubcomponents()
{
    // +0x68: some flag (active/initialized) - set to 0
    *(byte *)(this + 0x68) = 0;

    // Clear and reinitialize subcomponent at +0x44
    subobjectClear(this + 0x44);
    subobjectInit(this + 0x44);

    // Clear and reinitialize subcomponent at +0x4C
    subobjectClear(this + 0x4C);
    subobjectInit(this + 0x4C);

    // If subcomponent at +0x54 is present (flag at +0x28 non-zero), reset it
    if (*(int *)(this + 0x28) != 0) {
        subobjectClear(this + 0x54);
        subobjectInit(this + 0x54);
    }

    // If subcomponent at +0x5C is present (flag at +0x38 non-zero), reset it
    if (*(int *)(this + 0x38) != 0) {
        subobjectClear(this + 0x5C);
        subobjectInit(this + 0x5C);
    }
}