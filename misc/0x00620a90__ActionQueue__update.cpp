// FUNC_NAME: ActionQueue::update
void ActionQueue::update(int *this)
{
  int iVar1;
  int time;
  int *piVar3;
  uint uVar4;
  int *currentJob;
  int processedCount;
  int *puStack_34;
  int *apuStack_30 [2];
  float conditionVal;
  int jobData1;
  int jobData2;
  int jobData3;
  int jobData4;
  
  // Per-frame initialization
  tickInit();
  // Call vtable function at +0xc (likely virtual update)
  (**(code **)(*this + 0xc))();
  
  time = getTickCount();
  // Check if delayed callback timer has expired
  if (((int)((float)this[0x12] * timerMultiplier) <= time) && (this[0xc] != 0)) {
    acquireMutex(&globalMutex);
    // Recheck after acquiring lock
    (**(code **)(*this + 0xc))();
    time = getTickCount();
    if (((int)((float)this[0x12] * timerMultiplier) <= time) &&
       ((code *)this[0xc] != (code *)0x0)) {
      // First time flag
      if ((char)this[0x20] == '\0') {
        *(undefined1 *)(this + 0x20) = 1;
        // Execute delayed callback
        (*(code *)this[0xc])(this[0xd]);
      }
      releaseMutex(&globalMutex);
      return;
    }
    releaseMutex(&globalMutex);
  }
  
  // Process ring buffer (job queue)
  if (this[10] != 0) {
    // First pass: process pending dequeued jobs
    int count = this[0x22];
    while (count != 0) {
      // Dequeue a job (type 3)
      ringBufferDequeue(this[2], *(int *)(this[0x28] + 0x10), 3, apuStack_30);
      if (this[0x22] == 0) {
        apuStack_30[0] = 0;
      } else {
        apuStack_30[0] = (int *)(this[0x25] * 0x10 + this[0x26]);
      }
      ringBufferOp1();
      ringBufferPop(3, apuStack_30);
      ringBufferOp2();
      // Check condition: if conditionVal != some constant OR queue empty, break
      if ((conditionVal != knownFloatConstant) || (this[0x22] == 0)) break;
      
      // Write modified job back to ring buffer
      iVar2 = this[0x25];
      iVar1 = this[0x26];
      piVar3 = (int *)(iVar1 + iVar2 * 0x10);
      *piVar3 = this[0x23];
      piVar3[2] = *(int *)(iVar1 + 8 + iVar2 * 0x10);
      piVar3[1] = 0;
      this[0x25] = this[0x25] + 1;
      if ((uint)this[0x21] <= (uint)this[0x25]) {
        this[0x25] = 0;
      }
      this[0x22] = this[0x22] - 1;
      count = this[0x22];
    }
    
    // Second pass: process pending enqueued jobs
    currentJob = 0;
    processedCount = 0;
    if (this[0x22] != this[0x21]) {
      // Get next job to process from write index
      currentJob = (int *)(this[0x24] * 0x10 + this[0x26]);
      uVar4 = this[0x24] + 1;
      this[0x24] = uVar4;
      if ((uint)this[0x21] <= uVar4) {
        this[0x24] = 0;
      }
      this[0x22] = this[0x22] + 1;
    }
    
    if (currentJob != 0) {
      while( true ) {
        pushProfilerContext();
        // Prepare job data for callback
        jobData4 = 0;
        jobData1 = currentJob[2];
        jobData2 = *currentJob;
        jobData3 = 0;
        
        if ((code *)this[10] != (code *)0x0) break;
        
LAB_00620d3e:
        if (5 < processedCount) goto LAB_00620d9e;
        
        currentJob = 0;
        if (this[0x22] != this[0x21]) {
          currentJob = (int *)(this[0x24] * 0x10 + this[0x26]);
          uVar4 = this[0x24] + 1;
          this[0x24] = uVar4;
          if ((uint)this[0x21] <= uVar4) {
            this[0x24] = 0;
          }
          this[0x22] = this[0x22] + 1;
        }
        popProfilerContext();
        if (currentJob == 0) {
          return;
        }
      }
      
      // Call the job processing callback
      puStack_34 = &jobData1;
      (*(code *)this[10])(&puStack_34, this[0xb]);
      
      if (puStack_34[3] != 0) { // If callback returned new data
        // Re-enqueue the job with new data
        if (this[0x22] != this[0x21]) {
          this[0x24] = this[0x24] + 1;
          if ((uint)this[0x21] <= (uint)this[0x24]) {
            this[0x24] = 0;
          }
          this[0x22] = this[0x22] + 1;
        }
        *currentJob = puStack_34[3];
        currentJob[1] = 0;
        // Enqueue back (type 2)
        ringBufferEnqueue(this[2], *(int *)(this[0x28] + 0x10), 2, apuStack_30);
        apuStack_30[0] = currentJob;
        ringBufferOp1();
        ringBufferPush(2, apuStack_30);
        ringBufferOp2();
        processedCount = processedCount + 1;
        goto LAB_00620d3e;
      }
      
LAB_00620d9e:
      popProfilerContext();
    }
  }
  return;
}