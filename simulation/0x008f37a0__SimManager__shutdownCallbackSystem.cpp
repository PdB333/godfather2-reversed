// FUNC_NAME: SimManager::shutdownCallbackSystem
void __thiscall SimManager::shutdownCallbackSystem(int thisPtr)
{
  int callbackCount;
  code *callbackFunc1;
  code *callbackFunc2;
  code *callbackFunc3;
  int callbackArg1;
  code *callbackFunc0;
  int callbackArg;
  byte filler;
  int hashKey;

  // Clear flag at offset +0x10 (bit 0x2000)
  *(uint *)(thisPtr + 0x10) &= 0xFFFFDFFF;

  hashKey = 0;
  // Look up a hash (0xE99303E3) – likely a string key for a global system
  FUN_006039d0(0xE99303E3, &hashKey, &filler);
  FUN_004d3bc0(hashKey); // free or release resource associated with the hash

  // Initialize local callback structure
  callbackFunc0 = 0;
  callbackArg1 = 0;
  callbackFunc1 = 0;
  callbackFunc2 = 0;
  callbackFunc3 = 0;

  // Build the callback triple from current state (likely iterates through listeners)
  FUN_008f22f0(&callbackFunc0);

  // Lock or enter critical section on global mutex at 0x00d57620
  FUN_004d4300(&DAT_00d57620);

  // If no callback, use a default static function pointer
  if (callbackFunc0 == 0) {
    callbackFunc0 = (code *)&DAT_0120546e; // default sentinel handler
  }
  FUN_004dba80(callbackFunc0, callbackArg1); // Register or invoke the callback

  // Similarly handle secondary callback (callbackFunc1 corresponds to local_20)
  if (callbackFunc1 == 0) {
    callbackFunc1 = (code *)&DAT_00e2df14; // default sentinel
  }
  // Call virtual method at vtable+0x34 on object pointed by thisPtr+0x2098
  // This vtable entry is likely an unregister/set listener method
  (**(code **)(**(int **)(thisPtr + 0x2098) + 0x34))(callbackFunc1, 0, &hashKey);

  // Fire any existing callbacks if their arguments are non‑zero
  if (callbackArg1 != 0) {
    (*callbackFunc1)(callbackArg1); // local_20 used as function
  }
  if (unaff_ESI != 0) {
    (*callbackFunc0)(unaff_ESI); // unaff_ESI likely stored from ESI (extra implicit param)
  }
  if (callbackArg != 0) {
    (*callbackFunc3)(callbackArg); // local_10 used as function
  }
}