// FUNC_NAME: NetworkUtil::packTripleByte
uint64 NetworkUtil::packTripleByte(byte low5Bits, uint32 param2, uint32 param3, byte highByte)
{
    // param2 is unused (likely a placeholder or compiler artifact)
    // param3 converted to a byte via helper function (likely an ID lookup or flags extraction)
    byte middleByte = sub_499b80(param3); // FUN_00499b80

    // Pack into 64-bit: highByte occupies bits 21-28, middleByte bits 13-20, low5Bits bits 0-4
    // The original code used CONCAT16/CONCAT15; we reconstruct the packing logic
    uint32 lowPart = (static_cast<uint32>(middleByte) << 5) | (low5Bits & 0x1F);
    uint64 result = (static_cast<uint64>(highByte) << 32) | lowPart; // Position shift adjusted for clarity
    return result;
}