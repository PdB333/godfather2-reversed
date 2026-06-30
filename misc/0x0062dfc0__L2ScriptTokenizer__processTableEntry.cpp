// FUNC_NAME: L2ScriptTokenizer::processTableEntry
undefined4 L2ScriptTokenizer::processTableEntry(int this) // 0x0062dfc0
{
  int *tableEnd; // +0xc
  int *tablePos; // +0x8
  int *elemPtr;
  int *extraout_ECX;
  int *extraout_ECX_00;
  int *extraout_ECX_01;

  tableEnd = *(int **)(this + 0xc);  // tableBufferEnd
  tablePos = *(int **)(this + 8);    // currentTablePosition
  if (((tablePos <= tableEnd) || (tableEnd == (int *)0x0)) || (*tableEnd != 5)) {
    // 5 = MKEY_START_DICT? Ensure we're at a dictionary start marker
    FUN_00627ac0(PTR_s_table_00e2a8b0);  // likely parseError("table")
    tableEnd = extraout_ECX;
  }
  elemPtr = tableEnd + 2;  // skip dict marker + key index
  if (((tablePos <= elemPtr) || (elemPtr == (int *)0x0)) || (*elemPtr == -1)) {
    // Expecting a key (or value identifier)
    FUN_00627a20(this, 2, "value expected");  // parse error at token 2
    tableEnd = extraout_ECX_00;
  }
  elemPtr = tableEnd + 4;  // skip value1, value2
  if (((tablePos <= elemPtr) || (elemPtr == (int *)0x0)) || (*elemPtr == -1)) {
    FUN_00627a20(this, 3, "value expected");
    tableEnd = extraout_ECX_01;
  }
  // Fetch the target value from the table (e.g., getString by tableEnd[1])
  int *target = (int *)FUN_00638020(this, tableEnd[1]);  // likely getValueByIndex
  *target = tablePos[-2];   // copy two words from table stream
  target[1] = tablePos[-1];
  *(int *)(this + 8) = *(int *)(this + 8) + -0x10;  // pop 16 bytes from table stack
  return 1;
}