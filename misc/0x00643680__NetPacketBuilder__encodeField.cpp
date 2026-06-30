// FUNC_NAME: NetPacketBuilder::encodeField
void __fastcall NetPacketBuilder::encodeField(int this, uint value1, int typeOrSize, uint value2)
{
    uint uVar2;
    uint encodedValue;
    undefined4 result;

    // If typeOrSize > 4, it indicates a larger field (>4 bytes?)
    if (4 < typeOrSize) {
        // For typeOrSize between 5 and 9, swap the two values
        if (typeOrSize < 10) {
            uVar2 = value1;
            value1 = value2;
            value2 = uVar2;
        }
        // Look up encoding function from a table at base+0xC+typeOrSize*4
        // The table base is unknown; Ghidra showed a string artifact.
        // We assume there is a table of function pointers or constants.
        encodedValue = FUN_006424f0(*(undefined4 *)(tableBase + typeOrSize * 4 + 0xC),
                                   value2, value1);
        // Write result as type 9 (likely a compact representation)
        *unaff_EDI = 9;
        unaff_EDI[1] = encodedValue;
        return;
    }

    // For typeOrSize <= 4, encode as type 10
    // Combine value1, value2 and typeOrSize into a single encoded value
    encodedValue = (value1 << 9 | value2) << 6 | (typeOrSize + 0xC);
    // Fetch a second parameter from the object structure at offset +0xC->+8
    result = FUN_006438e0(encodedValue, *(undefined4 *)(*(int *)(this + 0xC) + 8));
    *unaff_EDI = 10;
    unaff_EDI[1] = result;
    return;
}