// FUNC_NAME: RandomGenerator::update
// Function address: 0x005b1b60
// Role: Updates random generator state using a global counter and two state fields.
// The function combines state fields at offsets 0 and 8, increments a global counter,
// and calls a helper to produce a new random value into a local buffer.

void __fastcall RandomGenerator::update(int* state)
{
    int combined = state[2] + state[0]; // state[0] = +0x00, state[2] = +0x08 (unused result)
    int seed = g_randomCounter + 1;     // global counter incremented each call
    int output;                         // 4-byte buffer for generated value
    FUN_005aba20(&output, &seed);       // helper function (likely generates random number)
}