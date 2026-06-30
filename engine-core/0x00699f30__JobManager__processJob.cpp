// FUNC_NAME: JobManager::processJob
undefined4 __thiscall JobManager::processJob(void* this)

{
  int* jobPtr;
  int jobId;
  int* dataPtr;
  int* endPtr;
  bool jobFound;
  uint8_t buffer[4];
  uint32_t callbackData[3];
  code* callback;
  code* unknownCallback;
  
  jobPtr = g_jobListStart;   // DAT_01129f8c
  endPtr = g_jobListEnd;     // DAT_01129f90
  
  if (jobPtr == endPtr) {
    return 0;
  }
  
  do {
    jobId = *jobPtr;
    // Prepare for checking this job
    FUN_004d3bc0(this);
    
    // Initialize callback and data fields
    callbackData[0] = 0;
    callbackData[1] = 0;
    callbackData[2] = 0;
    unknownCallback = (code*)0x0;
    
    // Get job data - returns pointer to a job state structure
    dataPtr = (int*)FUN_00698c00(buffer, callbackData);
    
    // Compare the job's unique ID with expected value (jobId + 12)
    jobFound = (*dataPtr != (jobId + 12));
    
    if (jobFound) {
      // Execute some action if mismatch: call function at offset 0x20 from data
      FUN_004d3e20(*dataPtr + 0x20);
    }
    
    // Cleanup callbacks if set
    if (callbackData[0] != 0) {
      (*unknownCallback)(callbackData[0]);
    }
    if (callbackData[0] != 0) {
      (*callback)(callbackData[0]);   // Possibly different callback from local_4
    }
    
    if (jobFound) {
      return 1;
    }
    
    jobPtr++;
  } while (jobPtr != endPtr);
  
  return 0;
}