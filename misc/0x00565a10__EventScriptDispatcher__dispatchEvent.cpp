// FUNC_NAME: EventScriptDispatcher::dispatchEvent
uint __thiscall EventScriptDispatcher::dispatchEvent(EventScriptDispatcher *this, ScriptEvent *event)
{
  int iVar1;
  char *scriptName;
  uint retVal;
  int scriptObject;
  code *scriptFunction;
  
  // Initialize the event's script name string (offset +0x8)
  string::assign(&event->scriptName);
  // Retrieve script object and function for this event from the dispatcher's manager
  iVar1 = ScriptManager::getScriptForEvent(this, &scriptObject, &scriptFunction);
  // If script object exists, call its function
  if (scriptObject != 0) {
    scriptFunction(scriptObject);  // scriptFunction is a callback
  }
  // Get the script name from the manager (offset +0x24)
  scriptName = *(char **)(iVar1 + 0x24);
  if (scriptName == (char *)0x0) {
    scriptName = &DAT_0120546e;  // Default script name string
  }
  // Try to run the script function with that name; if it fails, fall back to virtual handler
  retVal = ScriptManager::runScriptFunction(scriptName, 1);
  if ((char)retVal == '\0') {
    // Call virtual function at vtable offset 0x28 on the object pointed to by this+0x20
    retVal = (**(code **)(**(int **)((int)this + 0x20) + 0x28))(event);
  }
  return retVal & 0xffffff00;  // Return high 24 bits as result
}