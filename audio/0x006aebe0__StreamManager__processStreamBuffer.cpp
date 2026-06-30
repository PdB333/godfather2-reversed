// FUNC_NAME: StreamManager::processStreamBuffer
void __thiscall StreamManager::processStreamBuffer(int thisPtr, int *param_2)
{
  char cVar1;
  int unaff_ESI;
  int *local_1c;
  int local_18;
  undefined4 local_14;
  undefined1 *local_10;
  undefined1 uStack_c;
  
  // Increment stream buffer position counter at +0x1d4
  *(int *)(thisPtr + 0x1d4) = *(int *)(thisPtr + 0x1d4) + 1;
  
  // Check if position exceeds buffer size at +0x1d8
  if (*(uint *)(thisPtr + 0x1d8) <= *(uint *)(thisPtr + 0x1d4)) {
    // If there's a pending buffer at +0x1dc, process it
    if (*(int *)(thisPtr + 0x1dc) != 0) {
      local_14 = 0;
      local_10 = (undefined1 *)((uint)local_10 & 0xffffff00);
      local_18 = *(int *)(thisPtr + 0x1dc);
      FUN_00408a00(&local_18, 0);  // Likely memcpy or buffer copy
      FUN_00408310(thisPtr + 0x1dc);  // Likely free or release buffer
    }
  }
  
  local_1c = (int *)0x0;
  // Call virtual function at vtable+0x10 (likely getNextStreamData)
  cVar1 = (**(code **)(*param_2 + 0x10))(0x6a8acf44, &local_1c);
  if ((cVar1 != '\0') && (unaff_ESI != 0)) {
    local_1c = (int *)0x0;
    local_18 = 0;
    if (param_2 + 0x12 != (int *)0x0) {
      local_18 = param_2[0x13];
      param_2[0x13] = (int)&local_1c;
      local_1c = param_2 + 0x12;
    }
    local_10 = &stack0xffffffe0;
    local_14 = DAT_0112ade8;  // Global stream data reference
    uStack_c = 0;
    FUN_00408a00(&local_14, 0);  // Likely memcpy or buffer copy
    if (local_1c != (int *)0x0) {
      FUN_004daf90(&local_1c);  // Likely free or release memory
    }
  }
  return;
}