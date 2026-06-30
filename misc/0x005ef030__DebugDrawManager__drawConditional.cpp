// FUNC_NAME: DebugDrawManager::drawConditional
void __thiscall DebugDrawManager::drawConditional(int this, int someParam)
{
  int conditionResult;
  
  // Check if the debug draw object at offset +0x580 is non-null
  if (*(int *)(this + 0x580) != 0) {
    // Check if the condition to draw is met
    conditionResult = isConditionMet();
    if (conditionResult != 0) {
      beginDebugDraw();
      drawDebugText(0, someParam); // 0 likely indicates a debug layer or type
      endDebugDraw();
    }
  }
  return;
}