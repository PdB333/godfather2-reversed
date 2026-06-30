// FUNC_NAME: PacketAckField::modifyByte

// Function at 0x00496640: modifies a packed 32-bit field in an 8-byte structure.
// The structure is pointed by param_2, containing a main 4-byte field and an extra 4-byte field.
// The main field's low byte is a flag: 0 -> reset to default (0x00FFFF01), 1 or 3 -> allow editing byte at offset+1.
// param_3 is the new byte value, param_4 is the offset (0-based index beyond flag byte).
// param_1 is unused (likely leftover from fastcall).

void __fastcall PacketAckField::modifyByte(int /*unused*/ param_1, uint32_t* packetStruct, uint8_t newByte, int offset)
{
    uint32_t mainField = packetStruct[0];  // +0x00: main 4-byte field (flags + data)
    uint32_t extraField = packetStruct[1]; // +0x04: extra 4-byte field

    uint8_t flag = mainField & 0xFF; // low byte is flag

    if (flag == 0)
    {
        // Reset to default state: flag=1, high bytes 0xFF,0xFF,0x00
        mainField = 0x00FFFF01; // constant: low byte becomes 1
        extraField = 0;
    }
    else if (flag != 1 && flag != 3)
    {
        // Unknown flag value, no modification: restore original values and return
        packetStruct[0] = mainField;
        packetStruct[1] = extraField;
        return;
    }

    // Flag is 1 or 3: write newByte into byte at offset+1 of mainField
    // (offset is 0-based; offset+1 skips the flag byte)
    uint8_t* bytePtr = (uint8_t*)&mainField;
    bytePtr[offset + 1] = newByte;

    // Write back the modified fields
    packetStruct[0] = mainField;
    packetStruct[1] = extraField;
}