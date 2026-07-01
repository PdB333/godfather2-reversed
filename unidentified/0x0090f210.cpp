// FUN_NAME: EventHandler::onMessage
// Function address: 0x0090f210
// Role: Event handler - checks if the incoming message ID (param_2) matches the object's registered ID (obtained from FUN_00466840).
// If matched, calls the virtual function at vtable offset +0x2c (likely onEvent or processMessage).

undefined4 __thiscall EventHandler::onMessage(int *thisPtr, int messageId)
{
  int registeredId;

  registeredId = getRegisteredMessageId();  // FUN_00466840 - returns the message ID this object is registered to handle
  if (messageId == registeredId) {
    // Call the virtual event handler (vtable slot at offset 0x2c)
    (thisPtr->vtable[0x2c / 4])(thisPtr);
  }
  return 0;
}