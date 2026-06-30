// FUNC_NAME: GodfatherGameManager::resetGlobalState
void GodfatherGameManager::resetGlobalState(void)

{
  // +0x00: Global state variables at 0x01219260-0x012192dc
  // These are likely static/global variables for game state management
  
  // Initialize time-related values (DAT_00e39f98 is probably a default time value)
  _DAT_01219270 = DAT_00e39f98;  // +0x10: startTime
  DAT_01219274 = DAT_00e39f98;   // +0x14: endTime
  
  // Reset counters/flags to zero
  _DAT_01219260 = 0;  // +0x00: someFlag1
  _DAT_01219264 = 0;  // +0x04: someFlag2
  _DAT_01219268 = 0;  // +0x08: someCounter
  
  // Initialize position/vector values (DAT_00e2b1a4 is likely a zero vector or default position)
  _DAT_0121926c = DAT_00e2b1a4;  // +0x0C: positionX
  DAT_01219250 = DAT_00e2b1a4;   // -0x10: positionY (overlapping with previous)
  DAT_01219254 = DAT_00e2b1a4;   // -0x0C: positionZ
  _DAT_01219258 = DAT_00e2b1a4;  // -0x08: someVectorComponent
  
  // Initialize another value (DAT_00e445ac is likely a default rotation/angle)
  DAT_01219278 = DAT_00e445ac;   // +0x18: rotation
  DAT_0121927c = 0;             // +0x1C: someFlag3
  
  // Reset more state variables
  DAT_01219290 = 0;  // +0x30: someFlag4
  DAT_01219294 = 0;  // +0x34: someFlag5
  DAT_01219280 = 0;  // +0x20: someFlag6
  DAT_01219284 = 0;  // +0x24: someFlag7
  
  // Initialize more vector values
  DAT_01219288 = DAT_00e2b1a4;  // +0x28: someVectorX
  DAT_0121928c = DAT_00e2b1a4;  // +0x2C: someVectorY
  
  // Reset remaining counters/flags
  DAT_0121925c = 0;  // -0x04: someFlag8
  DAT_012192a0 = 0;  // +0x40: someFlag9
  DAT_012192dc = 0;  // +0x7C: someFlag10
  
  return;
}