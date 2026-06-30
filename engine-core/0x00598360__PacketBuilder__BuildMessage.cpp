// FUNC_NAME: PacketBuilder::BuildMessage
int PacketBuilder::BuildMessage(void* pInputBuffer, const char* pString) {
    // Global stream writer used to serialize the packet
    // *DAT_01205590 is assumed to be a pointer to a StreamWriter object
    StreamWriter* writer = *(StreamWriter**)0x01205590;

    int buffer; // in_EAX from first allocation call

    // Allocate initial buffer? First write call returns a pointer in EAX
    writer->Write(&buffer, 0x54, 0x600); // Write header: size 0x54? Actually first call writes something

    // First call: write 2 bytes? The stack setup is confusing
    writer->Write(buffer + 2, 2); // Write 2-byte field at offset 2

    // Write 4-byte field
    writer->Write(buffer + 4, 4);

    // Check input buffer length (param_2)
    int inputLen = writer->GetSize(pInputBuffer);
    if (inputLen > 0x3F) {
        writer->Error(); // Offset 4 might be an error handler
    }

    // Get size again and increment
    inputLen = writer->GetSize(pInputBuffer);
    inputLen++;

    // Write field at offset 8 based on input buffer
    writer->Write(buffer + 8, pInputBuffer, inputLen);

    // Write field at offset 0x48 with 0 bytes? Actually writes null terminator
    writer->Write(buffer + 0x48, nullptr, 0); // Or some default

    // Write sequence or type at offset 0x54
    uint16_t field1 = 0x603;
    writer->Write(buffer + 0x54, &field1, 2);

    // Write another uint16 at offset 0x56
    uint16_t field2 = 2; // from uVar4
    writer->Write(buffer + 0x56, &field2, 2);

    // Write uint32 at offset 0x58
    int32_t field3 = buffer + 4; // from iStack_48
    writer->Write(buffer + 0x58, &field3, 4);

    // Write pointer at offset 0x5C
    void* field4 = nullptr; // from ppuStack_64
    writer->Write(buffer + 0x5C, &field4, 4);

    // Check string length (param_3)
    int strLen = writer->GetSize(pString);
    if (strLen > 0x1F) {
        writer->Error();
    }

    // Write string with null terminator at offset 0x60
    int strLenWithNull = writer->GetSize(pString) + 1;
    writer->Write(buffer + 0x60, pString, strLenWithNull);

    // Write final field at offset 0x80: 2 bytes of value 2, size 0xC? Actually writes uVar4 (2) with size 0xC
    writer->Write(buffer + 0x80, &uVar4, 0xC);

    return 0x8C; // Total packet size
}