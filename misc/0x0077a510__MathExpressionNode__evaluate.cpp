// FUNC_NAME: MathExpressionNode::evaluate
float __thiscall MathExpressionNode::evaluate(int thisPtr, undefined4 param_2)
{
  float fVar1;
  float unaff_ESI;
  float fVar3;
  
  // Evaluate left operand (always present at +0x8)
  fVar1 = (float)(**(code **)(**(int **)(thisPtr + 8) + 4))(param_2);
  fVar3 = 0.0;
  
  // Evaluate right operand (optional, at +0xC)
  if (*(int *)(thisPtr + 0xc) != 0) {
    fVar3 = (float)(**(code **)(**(int **)(thisPtr + 0xc) + 4))(param_2);
  }
  
  // Apply operation based on type at +0x4
  // 0 = ADD, 1 = SUBTRACT, 2 = MULTIPLY, 3 = DIVIDE
  switch(*(undefined4 *)(thisPtr + 4)) {
  case 0:
    return (float)(fVar3 + fVar1);
  case 1:
    return (float)(fVar1 - fVar3);
  case 2:
    return (float)(fVar3 * fVar1);
  case 3:
    unaff_ESI = fVar1 / fVar3;
  }
  return (float)unaff_ESI;
}