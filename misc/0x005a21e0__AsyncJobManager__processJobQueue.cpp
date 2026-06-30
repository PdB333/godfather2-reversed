// FUNC_NAME: AsyncJobManager::processJobQueue
void AsyncJobManager::processJobQueue(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  undefined4 *puVar5;
  char cVar6;
  undefined4 *local_8;
  
  puVar5 = DAT_0119a9c8; // g_jobQueueHead - linked list of job queues
  do {
    local_8 = (undefined4 *)*puVar5; // current queue node
    bVar4 = false;
    if (local_8 == (undefined4 *)0x0) {
      return;
    }
    do {
      piVar1 = (int *)*local_8; // current job in queue
      if (piVar1 != (int *)0x0) {
        *piVar1 = *piVar1 + 1; // increment ref count
      }
      do {
        while( true ) {
          while (iVar2 = piVar1[8], iVar2 == 1) { // job state == JOB_STATE_INITIAL
            piVar1[8] = 2; // set to JOB_STATE_RUNNING
            *piVar1 = *piVar1 + 1; // increment ref count
            (*DAT_0119cb10)(piVar1[3],piVar1); // call job execute function
          }
          if (iVar2 == 2) goto LAB_005a2378; // JOB_STATE_RUNNING - skip
          if (iVar2 != 3) break; // not JOB_STATE_COMPLETED
          *piVar1 = *piVar1 + 1; // increment ref count
          cVar6 = FUN_005a20d0(puVar5,piVar1); // check if job can be finalized
          if (cVar6 == '\\0') goto LAB_005a2378; // not ready yet
          piVar1[8] = 4; // set to JOB_STATE_FINALIZING
          bVar4 = true;
          FUN_005a5a20(piVar1[0xb]); // process job result
          *piVar1 = *piVar1 + 1; // increment ref count
          *piVar1 = *piVar1 + 1; // increment ref count
          *piVar1 = *piVar1 + 1; // increment ref count
          FUN_005a27d0(piVar1); // finalize job
          if (DAT_0119cad0 != 0) { // g_jobDebugEnabled
            FUN_005a1d10(DAT_0119cae4); // log job completion
          }
          *piVar1 = *piVar1 + -1; // decrement ref count
          if (*piVar1 == 0) {
            FUN_005a1f20(); // free job memory
            if ((piVar1[8] == 3) || (piVar1[8] == 4)) { // if completed or finalizing
              FUN_005a5650(piVar1[9]); // release job data
              (*DAT_0119cb14)(piVar1[0xb]); // free result
            }
            piVar3 = (int *)piVar1[3]; // job callback
            if ((piVar3 != piVar1 + 4) && (piVar3 != (int *)0x0)) {
              (*DAT_0119caf4)(piVar3); // call callback destructor
            }
            (*DAT_0119caf8)(piVar1,0x30); // free job struct (48 bytes)
          }
          *piVar1 = *piVar1 + -1; // decrement ref count
          if (*piVar1 == 0) {
            FUN_005a1f20(); // free job memory
            if ((piVar1[8] == 3) || (piVar1[8] == 4)) { // if completed or finalizing
              FUN_005a5650(piVar1[9]); // release job data
              (*DAT_0119cb14)(piVar1[0xb]); // free result
            }
            piVar3 = (int *)piVar1[3]; // job callback
            if ((piVar3 != piVar1 + 4) && (piVar3 != (int *)0x0)) {
              (*DAT_0119caf4)(piVar3); // call callback destructor
            }
            (*DAT_0119caf8)(piVar1,0x30); // free job struct (48 bytes)
          }
        }
      } while (iVar2 != 4); // JOB_STATE_FINALIZING - skip
LAB_005a2378:
      *piVar1 = *piVar1 + -1; // decrement ref count
      if (*piVar1 == 0) {
        FUN_005a1f20(); // free job memory
        if ((piVar1[8] == 3) || (piVar1[8] == 4)) { // if completed or finalizing
          FUN_005a5650(piVar1[9]); // release job data
          (*DAT_0119cb14)(piVar1[0xb]); // free result
        }
        piVar3 = (int *)piVar1[3]; // job callback
        if ((piVar3 != piVar1 + 4) && (piVar3 != (int *)0x0)) {
          (*DAT_0119caf4)(piVar3); // call callback destructor
        }
        (*DAT_0119caf8)(piVar1,0x30); // free job struct (48 bytes)
      }
      local_8 = (undefined4 *)local_8[1]; // next queue node
    } while (local_8 != (undefined4 *)0x0);
    if (!bVar4) {
      return;
    }
  } while( true );
}