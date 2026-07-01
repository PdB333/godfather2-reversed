// FUNC_NAME: OperatorSymbolNode::evaluate
float __thiscall OperatorSymbolNode::evaluate(int thisPtr, uint entityId)
{
  float leftValue;
  float opResult;
  float rightValue;
  
  // Evaluate the left operand
  leftValue = (**(code **)(**(int **)(thisPtr + 8) + 4))(entityId);
  
  // Evaluate the right operand if it exists
  opResult = 0.0;
  if (*(int *)(thisPtr + 0xc) != 0) {
    rightValue = (**(code **)(**(int **)(thisPtr + 0xc) + 4))(entityId);
    opResult = rightValue;
  }
  
  // Apply the operator based on the opcode stored at +0x4
  // Opcodes: 0=Add, 1=Subtract, 2=Multiply, 3=Divide
  switch(*(int *)(thisPtr + 4)) {
    case 0: // OP_ADD
      return opResult + leftValue;
    case 1: // OP_SUBTRACT
      return leftValue - opResult;
    case 2: // OP_MULTIPLY
      return opResult * leftValue;
    case 3: // OP_DIVIDE
      return leftValue / opResult; // Note: may crash if rightValue is 0
  }
  
  return 0.0; // Unreachable if switch is exhaustive
}