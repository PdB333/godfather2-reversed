// FUNC_NAME: JobQueue::enqueueJob
void __thiscall JobQueue::enqueueJob(int this, int jobId)
{
  int queueIndex;
  int totalPending;

  // Check if the queue is active (bit 1 of flags at +0x100)
  if ((*(unsigned char*)(this + 0x100) >> 1 & 1) != 0) {
    queueIndex = *(int*)(this + 0x54); // current insertion index (number of jobs in main array)
    // Sum all pending counts from various sub-queues (offsets 0x30, 0x78, 0x9c, 0x54)
    totalPending = *(int*)(this + 0x9c) + *(int*)(this + 0x78) + *(int*)(this + 0x30) + queueIndex;
    if (totalPending < 8) {
      // Validate the job via external function; returns negative if allowed
      if (FUN_0097b760(jobId) < 0) {
        // Store the job at the next slot in the main job array
        *(int*)(this + 0x34 + queueIndex * 4) = jobId;
        // Increment the main queue count
        *(int*)(this + 0x54) = queueIndex + 1;
        // If the queue was completely empty before insertion, start processing
        if (totalPending == 0) {
          FUN_0097c5a0();
        }
      }
    }
  }
}