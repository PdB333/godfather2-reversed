// FUNC_NAME: ConfigData::writeDefaults
// Function at 0x597cf0: Writes fixed configuration values (2, 0x207, 2) into a struct and returns its size (12).
// Uses a global serializer object (DAT_01205590) to write fields at offsets +2, +4, +8.
unsigned int __thiscall ConfigData::writeDefaults(ConfigData* this) {
    // Global serializer with vtable at 0x01205590, method at +0x10 = writeBytes
    int serializer = *(int*)0x01205590;

    // Local buffer for writing
    int local8 = 0x207;          // +0x4 field value
    int local4 = 0xc;            // size return value
    int stack10 = 2;             // +0x2 field value
    int stackArray[2] = { 2, 0 }; // first element used for +0x8 field, second unused

    // First write: set +0x2 to 2
    (*(void (__thiscall**)(int, int*, int))(*(int*)serializer + 0x10))(serializer, this + 2, &stack10, 4);
    // Second write: set +0x4 to 0x207
    (*(void (__thiscall**)(int, int*, int*, int))(*(int*)serializer + 0x10))(serializer, this + 4, &local8, 4);
    // Third write: set +0x8 to 2
    (*(void (__thiscall**)(int, int*, int*, int))(*(int*)serializer + 0x10))(serializer, this + 8, stackArray, 4);

    return 0xc; // size of this config struct
}