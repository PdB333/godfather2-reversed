// FUNC_NAME: clearVector6
// Function at 0x0052fae0: Clears a 6-element float array to zero.
// Used for resetting vectors or small matrices (e.g., position + direction).
void clearVector6(float* vec6)
{
    vec6[0] = 0.0f;
    vec6[1] = 0.0f;
    vec6[2] = 0.0f;
    vec6[3] = 0.0f;
    vec6[4] = 0.0f;
    vec6[5] = 0.0f;
}