// FUNC_NAME: EntryData::init
// Function address: 0x0079b3d0
// Role: Initializes an EntryData structure with default values and copies data from a parameter array.
// Structure layout:
//   +0x00: byte active (set to 1)
//   +0x04: int32_t type (set to 7)
//   +0x08: uint64_t value0 (copied from params[0])
//   +0x10: uint64_t value1 (copied from params[1])
//   +0x18: int32_t value2 (copied from low 32 bits of params[2])

void __thiscall EntryData::init(EntryData* this, const uint64_t* params) {
    this->active = 1;
    this->type = 7;
    this->value0 = params[0];
    this->value1 = params[1];
    this->value2 = (int32_t)params[2];
}