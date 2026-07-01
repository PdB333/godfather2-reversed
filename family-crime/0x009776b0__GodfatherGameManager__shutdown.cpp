// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(undefined4 *this)
{
  // Set vtable pointers to destructor stubs
  *this = &PTR_FUN_00d8fa48;
  this[4] = &PTR_LAB_00d8fa24;
  this[0x13] = &PTR_LAB_00d8fa20;
  this[0x14] = &PTR_LAB_00d8fa10;
  this[0x17] = &PTR_LAB_00d8f9f8;
  
  // Check if bit 8 of field at +0x60 is set (some flag)
  if (((uint)this[0x18] >> 8 & 1) != 0) {
    // Clear bit 2 of some global state at DAT_011298d4 + 0x10
    *(uint *)(DAT_011298d4 + 0x10) = *(uint *)(DAT_011298d4 + 0x10) & 0xfffffffb;
    FUN_00912030(); // Likely some cleanup function
    this[0x18] = this[0x18] & 0xfffffeff; // Clear the flag
  }
  
  // Release object at +0xF0
  FUN_009c8f10(this[0x3c]);
  
  // If there's a callback object at +0x120, call its destructor
  if ((undefined4 *)this[0x48] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[0x48])(1);
  }
  
  // If there's a string at +0xB4 and it's non-empty, free it
  if ((*(char *)(this + 0x2d) != '\0') && (this[0x2c] != 0)) {
    FUN_004df600(); // Memory free function
  }
  
  // Unregister from some global list
  FUN_004086d0(&DAT_0112a638);
  
  // Notify shutdown
  FUN_00977140(1);
  
  // Remove event handlers (callbacks at LAB_009767b0 and LAB_00976800)
  FUN_005c0c50(this + 5, &LAB_009767b0);
  FUN_005c0c50(this + 5, &LAB_00976800);
  
  // Release more objects
  if (this[0x4b] != 0) {
    FUN_009c8f10(this[0x4b]);
  }
  
  // Clear and release multiple pointer fields (likely smart pointers or handles)
  // Each at offsets +0x108, +0x104, +0x100, +0xFC, +0xF8, +0xF4, +0xB0
  if (this[0x42] != 0) {
    *(undefined4 *)(this[0x42] + 8) = 0;
    this[0x42] = 0;
  }
  if (this[0x41] != 0) {
    *(undefined4 *)(this[0x41] + 8) = 0;
    this[0x41] = 0;
  }
  if (this[0x40] != 0) {
    *(undefined4 *)(this[0x40] + 8) = 0;
    this[0x40] = 0;
  }
  if (this[0x3f] != 0) {
    *(undefined4 *)(this[0x3f] + 8) = 0;
    this[0x3f] = 0;
  }
  if (this[0x3e] != 0) {
    *(undefined4 *)(this[0x3e] + 8) = 0;
    this[0x3e] = 0;
  }
  if (this[0x3d] != 0) {
    *(undefined4 *)(this[0x3d] + 8) = 0;
    this[0x3d] = 0;
  }
  if (this[0x2c] != 0) {
    *(undefined4 *)(this[0x2c] + 8) = 0;
    this[0x2c] = 0;
  }
  
  // Final cleanup
  FUN_004083d0();
  
  // Update vtable pointer to final destructor stub
  this[0x13] = &PTR_LAB_00d8f9f4;
  
  // Clear global flag
  DAT_0112af70 = 0;
  
  // Final cleanup function
  FUN_005c16e0();
  
  return;
}