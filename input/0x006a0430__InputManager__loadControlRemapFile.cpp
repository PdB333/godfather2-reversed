//FUNC_NAME: InputManager::loadControlRemapFile
void InputManager::loadControlRemapFile(void)
{
  undefined2 *pData;
  undefined2 *pDataArray[3];
  code *pDestructor;

  // Load the "controls_rmp" resource (flag=1 indicates load from file)
  FUN_00699080(pDataArray,PTR_u_controls_rmp_00e50c74,1);
  pData = pDataArray[0];
  if (pDataArray[0] == (undefined2 *)0x0) {
    // Use default control mapping data if file not found
    pData = &DAT_00e2df14;
  }
  // Parse/apply the control mapping data
  FUN_00497620(pData);
  if (pDataArray[0] != (undefined2 *)0x0) {
    // Call destructor/release function on the loaded data
    (*pDestructor)(pDataArray[0]);
  }
  return;
}