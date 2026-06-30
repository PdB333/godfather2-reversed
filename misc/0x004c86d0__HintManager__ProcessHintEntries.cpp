// FUNC_NAME: HintManager::ProcessHintEntries

int HintManager::ProcessHintEntries(int param_1)
{
  int *currentEntryPtr; // +0x0c - pointer to current hint entry (8 bytes each)
  int entryCount;       // number of entries in the buffer
  int addedCount;       // number of hints added to local list
  int entryIndex;       // loop index (starts at 2)
  float *floatPair;     // temporary pointer into local buffer
  float *hintTextStr;   // pointer to hint text string
  char *hintText;       // actual hint text string
  int *tempPtr;         // temporary pointer
  float value;          // extracted value
  int entryType;        // type of current entry
  float10 extraValue;   // extended precision float from some function
  int stringLength;     // length of hint text after processing
  float hintPairs[16];  // array of 8 float pairs (value, typeFlag)
  int pairCount;        // number of pairs stored (index into hintPairs)
  int ret;              // return value

  currentEntryPtr = *(int **)(param_1 + 0xc);
  entryCount = (int)*(int **)(param_1 + 8) - (int)currentEntryPtr >> 3;
  addedCount = 0;
  if ((currentEntryPtr < *(int **)(param_1 + 8)) && (currentEntryPtr != (int *)0x0))
  {
    if (*currentEntryPtr == 4)
    {
      hintText = (char *)(currentEntryPtr[1] + 0x10);
    }
    else
    {
      tempPtr = (int *)FUN_00633990(param_1);
      if (tempPtr == 0)
      {
        hintText = (char *)0x0;
      }
      else
      {
        hintText = (char *)(currentEntryPtr[1] + 0x10);
      }
      if (*(uint *)(*(int *)(param_1 + 0x10) + 0x20) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x24))
      {
        FUN_00627360();
      }
    }
  }
  else
  {
    hintText = (char *)0x0;
  }
  entryIndex = 2;
  hintPairs[0] = 0.0f;
  hintPairs[1] = 0.0f;
  hintPairs[2] = 0.0f;
  hintPairs[3] = 0.0f;
  hintPairs[4] = 0.0f;
  hintPairs[5] = 0.0f;
  hintPairs[6] = 0.0f;
  hintPairs[7] = 0.0f;
  hintPairs[8] = 0.0f;
  hintPairs[9] = 0.0f;
  hintPairs[10] = 0.0f;
  hintPairs[11] = 0.0f;
  hintPairs[12] = 0.0f;
  hintPairs[13] = 0.0f;
  hintPairs[14] = 0.0f;
  hintPairs[15] = 0.0f;
  pairCount = 0;
  if (1 < entryCount)
  {
    do
    {
      if (entryIndex < 1)
      {
        if (entryIndex < -9999)
        {
          if (entryIndex == -0x2711)
          {
            // Special negative index - handles invalid/out-of-range
            currentEntryPtr = (int *)(param_1 + 0x40);
          }
          else if (entryIndex == -10000)
          {
            currentEntryPtr = (int *)(*(int *)(param_1 + 0x10) + 0x2c);
          }
          else
          {
            int baseEntry = *(int *)(*(int *)(param_1 + 0xc) + -4);
            if ((int)(uint)*(byte *)(baseEntry + 7) < -0x2711 - entryIndex)
            {
              currentEntryPtr = (int *)0x0;
            }
            else
            {
              currentEntryPtr = (int *)(baseEntry + 8 + (-0x2711 - entryIndex) * 8);
            }
          }
        }
        else
        {
          currentEntryPtr = (int *)(*(int *)(param_1 + 8) + entryIndex * 8);
        }
        if (currentEntryPtr != (int *)0x0)
        {
          entryType = *currentEntryPtr;
          switch(entryType)
          {
          case 0: // Separator or empty slot
            pairCount = addedCount + 1;
            hintPairs[addedCount * 2] = 0.0f;
            hintPairs[addedCount * 2 + 1] = 0.0f;
            addedCount = pairCount;
            break;
          case 1: // Boolean/flag type
            floatPair = hintPairs + addedCount * 2;
            pairCount = addedCount + 1;
            tempPtr = (int *)FUN_00625a30(param_1, entryIndex);
            *floatPair = (float)(uint)(tempPtr != 0);
            floatPair[1] = 4.2039e-45f; // type flag 0x00000001
            addedCount = pairCount;
            break;
          case 2:
          case 7: // Numeric or text value
            if (entryIndex < 1)
            {
              tempPtr = (int *)FUN_00625430();
              if (tempPtr != (int *)0x0)
              {
                if (*tempPtr == 2)
                {
                  value = (float)tempPtr[1];
                }
                else if (*tempPtr == 7)
                {
                  value = (float)(tempPtr[1] + 0x10);
                }
                else
                {
                  value = 0.0f;
                }
              }
              else
              {
                value = 0.0f;
              }
            }
            else
            {
              tempPtr = (int *)(*(int *)(param_1 + 0xc) + -8 + entryIndex * 8);
              if (tempPtr < *(int **)(param_1 + 8))
              {
                // Re-use the same extraction logic for positive index
                if (*tempPtr == 2)
                {
                  value = (float)tempPtr[1];
                }
                else if (*tempPtr == 7)
                {
                  value = (float)(tempPtr[1] + 0x10);
                }
                else
                {
                  value = 0.0f;
                }
              }
              else
              {
                value = 0.0f;
              }
            }
            pairCount = addedCount + 1;
            hintPairs[addedCount * 2] = value;
            hintPairs[addedCount * 2 + 1] = 1.4013e-45f; // type flag 0x00000002
            addedCount = pairCount;
            break;
          case 3: // Float value (extended precision)
            floatPair = hintPairs + addedCount * 2;
            pairCount = addedCount + 1;
            extraValue = (float10)FUN_006259b0(param_1, entryIndex);
            *floatPair = (float)extraValue;
            floatPair[1] = 2.8026e-45f; // type flag 0x00000004
            addedCount = pairCount;
            break;
          case 4: // Another numeric value (integer or float)
            floatPair = hintPairs + addedCount * 2;
            pairCount = addedCount + 1;
            value = (float)FUN_00625a70(param_1, entryIndex);
            *floatPair = value;
            floatPair[1] = 5.60519e-45f; // type flag 0x00000008
            addedCount = pairCount;
            break;
          }
        }
      }
      else
      {
        currentEntryPtr = (int *)(*(int *)(param_1 + 0xc) + -8 + entryIndex * 8);
        if (currentEntryPtr < *(int **)(param_1 + 8))
        {
          // Process normally
          goto processEntry;
        }
      }
      entryIndex = entryIndex + 1;
    } while (entryIndex <= entryCount);
  }
  hintTextStr = (float *)0x0;
  // Initialize some structure members (maybe for string conversion)
  // These are likely for building the final hint text
  // local_60 and local_5e are probably part of a string structure
  if ((hintText != (char *)0x0) && (*hintText != '\0'))
  {
    stringLength = FUN_004dafd0(hintText); // possibly get length or process
    FUN_00408260(&hintTextStr, stringLength);
  }
  // Setup for building final output (maybe a UI string or tooltip)
  // local_50 is a pointer to some static table PTR_LAB_00e365dc
  // local_58 points to that table
  // local_5c points to the processed hint text float array
  // local_54 is a flag/zero
  FUN_00408a00(&hintTextStr, 0);
  FUN_00408310(&hintTextStr);
  // The number of pairs added minus something (likely bug in decompilation)
  // The original code sets ret = pairCount - addedCount, which yields 0.
  // We assume the intended return is the number of pairs processed.
  ret = pairCount;
  if (ret != 0)
  {
    FUN_004c8460(&local_50); // Display/process the built hint list
  }
  return ret;
}