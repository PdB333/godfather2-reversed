// FUNC_NAME: BytecodeInterpreter::decodeInstruction
// Address: 0x00579a50
// Decodes the current bytecode instruction and advances the instruction pointer.
// The instruction pointer is stored in the object pointed to by this (register EDI).
// Bytecode format: first byte = [opcode (low 4 bits) | immediate_low_nibble (high 4 bits)],
//                   second byte = immediate_high_byte (for non-opcode-5 instructions).
// For opcode 5, a 16-bit length is read at offset 2.

void BytecodeInterpreter::decodeInstruction(void)
{
    // Context pointer (this) is in EDI for this function.
    // The first member of this context is a pointer to the current instruction byte.
    byte** ppInstr = (byte**)this;
    byte* instrPtr = *ppInstr;

    byte firstByte = instrPtr[0];
    uint opcode = firstByte & 0x0F;

    int instructionLength;
    if (opcode == 5)
    {
        // Opcode 5: instruction length stored as 16-bit integer at offset 2
        instructionLength = *(int16*)(instrPtr + 2);
    }
    else
    {
        // Build 12-bit immediate from the two bytes:
        // immediate = (second_byte << 4) | (first_byte >> 4)
        uint immediate = (static_cast<uint>(instrPtr[1]) << 4) | (firstByte >> 4);

        // Static tables derived from data at 0x00e2c758 (scale) and 0x00e2c720 (base)
        static const int scaleTable[16] = {
            /* values from 0x00e2c758, indexed by opcode */
        };
        static const int baseTable[16] = {
            /* values from 0x00e2c720, indexed by opcode */
        };

        instructionLength = scaleTable[opcode] * immediate + baseTable[opcode];
    }

    // Advance the instruction pointer by the computed length
    *ppInstr = instrPtr + instructionLength;
}