// FUNC_NAME: StateData::assign
// Function at 0x0054bfb0: copies 17 fields (indices 0-4 and 8-19) from source to destination, skipping indices 5-7.
// Used by multiple callers to copy state data between objects (likely a struct with a 3x4 matrix at +0x20 and 5 extra fields at +0x00).
void __thiscall StateData::assign(StateData* this, const StateData* source)
{
    this->field0 = source->field0;
    this->field1 = source->field1;
    this->field2 = source->field2;
    this->field3 = source->field3;
    this->field4 = source->field4;
    this->field8 = source->field8;
    this->field9 = source->field9;
    this->field10 = source->field10;
    this->field11 = source->field11;
    this->field12 = source->field12;
    this->field13 = source->field13;
    this->field14 = source->field14;
    this->field15 = source->field15;
    this->field16 = source->field16;
    this->field17 = source->field17;
    this->field18 = source->field18;
    this->field19 = source->field19;
    // Note: indices 5,6,7 are not copied (possibly reserved or not part of the data block)
}