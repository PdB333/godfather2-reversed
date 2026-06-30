// FUNC_NAME: EventDispatcher::dispatchEvents
void EventDispatcher::dispatchEvents(void *callback, undefined4 userData)
{
  int *bucketArray;
  uint bucketIndex;
  undefined4 *eventNode;
  
  bucketArray = DAT_012054c4; // global event bucket array
  FUN_004e1020(); // likely lockMutex or enterCriticalSection
  if (eventNode != (undefined4 *)0x0) {
    do {
      while( true ) {
        ((code *)callback)(*eventNode, userData); // call callback with event data
        eventNode = (undefined4 *)eventNode[1]; // move to next node in linked list
        if (bucketArray == (int *)0x0) break;
        if (eventNode == (undefined4 *)0x0) {
          do {
            if ((uint)bucketArray[1] <= bucketIndex) goto LAB_004df202; // bucket count check
            eventNode = *(undefined4 **)(*bucketArray + bucketIndex * 4); // get first node from next bucket
            bucketIndex = bucketIndex + 1;
          } while (eventNode == (undefined4 *)0x0); // skip empty buckets
        }
      }
LAB_004df202:
    } while (eventNode != (undefined4 *)0x0);
  }
  return;
}