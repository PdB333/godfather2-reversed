// FUNC_NAME: QuadInt::processIfNonZero
// Function at 0x008495c0: Checks if any of the four integer members is non-zero; if so, calls an external processing function with them.
// This appears to be a method of a class containing four contiguous ints (e.g., a 4D vector, color, or rectangle).
void QuadInt::processIfNonZero(void) {
    // Check if any of the four components is non-zero
    if (m_value0 != 0 || m_value1 != 0 || m_value2 != 0 || m_value3 != 0) {
        // Call external handler with the four values
        FUN_0088db10(m_value0, m_value1, m_value2, m_value3);
    }
}