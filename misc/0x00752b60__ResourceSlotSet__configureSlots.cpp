// FUNC_NAME: ResourceSlotSet::configureSlots
// Address: 0x00752b60
// This function sets two internal resource slots (A and B) from provided source structs,
// copies associated data into larger storage, and optionally calls a setup function.
// It manages intrusive linked list nodes: each slot holds a pointer to a node, and nodes
// have a back-pointer at offset +4 pointing to the slot. Reference counting is handled via FUN_004daf90.
// Offsets (relative to this):
//   +0x5c : int flag (param_2)
//   +0x60 : int* slotA (pointer to node)
//   +0x64 : int (set to nodeA->+4)
//   +0x68 : int* dataA (source data pointer, from param_3[2])
//   +0x6c : int* slotB
//   +0x70 : int (set to nodeB->+4)
//   +0x74 : int* dataB (source data pointer, from param_4[2])
//   +0xa4 : undefined8 copy0 from dataA[0..1]
//   +0xac : undefined4 copy1 from dataA[2]? (actually *(puVar4+1))
//   +0xb0 : undefined8 copy0 from dataB[0..1]
//   +0xb8 : undefined4 copy1 from dataB[2]
//   +0xbc : undefined8 duplicate copy0 from dataB[0..1]
//   +0xc4 : undefined4 duplicate copy1 from dataB[2]

void __thiscall ResourceSlotSet::configureSlots(int thisPtr, int flag, int* sourceA, int* sourceB)
{
  int* slotAPtr;   // actually pointer to slot field at this+0x60
  int* slotBPtr;   // pointer to slot field at this+0x6c
  int oldNodeA;
  int oldNodeB;
  int newNodeA;
  int newNodeB;
  int** dataA;     // pointer to dataA field (this+0x68)
  int** dataB;     // pointer to dataB field (this+0x74)
  int* rawDataA;   // pointer to the actual data (from sourceA[2])
  int* rawDataB;   // pointer to the actual data (from sourceB[2])

  // Store the flag
  *(int*)(thisPtr + 0x5c) = flag;

  // --- Slot A handling ---
  slotAPtr = (int*)(thisPtr + 0x60); // points to slotA value
  if (slotAPtr != sourceA)   // ensure not same pointer (unlikely)
  {
    newNodeA = *sourceA;              // candidate new node pointer
    if (*slotAPtr != newNodeA)        // only update if different
    {
      if (*slotAPtr != 0)            // release old node if exists
      {
        FUN_004daf90(slotAPtr);      // release reference via slot pointer
      }
      *slotAPtr = newNodeA;
      if (newNodeA != 0)             // link back to slot
      {
        *(int*)(thisPtr + 0x64) = *(int*)(newNodeA + 4); // save node back pointer?
        *(int**)(newNodeA + 4) = slotAPtr;               // set node's back pointer to slot
      }
    }
  }

  // --- Slot B handling ---
  slotBPtr = (int*)(thisPtr + 0x6c);
  *(int*)(thisPtr + 0x68) = sourceA[2]; // store data pointer for slot A
  if (slotBPtr != sourceB)
  {
    newNodeB = *sourceB;
    if (*slotBPtr != newNodeB)
    {
      if (*slotBPtr != 0)
      {
        FUN_004daf90(slotBPtr);
      }
      *slotBPtr = newNodeB;
      if (newNodeB != 0)
      {
        *(int*)(thisPtr + 0x70) = *(int*)(newNodeB + 4); // save node back pointer?
        *(int**)(newNodeB + 4) = slotBPtr;
      }
    }
  }

  // Store data pointer for slot B
  *(int*)(thisPtr + 0x74) = sourceB[2];

  // If slot A is active, copy its associated data into this+0xa4/0xac
  if (*slotAPtr != 0)
  {
    rawDataA = *(int**)(thisPtr + 0x68); // get data pointer stored earlier
    *(undefined8*)(thisPtr + 0xa4) = *(undefined8*)rawDataA;          // copy 8 bytes
    *(undefined4*)(thisPtr + 0xac) = *(undefined4*)(rawDataA + 2);    // copy next 4 bytes (actually offset 8)
    // Note: rawDataA is int*, so +2 means +8 bytes from original.

    // If slot B is also active, copy its data into two locations
    if (*slotBPtr != 0)
    {
      rawDataB = *(int**)(thisPtr + 0x74);
      // First copy at +0xb0/+0xb8
      *(undefined8*)(thisPtr + 0xb0) = *(undefined8*)rawDataB;
      *(undefined4*)(thisPtr + 0xb8) = *(undefined4*)(rawDataB + 2);
      // Duplicate copy at +0xbc/+0xc4 (possibly for different purpose)
      *(undefined8*)(thisPtr + 0xbc) = *(undefined8*)rawDataB;
      *(undefined4*)(thisPtr + 0xc4) = *(undefined4*)(rawDataB + 2);

      // If flag == 1, call the setup function with node pointers and data pointers
      if (flag == 1)
      {
        FUN_00752ad0(*slotAPtr, rawDataA, *slotBPtr, rawDataB);
      }
    }
  }
  return;
}