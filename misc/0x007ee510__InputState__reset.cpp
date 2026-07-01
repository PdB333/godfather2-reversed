// FUNC_NAME: InputState::reset
// Function address: 0x007ee510
// Role: Initializes all fields of an InputState structure to zero (32 bytes).
// Called during input device initialization/reset.
// The structure likely contains analog axes, button states, etc.
// Fields (offsets in bytes):
//   0x00: int (some state flag or index)
//   0x04: int
//   0x08: int
//   0x0C: int
//   0x10: int
//   0x14: double (float pair? or 64-bit timer)
//   0x1C: int // actually offset 0x1C (since +7 *4 = 28 = 0x1C)
// Total size 0x20 bytes.
void __thiscall InputState::reset(void *this_)
{
    int *ints = (int *)this_;
    ints[0] = 0;
    ints[1] = 0;
    ints[2] = 0;
    ints[3] = 0;
    ints[4] = 0;
    *(double *)(ints + 5) = 0.0; // clear 8 bytes at offset 0x14
    ints[7] = 0; // offset 0x1C
}