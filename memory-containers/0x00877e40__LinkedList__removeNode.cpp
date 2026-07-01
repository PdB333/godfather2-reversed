// FUNC_NAME: LinkedList::removeNode
void __thiscall LinkedList::removeNode(int param_1, int param_2)
{
  undefined4 local_20;
  undefined ***local_1c;
  undefined1 local_18;
  undefined **local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  undefined4 local_4;
  
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  // If the list (param_1) is valid and has a head node (+0x48)
  if ((param_1 != 0) && (param_1 + 0x48 != 0)) {
    // Save the next pointer of the head node (+0x4c)
    local_4 = *(undefined4 *)(param_1 + 0x4c);
    // Set the head node's next to point to our local sentinel
    *(int **)(param_1 + 0x4c) = &local_8;
    // Link the sentinel back to the head node
    local_8 = param_1 + 0x48;
  }
  // If param_2 is null, keep it null; otherwise advance to its node data (+0x48)
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + 0x48;
  }
  // If the second node is valid, do similar sentinel swap
  if ((param_2 != 0) && (local_c = 0, local_10 = param_2, param_2 != 0)) {
    local_c = *(undefined4 *)(param_2 + 4);
    *(int **)(param_2 + 4) = &local_10;
  }
  // Setup a local vtable pointer for some operation
  local_14 = &PTR_FUN_00d7666c;
  local_1c = &local_14;
  local_20 = DAT_0112e13c;
  local_18 = 0;
  // Call some initialization/cleanup function
  FUN_00408a00(&local_20,0);
  // Clean up the sentinel nodes
  if (local_8 != 0) {
    FUN_004daf90(&local_8);
  }
  if (local_10 != 0) {
    FUN_004daf90(&local_10);
  }
  return;
}