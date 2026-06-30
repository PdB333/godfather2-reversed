// FUNC_NAME: BytecodeInterpreter::executeOpcode
void BytecodeInterpreter::executeOpcode(void)
{
  int *bytecodePtr; // unaff_EDI - pointer to current bytecode stream
  int opcodeData; // iVar1 - base data for current opcode
  undefined4 *stackPtr; // puVar2 - pointer to stack
  undefined4 result; // uVar3 - result of function call
  
  // Get the current opcode's data block from the bytecode stream
  opcodeData = bytecodePtr[2]; // +0x08: opcode data block offset
  
  // Check if we need to grow the stack (stack size check)
  // +0x10: stack pointer, +0x20: current size, +0x24: allocated capacity
  if (*(uint *)(*(int *)(opcodeData + 0x10) + 0x20) <= *(uint *)(*(int *)(opcodeData + 0x10) + 0x24)) {
    // Stack needs to grow - call stack expansion function
    FUN_00627360(); // likely stackGrow()
  }
  
  // Get current stack top pointer
  stackPtr = *(undefined4 **)(opcodeData + 8); // +0x08: stack pointer
  
  // Write opcode type (4 = function call opcode)
  *stackPtr = 4;
  
  // Execute the function call and get result
  result = FUN_00638920(opcodeData, bytecodePtr + 3, unaff_retaddr); // likely executeFunctionCall()
  stackPtr[1] = result; // Store result on stack
  
  // Advance stack pointer by 8 bytes (opcode + result)
  *(int *)(opcodeData + 8) = *(int *)(opcodeData + 8) + 8;
  
  // Advance bytecode stream pointer by 3 words (opcode header + arguments)
  *bytecodePtr = (int)(bytecodePtr + 3);
  
  // Increment instruction counter
  bytecodePtr[1] = bytecodePtr[1] + 1;
  
  return;
}