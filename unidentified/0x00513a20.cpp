// FUN_00513a20: BytecodeInterpreter::fetchAndExecute
// This function reads a 3-word opcode from a stream buffer (at this+0x18),
// computes a new stream pointer based on operands, and calls a virtual handler.

void BytecodeInterpreter::fetchAndExecute(OpcodeHandler* pHandler)
{
    // Read the current stream pointer from this object at offset +0x18
    uint32_t* streamPtr = *reinterpret_cast<uint32_t**>(reinterpret_cast<char*>(this) + 0x18);

    // Read opcode (first word)
    uint32_t opcode = streamPtr[0];
    // Advance stream pointer past first word
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x18) = streamPtr + 1;

    // Read operand1 (second word)
    int32_t operand1 = streamPtr[1];
    // Advance stream pointer past second word
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x18) = streamPtr + 2;

    // Read operand2 (third word)
    int32_t operand2 = streamPtr[2];
    // Advance stream pointer past third word
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x18) = streamPtr + 3;

    // Compute new stream pointer: align the base (streamPtr) + operand2 to the next multiple of operand2? Or just align to operand2?
    // Formula: (streamPtr + operand2 + 0x0B) & ~(operand2 - 1)
    uint32_t alignedAddress = (reinterpret_cast<uint32_t>(streamPtr) + operand2 + 0x0B) & ~(operand2 - 1U);

    // Set the new stream pointer: operand1 * 8 + alignedAddress
    *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0x18) = operand1 * 8 + alignedAddress;

    // Build a 64-bit value from operand1 (high) and the lower part (conditional mask)
    // -(operand1 != 0) yields 0xFFFFFFFF if operand1 != 0, else 0. The low part is that masked with alignedAddress.
    uint32_t lowPart = -(uint32_t)(operand1 != 0) & alignedAddress;
    uint64_t combinedValue = (static_cast<uint64_t>(operand1) << 32) | lowPart;

    // Call the handler's first virtual method (vtable entry at offset 0)
    // The handler object is passed as the first "this" argument to the function.
    reinterpret_cast<void (__thiscall*)(void*, uint32_t, uint64_t, int32_t)>(
        *reinterpret_cast<void**>(*reinterpret_cast<void**>(pHandler))
    )(pHandler, opcode, combinedValue, operand2);

    return;
}