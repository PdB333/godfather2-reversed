// FUN_006acea0: PlayerReputationTracker::updateEventQueue

void __fastcall PlayerReputationTracker::updateEventQueue(PlayerReputationTracker* this)
{
  int* elementPtr;
  int i;
  float floatVal;
  int* globalObj;
  undefined4 debugStrPtr;
  char* pDebugStr;
  // +0x3d4: bit flags for active event types (bit0 = startEvent, bit2 = endEvent)
  bool isStartEvent = (*(byte*)(this + 0x3d4) & 1) != 0;
  bool isEndEvent = ((*(uint*)(this + 0x3d4) >> 2) & 1) != 0;

  if (isStartEvent || isEndEvent)
  {
    // Handle start-of-event actions
    if (isStartEvent)
    {
      // Iterate over 20 crime/event slots starting at +0x34, each 12 bytes (3 ints)
      elementPtr = (int*)((char*)this + 0x34);
      i = 20;
      do
      {
        // Check if the slot's flag (at relative offset -2 ints) has bit1 set
        // and the slot's state (first int) is 0 (idle).
        if ((((uint)elementPtr[-2] >> 1) & 1) != 0 && *elementPtr == 0)
        {
          // Free the resource pointer stored in the slot (second int)
          FUN_00894c90((void*)elementPtr[1]);
          // Free a constant handle (0x94090189) – likely a mission/asset ID
          FUN_00894c90((void*)0x94090189);
          // Reset the slot's progress or count (field 5 ints before current element)
          elementPtr[-5] = 0;
        }
        elementPtr += 3; // advance 12 bytes (3 ints)
        i--;
      } while (i != 0);

      // Convert signed integer to float with rounding
      floatVal = (float)*(int*)((char*)this + 0x3e4);  // +0x3e4: event start time or count
      if (*(int*)((char*)this + 0x3e4) < 0)
      {
        floatVal = floatVal + -0.0f;  // DAT_00e44578 is -0.0f (used for sign fix)
      }
      // Send event with ID 0xefb654ea
      FUN_00894e50(0xefb654ea, floatVal, 0);

      // Access global game manager (DAT_012233a0 + 4)
      globalObj = *(int**)(DAT_012233a0 + 4);
      if (globalObj != 0 && globalObj != (int*)0x1f30) // 0x1f30 = invalid sentinel
      {
        int checkVal = FUN_008c74d0(*(int*)((char*)globalObj - 0x5c));
        if (checkVal != 0)
        {
          FUN_008c29a0(*(undefined4*)((char*)this + 0x3e4), 4); // set flag 4
        }
      }

      // Retrieve debug string based on event ID
      FUN_004d4a60(&debugStrPtr, 1, &DAT_00d5db54, *(undefined4*)((char*)this + 0x3e4));
      pDebugStr = (char*)debugStrPtr;
      if (pDebugStr == 0)
      {
        pDebugStr = (char*)&DAT_0120546e; // default string
      }
      // Log with tags 'S','P','G','P' (ASCII 0x53504750, 0x53574753)
      FUN_009085a0(0x53504750, 0x53574753, pDebugStr);

      // Play a sound effect (index 0x2d)
      FUN_007e7df0(0x2d);

      if (globalObj != 0 && globalObj != (int*)0x1f30)
      {
        FUN_0079f100(0x30, 0); // set some parameter to 0
      }

      // Spawn VFX (visual effect) with ID 0x51c560e8
      FUN_0093f540(0x51c560e8, 0, 0, 0, 0);

      if (debugStrPtr != 0)
      {
        // Free the allocated debug string via its destructor
        ((void (*)(void*))local_8)((void*)debugStrPtr);
      }
    }

    // Handle end-of-event actions
    if (isEndEvent)
    {
      elementPtr = (int*)((char*)this + 0x34);
      i = 20;
      do
      {
        // Check slot flag (bit1) and slot state == 2 (completed)
        if ((((uint)elementPtr[-2] >> 1) & 1) != 0 && *elementPtr == 2)
        {
          elementPtr[-5] = 0; // reset progress
        }
        elementPtr += 3;
        i--;
      } while (i != 0);

      // Process end time (offset 0x3e8 = 1000)
      floatVal = (float)*(int*)((char*)this + 1000);
      if (*(int*)((char*)this + 1000) < 0)
      {
        floatVal = floatVal + -0.0f;
      }
      FUN_00894e50(0x97e560ab, floatVal, 0);

      // Process another end-related value (offset 0x3ec)
      floatVal = (float)*(int*)((char*)this + 0x3ec);
      if (*(int*)((char*)this + 0x3ec) < 0)
      {
        floatVal = floatVal + -0.0f;
      }
      FUN_00894e50(0xe2b30772, floatVal, 0);

      globalObj = *(int**)(DAT_012233a0 + 4);
      if (globalObj != 0 && globalObj != (int*)0x1f30)
      {
        int checkVal2 = FUN_008c74d0(*(int*)((char*)globalObj - 0x5c));
        if (checkVal2 != 0)
        {
          FUN_008c29a0(*(undefined4*)((char*)this + 1000), 4);
        }
      }
    }

    // If debug mode flag is active, free debug string and update timed event
    if (DAT_0112a53c != 0)
    {
      FUN_00826510(&debugStrPtr); // free debug string
      FUN_007ede10((0x18 - iStack_c) * 0x3c - (int)local_8, (char*)this + 0x3f0, (char*)this + 4, 0);
    }
  }
}