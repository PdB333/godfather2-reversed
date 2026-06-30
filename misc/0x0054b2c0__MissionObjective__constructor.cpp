// FUNC_NAME: MissionObjective::constructor
void __thiscall MissionObjective::constructor(MissionObjective *this, int param2, int param3)
{
    int *globalPtr; // eax
    int *globalPtr2; // eax

    // Set vtable to base class (likely a generic objective base)
    this->vtable = (void *)&PTR_FUN_00e32a8c;

    // Initialize fields
    this->field_0x60 = 0;          // +0x60: some counter or flag
    this->field_0x50 = 0;          // +0x50: another counter
    this->field_0x20 = DAT_00e2b1a4; // +0x20: pointer from global
    this->field_0x24 = -1;         // +0x24: -1 (uninitialized)
    this->field_0x30 = -1;         // +0x30: -1 (uninitialized)
    this->field_0x04 = DAT_00e2b1a4; // +0x04: same global pointer

    this->field_0x88 = 0;          // +0x88: count of stored items (max 4)
    this->field_0x8c = param3;     // +0x8c: store third parameter

    // If there is room in the array at offset 0x78, add param2
    if (this->field_0x88 < 4) {
        this->array_0x78[this->field_0x88] = param2; // +0x78: array of 4 ints
        this->field_0x88++; // increment count
    }

    // Set field from global + 0x24 (likely a pointer to a manager)
    this->field_0x70 = *(int *)(DAT_01223480 + 0x24); // +0x70: pointer

    // Override vtable to derived class
    this->vtable = (void *)&PTR_LAB_00e39c58;

    // Self-reference (maybe for linked list or parent pointer)
    this->field_0x74 = this; // +0x74: pointer to self
}