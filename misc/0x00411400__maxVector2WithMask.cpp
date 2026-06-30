// FUNC_NAME: maxVector2WithMask
// Function at 0x00411400: Element-wise masked maximum for two 2-element uint vectors.
// Compares low bits (masked by a global) and updates the first vector if the second is larger.
// Likely used for priority or bounding-box operations in EA EARS engine.
void maxVector2WithMask(uint* destination, uint* source)
{
    uint mask = DAT_00e44680; // global mask (e.g., for component selection)
    // Compare first component
    if ((destination[0] & mask) < (source[0] & mask)) {
        destination[0] = source[0];
    }
    // Compare second component
    if ((destination[1] & mask) < (source[1] & mask)) {
        destination[1] = source[1];
    }
}