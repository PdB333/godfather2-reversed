// FUNC_NAME: InputManager::shutdown
void InputManager::shutdown(void)
{
  // Call base class destructor or cleanup function with global input manager data
  FUN_00408680(&DAT_012069c4);
  // Perform input manager specific shutdown
  FUN_006bbee0();
  return;
}