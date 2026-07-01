// FUNC_NAME: EARSObject::callVirtualMethod
void EARSObject::callVirtualMethod(TNLMessage *message)
{
  undefined4 *vtablePtr;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  vtablePtr = (undefined4 *)getGlobalVTable(); // FUN_009c8f80 - retrieves some global vtable or class instance
  local_c = 2;                                  // message type or command ID
  local_8 = 0x10;                               // some parameter (size? flags?)
  local_4 = 0;                                  // unused parameter
  (**(code **)*vtablePtr)(message,&local_c);    // call through vtable with message and parameters
  return;
}