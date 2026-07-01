// FUNC_NAME: TimelineSequencer::advanceExecution
void __fastcall TimelineSequencer::advanceExecution(int this) // 0x009894e0
{
  int duration;
  
  if (*(int *)(this + 0x5c) != 0) {
    // Decrement remaining time
    *(int *)(this + 0x5c) = *(int *)(this + 0x5c) - 1;
    
    // Get current position, clamped to maxDuration
    duration = *(int *)(this + 0x68);
    if (*(int *)(this + 0x70) <= *(int *)(this + 0x68)) {
      duration = *(int *)(this + 0x70); // +0x70 = maxDuration
    }
    
    // Execute timeline step at given duration position (calls into animation/DSP system)
    FUN_009893a0(duration); // +0x68 = currentDuration
  }
}