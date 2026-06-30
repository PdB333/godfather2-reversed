// FUNC_NAME: SomeClass::~SomeClass (or destructor: releaseResources)
void __fastcall SomeClass::releaseResources(void* this)
{
  *this = &PTR_LAB_00d65ae4; // Set vtable to derived class table (e.g., BaseVehicle vtable)
  
  // Check if a flag at +0x8DC (child object at +0x5C, offset 0x238) has bit 10 set
  if (((uint)(*((int**)((char*)this + 0x5C)) + 0x23C) >> 10 & 1) != 0) // +0x5C->+0x8DC (0x238*4=0x8E0? careful: offset 0x238 is a field index? Actually param_1[0x17] is a pointer at +0x5C, then [0x238] is offset 0x238*4=0x8E0 from that pointer. So bit at +0x8DC? Let's recalc: param_1[0x17] is at +0x5C, then *(int*)((char*)param_1[0x17] + 0x238*4) is +0x8E0. But the decompiled says [0x238] >> 10 &1. That means field at index 0x238 (assuming int array). So offset = 0x238 * 4 = 0x8E0 from the object at +0x5C. But the condition uses (int*)param_1[0x17])[0x238] which is dereferencing the pointer at +0x5C, then accessing its field at byte offset 0x238*4 = 0x8E0. So bit 10 of that int.
  {
    (**(code **)(*(int*)((char*)this + 0x5C) + 0x260))(); // Call virtual function at vtable+0x260 (likely finalize/shutdown)
  }
  
  *this = &PTR_LAB_00d63090; // Switch to base class vtable (e.g., Entity vtable)
  
  // Release child object at +0x68
  if (*(void**)((char*)this + 0x68) != 0)
  {
    FUN_004daf90((char*)this + 0x68); // Call destructor/release for that child
  }
  
  FUN_0080ea60(); // Static cleanup (e.g., memory deallocation or singleton cleanup)
}