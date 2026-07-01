// FUNC_NAME: GameplayDebugger::drawVelocityArrow
void __thiscall GameplayDebugger::drawVelocityArrow(void* this, void* debugComponent)
{
  int hashResult;
  float startX, startY, startZ;
  float endX, endY, endZ;
  float velocityScale;
  void* someObject;
  
  // Call a virtual function on debugComponent to get a hash/ID
  hashResult = (*(int (**)(void))*debugComponent)();
  
  // Only proceed if the hash matches a specific ID (likely "velocity" or similar)
  if (hashResult == 0x27a0f69c) {
    // Initialize global velocity scale once
    if ((*(int*)0x0112ba1c & 1) == 0) {
      // Read scale from object at offset 0x58, then +0x1FA0
      *(float*)0x0112ba18 = *(float*)(*(int*)((char*)this + 0x58) + 0x1FA0);
      *(int*)0x0112ba1c |= 1;
    }
    velocityScale = *(float*)0x0112ba18;
    
    // Compute start point: position + velocity * scale
    startX = *(float*)((char*)this + 0x80) * velocityScale + *(float*)((char*)this + 0x74);
    startY = *(float*)((char*)this + 0x84) * velocityScale + *(float*)((char*)this + 0x78);
    startZ = *(float*)((char*)this + 0x88) * velocityScale + *(float*)((char*)this + 0x7C);
    
    // Get some object from a function (possibly camera or world)
    someObject = (void*)FUN_00471610();
    // Overwrite the Y component of start with a value from that object's +0x34 offset
    startY = *(float*)((char*)someObject + 0x34);
    
    // Compute end point: usually (0 - velocity) or similar
    endX = 0.0f - *(float*)((char*)this + 0x80);  // "DAT_00e44564" is 0.0f
    endY = 0.0f - *(float*)((char*)this + 0x84);
    endZ = 0.0f - *(float*)((char*)this + 0x88);
    
    // Draw the arrow with the computed start and end points
    // Parameters: start vector, end vector, some flags, global color, 0, 1
    FUN_00754d30(&startX, &endX, 1, *(int*)0x00d5c454, 0, 1);
  }
  return;
}