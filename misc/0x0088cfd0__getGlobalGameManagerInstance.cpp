// FUNC_NAME: getGlobalGameManagerInstance
// Returns a pointer to the global GameManager singleton stored at 0x00e54220.
// This is a simple accessor function used throughout the codebase to retrieve the single instance.
undefined4 getGlobalGameManagerInstance(void)

{
  return DAT_00e54220;
}