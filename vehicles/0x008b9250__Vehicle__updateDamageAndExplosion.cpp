// FUNC_NAME: Vehicle::updateDamageAndExplosion
void __fastcall Vehicle::updateDamageAndExplosion(int *this)
{
  int *vtable;
  float damage;
  
  // Call virtual function at vtable+0x28 to get current damage level
  damage = (**(float (__fastcall **)(int))(*(int *)this[0x84] + 0x28))();
  
  if (0.0f < damage) {
    // Set damage to 0 via virtual function at vtable+0x3c
    (**(void (__fastcall **)(int, float))(*(int *)this[0x84] + 0x3c))(0, 0.0f);
    
    vtable = (int *)this[0x4c]; // +0x4C: pointer to explosion effect object
    if (vtable != (int *)0x0) {
      FUN_004a56e0(); // Play explosion sound effect
      (**(void (__fastcall **)(int, int))(*(int *)this + 0x154))(0, 0); // Spawn explosion VFX
      (**(void (__fastcall **)(int *))(*(int *)vtable + 0x2c))(); // Start explosion animation
    }
    
    // Check bit 3 of flags at +0x18C (this[99])
    if (((uint)this[99] >> 3 & 1) != 0) {
      FUN_0081cf20(this); // Handle vehicle destruction/removal
      this[99] = this[99] & 0xfffffff7; // Clear bit 3
      return;
    }
  }
  return;
}