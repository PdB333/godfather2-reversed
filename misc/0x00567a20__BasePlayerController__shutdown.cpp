// FUNC_NAME: BasePlayerController::shutdown
void __fastcall BasePlayerController::shutdown(undefined4 *this)
{
  // Set vtable to BasePlayerController vtable
  *this = &PTR_FUN_00e3a8d8;
  this[1] = &PTR_LAB_00e3a924;

  // If we have a network connection, notify it
  if ((int *)this[9] != (int *)0x0) {
    (**(code **)(*(int *)this[9] + 8))(this); // Destroy the connection
  }
  this[9] = 0;

  // Clean up combat knowledge
  if ((int *)this[2] != (int *)0x0) {
    (**(code **)(*(int *)this[2] + 0x2c))(); // Release combat knowledge
    this[2] = 0;
  }

  // Clean up combat perception
  if ((int *)this[3] != (int *)0x0) {
    (**(code **)(*(int *)this[3] + 0x5c))(); // Release combat perception
    this[3] = 0;
  }

  // Call a custom destructor callback
  if (this[4] != 0) {
    (*(code *)this[7])(this[4]); // Call the destructor function pointer
  }

  // Reset vtable to base class
  this[1] = &PTR_LAB_00e3a924;
  DAT_012234e4 = 0; // Some global flag
  *this = &PTR_LAB_00e3a890;
  return;
}