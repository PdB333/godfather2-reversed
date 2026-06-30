// FUNC_NAME: BinaryStreamReader::validateHeader
// Address: 0x006421b0
// Role: Reads and validates the header of a serialized VM bytecode stream, including version, type sizes, and a magic number.

void BinaryStreamReader::validateHeader()
{
    // Read initial header? (unknown purpose, possibly a length or flags)
    readShort();

    // Read version byte (major: high nibble, minor: low nibble)
    byte versionByte = readByte();
    byte major = versionByte >> 4;
    byte minor = versionByte & 0x0f;

    // Check if version is too new
    if (major > 0x05 || (major == 0x05 && minor > 0x00))
    {
        // Expected at most 5.0
        errorPrint(*m_stream, "%s too new: read version %d.%d; expected at most %d.%d",
                   m_name, major, minor, 5, 0);
    }
    // Check if version is too old (major < 5, or major==5 and minor<0? Actually they check lower bound: major < 5)
    // Note: The decompiled logic uses signed comparisons on the byte after sign extension.
    // Reconstructing: they check if (major < 5) OR (major == 5 and minor < 0) but minor is 0-15 so minor < 0 impossible.
    // Actually the decompile shows: if (cVar4 != cVar3) where cVar3 = (int)(uVar2 - 0x50) < 0; and cVar4 = SBORROW4(uVar2,0x50); 
    // That is checking if uVar2 (which is versionByte after mask) is LESS than 0x50 (80 decimal). Since versionByte is 0-255, 
    // 0x50 = 80, major = versionByte>>4, so major >=5 means versionByte >= 80? Actually 5<<4 = 80, so versionByte < 80 means major < 5.
    if (versionByte < 0x50)
    {
        // Expected at least 5.0
        // The error message uses (uVar2 + ((int)uVar2 >> 0x1f & 0xfU)) >> 4 for major and uVar1 for minor, but that's redundant.
        // We'll simplify to major and minor.
        errorPrint(*m_stream, "%s too old: read version %d.%d; expected at least %d.%d",
                   m_name, major, minor, 5, 0);
    }

    // Read byte for "bool" version (expect 1)
    byte boolVersion = readByte();
    if (boolVersion != 1)
    {
        // bool version mismatch (unlikely)
    }

    // Read and validate sizeof(bool) from stream
    byte boolSize = readByte();
    if (boolSize != 4) // Expect sizeof(bool) == 4 (common on some platforms)
    {
        errorPrint(*m_stream, "virtual machine mismatch in %s: size of %s is %d but read %d",
                   m_name, "bool", 4, boolSize);
    }

    // Read and validate sizeof(size_t)
    byte sizeTSize = readByte();
    if (sizeTSize != 4)
    {
        errorPrint(*m_stream, "virtual machine mismatch in %s: size of %s is %d but read %d",
                   m_name, "size_t", 4, sizeTSize);
    }

    // Read and validate sizeof(Instruction)
    byte instructionSize = readByte();
    if (instructionSize != 4)
    {
        errorPrint(*m_stream, "virtual machine mismatch in %s: size of %s is %d but read %d",
                   m_name, "Instruction", 4, instructionSize);
    }

    // Read and validate sizeof(some other type, e.g., Opcode or Register) expected 6
    byte unknownSize6 = readByte();
    if (unknownSize6 != 6)
    {
        errorPrint(*m_stream, "virtual machine mismatch in %s: size of %s is %d but read %d",
                   m_name, &DAT_00e429d8, 6, unknownSize6); // DAT_00e429d8 possibly a string like "Opcode"
    }

    // Read and validate another type expected 8
    byte unknownSize8 = readByte();
    if (unknownSize8 != 8)
    {
        errorPrint(*m_stream, "virtual machine mismatch in %s: size of %s is %d but read %d",
                   m_name, &DAT_00e429dc, 8, unknownSize8);
    }

    // Read and validate another type expected 9
    byte unknownSize9a = readByte();
    if (unknownSize9a != 9)
    {
        errorPrint(*m_stream, "virtual machine mismatch in %s: size of %s is %d but read %d",
                   m_name, &DAT_00e429e0, 9, unknownSize9a);
    }

    // Another type expected 9
    byte unknownSize9b = readByte();
    if (unknownSize9b != 9)
    {
        errorPrint(*m_stream, "virtual machine mismatch in %s: size of %s is %d but read %d",
                   m_name, &DAT_00e41eb4, 9, unknownSize9b);
    }

    // Read and validate sizeof(number) expected 4
    byte numberSize = readByte();
    if (numberSize != 4)
    {
        errorPrint(*m_stream, "virtual machine mismatch in %s: size of %s is %d but read %d",
                   m_name, "number", 4, numberSize);
    }

    // Read a magic float value
    float magicFloat = readFloat();
    // Expected integer representation: 0x1df5e76 (31317406 in decimal)
    if (*reinterpret_cast<int*>(&magicFloat) != 0x1df5e76)
    {
        errorPrint(*m_stream, "unknown number format in %s", m_name);
    }
}