// FUNC_NAME: EARSPlasmaTransaction::createTransaction
void __thiscall EARSPlasmaTransaction::createTransaction(int this, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5)
{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 local_10;
  undefined4 local_c;
  undefined8 local_18;
  long long local_20;
  undefined4 uStack_24;
  
  // Check if plasma interface exists (+0x8044) and is enabled (+0x8048)
  if ((*(int *)(this + 0x8044) != 0) && (*(char *)(this + 0x8048) != '\0')) {
    // Acquire plasma system lock
    FUN_00adc560();
    
    // Create a new transaction handle from plasma system
    local_20 = FUN_00566d50();
    
    if (local_20 != 0) {
      // Prepare transaction data
      local_10 = param3;
      local_c = param2;
      local_18 = CONCAT44(uStack_24,1);  // Transaction flags: 1 = create
      
      // Call plasma interface virtual function at vtable+0x0c
      // to submit the transaction
      (**(code **)(**(int **)(this + 0x8044) + 0xc))(this + 0x8004, &local_20, 1);
      
      // Check if there was an error
      cVar1 = FUN_00adc2d0();
      if (cVar1 != '\0') {
        // Get error code and log failure
        uVar2 = FUN_00adc2e0();
        FUN_005676d0(uVar2, "Error creating Plasma transaction");
      }
      
      // Get plasma interface pointer
      piVar3 = (int *)(**(code **)**(undefined4 **)(this + 0x8044))();
      
      // Call virtual function at vtable+0x10 with timeout of 10000ms
      (**(code **)(*piVar3 + 0x10))(this + 0x8004, param4, param5, 10000);
    }
  }
  return;
}