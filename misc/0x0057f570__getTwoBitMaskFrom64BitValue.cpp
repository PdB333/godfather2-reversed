// FUNC_NAME: getTwoBitMaskFrom64BitValue
uint getTwoBitMaskFrom64BitValue(void)
{
    // Reads a global 64-bit value (likely a high-frequency counter or random state),
    // performs a logical right shift (amount unknown, possibly from a constant or
    // another global), and returns the lowest 2 bits of the result.
    uint64_t shifted = __aullshr(); // __aullshr intrinsic: shifts 64-bit value right by an implicit count
    return (uint)(shifted & 3);
}