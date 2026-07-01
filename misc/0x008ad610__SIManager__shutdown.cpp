// FUNC_NAME: SIManager::shutdown
void __fastcall SIManager::shutdown(SIManager *this)
{
  int iVar1;
  
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d79fc8;
  this[0xf] = &PTR_LAB_00d79fb8;
  this[0x12] = &PTR_LAB_00d79fb4;
  this[0x14] = &PTR_LAB_00d7a0c8;
  
  // Call base shutdown
  FUN_008aa810(); // SIManager::shutdownBase
  
  // Release common resources (likely strings/buffers)
  FUN_004086d0(&DAT_01218068); // operator delete
  FUN_004086d0(&DAT_0112edf4);
  FUN_004086d0(&DAT_0112ef7c);
  FUN_004086d0(&DAT_012069c4);
  FUN_004086d0(&DAT_0112ecfc);
  
  // Destroy various lists/containers
  FUN_00408310(&DAT_0112ef7c); // list destructor
  FUN_00408310(&DAT_0112edf4);
  FUN_00408310(&DAT_0112f534);
  FUN_00408310(&DAT_0112f1dc);
  FUN_00408310(&DAT_0112b214);
  FUN_00408310(&DAT_0112b2a4);
  FUN_00408310(&DAT_0112b534);
  
  // Shutdown this object's subsystems
  FUN_008b0a80(this); // SIManager::shutdownSubsystems
  FUN_00408310(this + 0x28); // destroy list at +0xA0
  FUN_00408310(this + 0x2e); // destroy list at +0xB8
  FUN_00408310(this + 0x2a); // destroy list at +0xA8
  FUN_00408310(this + 0x2c); // destroy list at +0xB0
  
  // More global destruction
  FUN_00408310(&DAT_0112ecfc);
  FUN_00408310(&DAT_0112f4b4);
  FUN_00408310(&DAT_0112ee7c);
  FUN_00408310(&DAT_0112ee84);
  
  // Delete pending element if exists (+0x148)
  if (this[0x52] != 0) {
    FUN_004035f0(this[0x52], 0x1ff, this + 0xf); // operator delete with size
  }
  
  // Call destructor callbacks (+0x16C, +0x178)
  if (this[0x5b] != 0) {
    (*(code *)this[0x5e])(this[0x5b]); // callback
  }
  if (this[0x57] != 0) {
    (*(code *)this[0x5a])(this[0x57]); // callback
  }
  
  // Unlock/shutdown synchronization objects
  FUN_008ab5f0(); // semaphore destroy
  FUN_008ab5f0();
  FUN_008ab5f0();
  FUN_008ab720(); // mutex destroy
  
  // Release task manager (+0xD4)
  FUN_009c8f10(this[0x35]); // release
  iVar1 = this[0x30]; // task manager pointer (+0xC0)
  if (iVar1 != 0) {
    FUN_009c8f10(*(undefined4 *)(iVar1 + 8)); // release sub-object
    FUN_009c8eb0(iVar1); // delete task manager
  }
  
  // Destroy event listener (+0x80)
  if (this[0x20] != 0) {
    (*(code *)this[0x23])(this[0x20]); // callback
  }
  
  // Shutdown network
  FUN_006a7840(); // NetConnection::shutdown
  
  // Release network event (+0x78)
  FUN_009c8f10(this[0x1e]);
  
  // Delete network connection (+0x64)
  iVar1 = this[0x19];
  if (iVar1 != 0) {
    FUN_009c8f10(*(undefined4 *)(iVar1 + 8)); // release sub-object
    FUN_009c8eb0(iVar1); // delete connection
  }
  
  // Final cleanup
  FUN_00481520(); // shutdown memory manager
  FUN_0046c640(); // shutdown thread pool
  return;
}