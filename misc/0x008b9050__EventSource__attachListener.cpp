// FUNC_NAME: EventSource::attachListener
void __thiscall EventSource::attachListener(EventSource *this, int listenerObject)
{
  int listenerNode;
  int listenerNode2;
  byte tempBuffer[4];
  int oldNext1;
  undefined4 unused1;
  int oldNext2;
  undefined4 unused2;
  undefined8 engineData1;
  undefined4 engineData2;
  undefined8 engineData3;
  undefined4 engineData4;
  float elapsedTime;
  undefined4 unused3;
  undefined4 unused4;
  
  initCriticalSection();
  
  // Get the node pointer from the listener object (offset 0x48)
  if (listenerObject == 0) {
    listenerNode = 0;
  }
  else {
    listenerNode = listenerObject + 0x48;
  }
  
  // If the current attached node differs, release old and attach new
  if ( /* m_listHead1 */ local_44 != listenerNode) {
    if (local_44 != 0) {
      releaseListenerNode(&local_44);
    }
    local_44 = listenerNode;
    if (listenerNode != 0) {
      oldNext1 = *(int *)(listenerNode + 4);  // save old next pointer
      *(int **)(listenerNode + 4) = &local_44; // point to self as next? (likely a bug in decompilation)
    }
  }
  
  // Repeat for a second list head (e.g., secondary listener list)
  if (listenerObject == 0) {
    listenerNode2 = 0;
  }
  else {
    listenerNode2 = listenerObject + 0x48;
  }
  if ( /* m_listHead2 */ local_3c != listenerNode2) {
    if (local_3c != 0) {
      releaseListenerNode(&local_3c);
    }
    local_3c = listenerNode2;
    if (listenerNode2 != 0) {
      oldNext2 = *(int *)(listenerNode2 + 4);
      *(int **)(listenerNode2 + 4) = &local_3c;
    }
  }
  
  // Retrieve engine state for logging
  EngineState *engine = Engine::getInstance();
  engineData1 = engine + 0x30;  // some fields
  engineData2 = engine + 0x38;
  
  // Prepare log parameters
  int logType = 0xb;  // log severity or type
  int logFlag = 0;
  
  // Get current time from this object (vtable+0xc0)
  elapsedTime = (float)(*(code **)(*(int *)this + 0xc0))();
  
  engine = Engine::getInstance();
  engineData3 = engine + 0x30;
  engineData4 = engine + 0x38;
  
  // Log the event: format string, name of this (at offset 0xf), buffer, length=0
  Debug::log(DAT_0112dd94, this + 0xf, tempBuffer, 0);
  
  // Cleanup nodes if still attached (shouldn't happen after detach)
  if (local_3c != 0) {
    releaseListenerNode(&local_3c);
  }
  if (local_44 != 0) {
    releaseListenerNode(&local_44);
  }
}