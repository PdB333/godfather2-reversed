// FUNC_NAME: max (global math utility function) [Address: 0x00556270]
// Returns the greater of two floats.
float max(float a, float b) {
    if (b < a) {
        return a;
    }
    return b;
}