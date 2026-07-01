// FUNC_NAME: SimManager::destructor
void __fastcall SimManager::destructor(SimManager *this)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  this->vfptr = &SimManager_vftable_0;
  this->field_0x74 = &PTR_LAB_00d6eba4;  // +0x74 - another vtable or callback
  this->field_0x98 = &PTR_LAB_00d6eba0;  // +0x98 - another vtable or callback
  this->field_0x1c0 = 0;                 // +0x1c0 - flag or pointer
  
  // Release various singleton/managed resources (likely string/shared refs)
  releaseRef(&gSimManagerString1);       // DAT_0112ba94
  releaseRef(&gSimManagerString2);       // DAT_0112ba84
  releaseRef(&gSimManagerString3);       // DAT_0112ba60
  releaseRef(&gSimManagerString4);       // DAT_0112ba7c
  releaseRef(&gSimManagerString5);       // DAT_0112ba68
  releaseRef(&gSimManagerString6);       // DAT_0112ba8c
  releaseRef(&gSimManagerString7);       // DAT_0112ba74
  
  // Clean up manager-specific resources
  cleanupSimSubsystem();                  // FUN_007cd5e0
  
  // Delete named objects (if present)
  if (this->field_0x1fc != 0) {          // +0x1fc - pointer to object
    (*(code *)this->field_0x208)(this->field_0x1fc);  // +0x208 - destructor func
  }
  if (this->field_0x1ec != 0) {          // +0x1ec - pointer to object
    (*(code *)this->field_0x1f8)(this->field_0x1ec);  // +0x1f8 - destructor func
  }
  if (this->field_0x1b4 != 0) {          // +0x1b4 - pointer to object
    deleteObject(this + 0x1b4);          // FUN_004daf90
  }
  
  // Final cleanup
  finalCleanup();                        // FUN_007affe0
  
  // Reset vtable and free linked list
  this->field_0x98 = &PTR_FUN_00e32808;  // +0x98 - vtable for list nodes
  puVar2 = (undefined4 *)this->field_0x9c; // +0x9c - head of linked list
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar2[1];    // next node
    puVar2[1] = 0;                       // clear next
    *puVar2 = 0;                         // clear data
    puVar2 = puVar1;
  }
  
  // Clean up manager system
  cleanupManagerSystem();                // FUN_007ca830
  
  this->vfptr = &SimManager_vftable_1;   // +0x00 - base class vtable
  finalDestructor();                     // FUN_0080ea60
}