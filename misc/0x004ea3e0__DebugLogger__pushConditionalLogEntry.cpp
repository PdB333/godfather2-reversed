// FUNC_NAME: DebugLogger::pushConditionalLogEntry
void __fastcall DebugLogger::pushConditionalLogEntry(int param_1, int param_2)
{
  // param_1 likely ECX – some context or reason
  // param_2 likely in EDX? Decompiler shows in_EAX – actually passed in EAX? Let's treat as second parameter.

  int threadFlag;
  int bufferBase;
  int *__frame;

  // Fetch thread-local flag: fs:[0x2c] -> dereference -> +0x34
  __frame = (int *)__readfsdword(0x2c); // TEB linear address
  threadFlag = *(int *)(__frame[0] + 0x34); // Get some state (e.g., main thread check)

  // If not in main thread, or param_2 is null, or param_1 == 2 (force flush?)
  if (((threadFlag != 1) || (param_2 == 0)) || (param_1 == 2)) {
    // Clear a flag in an array (maybe cancel the pending log)
    // Index based on threadFlag being non-zero
    param_2[(uint)(threadFlag != 0) * 0x26 + 1] = 0;
  }

  // Now decide whether to actually push a log entry
  // Condition: (threadFlag==1 AND param_2 != 0) OR param_1 == 2
  if (((threadFlag == 1) && (param_2 != 0)) || (param_1 == 2)) {
    // Select the buffer pointer: either g_pBufferA or g_pBufferB
    if ((((threadFlag != 1) || (param_2 == 0)) || (param_1 == 2)) && (bufferBase = DAT_01206880, threadFlag != 0)) {
      bufferBase = DAT_012068e8; // Fallback buffer
    } else {
      bufferBase = DAT_01206880; // Chosen based on previous condition
    }

    // Write the log entry: first a pointer to a vtable/function (PTR_LAB_01124be4)
    *(void **)(*(int *)(bufferBase + 0x14)) = &PTR_LAB_01124be4;
    *(int *)(bufferBase + 0x14) += 4; // Advance pointer

    // Then write the condition flag
    *(uint *) (*(int *)(bufferBase + 0x14)) = (uint)(threadFlag != 0);
    *(int *)(bufferBase + 0x14) += 4;
  }
  return;
}