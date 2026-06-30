// FUNC_NAME: SomeState::Init (or free function InitSomeState)
// Address: 0x005e3280
// Role: Initializes a small state structure with default values (flags=1, others=0)

struct SomeState {
    int flags;    // +0x00: first field, set to 1
    int field_04; // +0x04: second field, set to 0
    int field_08; // +0x08: third field, set to 0
    char byte_0C; // +0x0C: byte field, set to 0
};

void __fastcall InitSomeState(SomeState* state) {
    state->flags = 1;
    state->field_04 = 0;
    state->field_08 = 0;
    state->byte_0C = 0;
}