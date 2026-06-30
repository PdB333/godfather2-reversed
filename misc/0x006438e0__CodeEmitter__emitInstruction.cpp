// FUNC_NAME: CodeEmitter::emitInstruction
// Function at 0x006438e0: Emit a two-word instruction (opcode + operand) into the code buffer.
// 'this' pointer (ESI) points to a CodeEmitter object with embedded code buffer pointer.
// Offsets relative to 'this':
//  +0x00: m_buffer (pointer to CodeBuffer struct)
//  +0x10: m_someParam (used in reallocation, possibly heap ID)
//  +0x18: m_counter (index for next instruction)
//  +0x20: m_lastOpcodeFlag (set to -1 after emit)
//
// CodeBuffer struct (pointed by m_buffer):
//  +0x0c: m_codeArray (int*)
//  +0x2c: m_codeCapacity (int)
//  +0x14: m_operandArray (int*)
//  +0x30: m_operandCapacity (int)

void CodeEmitter::emitInstruction(int opcode, int operand)
{
    CodeBuffer* buffer = this->m_buffer;                // deref this to get code buffer
    preEmitCheck();                                      // FUN_006426a0 – perhaps validate state
    this->m_lastOpcodeFlag = -1;                         // set flag to invalid

    // Ensure code array has space for one more int
    if (buffer->m_codeCapacity < this->m_counter + 1)
    {
        int newCodeArray = growArray(this->m_someParam,
                                     buffer->m_codeArray,
                                     &buffer->m_codeCapacity,
                                     4,
                                     "code size overflow");
        buffer->m_codeArray = newCodeArray;
    }
    buffer->m_codeArray[this->m_counter] = opcode;

    // Ensure operand array has space for one more int
    if (buffer->m_operandCapacity < this->m_counter + 1)
    {
        int newOperandArray = growArray(this->m_someParam,
                                        buffer->m_operandArray,
                                        &buffer->m_operandCapacity,
                                        4,
                                        "code size overflow");
        buffer->m_operandArray = newOperandArray;
    }
    buffer->m_operandArray[this->m_counter] = operand;

    this->m_counter++;                                   // advance instruction index
}