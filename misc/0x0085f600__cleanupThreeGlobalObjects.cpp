// FUNC_NAME: cleanupThreeGlobalObjects
void cleanupThreeGlobalObjects(void)
{
  // Call cleanup function on three global objects at known addresses
  FUN_00408310(&DAT_0112dfcc);  // Cleanup global object 1
  FUN_00408310(&DAT_0112dfc4);  // Cleanup global object 2
  FUN_00408310(&DAT_0112dfb8);  // Cleanup global object 3
  return;
}