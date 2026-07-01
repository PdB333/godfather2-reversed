// Xbox PDB: EARS_Modules_GameTimeEventScheduler_GameTimeEventScheduler
//FUNC_NAME: EventScheduler::EventScheduler
undefined4 * __thiscall EventScheduler::EventScheduler(EventScheduler *this, undefined4 heapId)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  int *local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Store this pointer globally (likely for singleton access)
  DAT_0112a55c = this;
  
  // Set vtable pointers (base class at +0x00, derived at +0x04)
  this->vtableBase = &PTR_FUN_00d6fffc;       // +0x00
  this->vtableDerived = &PTR_LAB_00d6ffec;    // +0x04
  
  // Initialize member variables
  this->field_0x08 = 1;                        // +0x08
  this->field_0x0C = 0;                        // +0x0C
  this->heapId = heapId;                       // +0x14
  this->field_0x38 = 0;                        // +0x38
  
  // Register message "iMsgGameTimeEventSchedulerFull" if not already registered
  if (DAT_012067cc != 0) {
    FUN_00408900(&this->vtableDerived, &DAT_012067cc, 0x8000);
  }
  FUN_00408240(&DAT_0112bb48, "iMsgGameTimeEventSchedulerFull");
  
  // Create a memory pool (0x24 bytes, alignment 4, using heapId)
  uVar1 = FUN_004abe60(0x24, 4, this->heapId);
  uVar2 = FUN_009c8e80(uVar1);
  this->memoryPool = uVar2;                    // +0x10
  
  // Allocate and construct the scheduler implementation object (0x28 bytes)
  puVar3 = (undefined4 *)FUN_009c8e50(0x28);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    uVar2 = this->memoryPool;
    puVar3->vtable = &PTR_LAB_00e30fc0;        // +0x00
    FUN_004abe90(uVar2, uVar1, 0x24, 4);       // Initialize pool
    puVar3[9] = 1;                              // +0x24
    FUN_004abfd0(0);
  }
  this->schedulerImpl = puVar3;                // +0x1C
  
  // Allocate and initialize a hash table or event list (0x20 bytes)
  iVar4 = FUN_009c8e50(0x20);
  if (iVar4 == 0) {
    uVar1 = 0;
    piVar5 = local_14;
  }
  else {
    piVar5 = (int *)this->schedulerImpl;
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    local_14 = piVar5;
    // Call virtual function at vtable+8 (likely getSize or similar)
    (**(code **)(*piVar5 + 8))();
    local_10 = FUN_004265d0(&local_c, piVar5);
    uVar1 = FUN_007ed890(&local_14);
  }
  this->eventTable = uVar1;                    // +0x18
  
  // Clean up temporary allocation if it succeeded
  if (iVar4 != 0) {
    if (local_10 != 0) {
      (**(code **)(*piVar5 + 4))(local_10, 0); // vtable+4 (destructor?)
    }
    (**(code **)(*piVar5 + 0xc))();            // vtable+12 (free?)
  }
  
  // Register message "iMsgGameTimeUpdated" and subscribe if valid
  FUN_00408240(&DAT_0112db7c, "iMsgGameTimeUpdated");
  if (DAT_0112db7c != 0) {
    FUN_00408900(&this->vtableDerived, &DAT_0112db7c, 0x8000);
  }
  
  // Final initialization
  this->field_0x20 = 0;                        // +0x20
  this->field_0x24 = 0xffffffff;               // +0x24
  
  return this;
}