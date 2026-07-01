// FUNC_NAME: NetConnection::constructor
undefined4 * __thiscall NetConnection::constructor(undefined4 *this, int param_2)

{
  int iVar1;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  // Call virtual function at vtable+4 (likely some initialization)
  (**(code **)(**(int **)(param_2 + 8) + 4))();
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7c598;
  
  // Store connection parameters
  this[1] = param_2;          // +0x04: connection data pointer
  this[2] = 0;                // +0x08: some flag/counter
  
  // Call initialization function
  FUN_0060ffd0();
  
  // Initialize packet window state (32-slot window)
  uStack_50 = _DAT_00d5780c;  // Sequence number base
  uStack_4c = 0;              // Slot 0
  uStack_48 = 0;              // Slot 1
  uStack_44 = 0;              // Slot 2
  uStack_40 = 0;              // Slot 3
  uStack_3c = _DAT_00d5780c;  // Sequence number base (duplicate?)
  uStack_38 = 0;              // Slot 4
  uStack_34 = 0;              // Slot 5
  uStack_30 = 0;              // Slot 6
  uStack_2c = 0;              // Slot 7
  uStack_28 = _DAT_00d5780c;  // Sequence number base
  uStack_24 = 0;              // Slot 8
  uStack_20 = 0;              // Slot 9
  uStack_1c = 0;              // Slot 10
  uStack_18 = 0;              // Slot 11
  uStack_14 = _DAT_00d5780c;  // Sequence number base
  
  // Initialize packet window structure
  FUN_00610040(&uStack_50);
  
  // Check if connection is valid
  iVar1 = (**(code **)(**(int **)(param_2 + 8) + 4))();
  if (iVar1 != 0) {
    // Initialize additional connection state at offset +0x10
    FUN_00610160(this + 4);
  }
  
  return this;
}