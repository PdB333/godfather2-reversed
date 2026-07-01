// FUNC_NAME: LinkedListNode::insertAfter
void __thiscall LinkedListNode::insertAfter(int param_1, int param_2)
{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x38); // +0x38: next pointer
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + 0x48; // +0x48: prev pointer offset in node
  }
  if (*piVar1 != param_2) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1); // likely removeFromList or unlink
    }
    *piVar1 = param_2;
    if (param_2 != 0) {
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_2 + 4); // +0x3c: prev pointer
      *(int **)(param_2 + 4) = piVar1; // update previous node's next
    }
  }
  return;
}