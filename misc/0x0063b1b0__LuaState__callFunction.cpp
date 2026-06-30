// FUNC_NAME: LuaState::callFunction
unsigned int LuaState::callFunction(int state)
{
  int *stackTop = *(int **)(state + 0xc);
  int *stackBase = *(int **)(state + 8);
  int *envPtr = *(int **)(state + 0x10);

  if (stackTop >= stackBase || stackTop == nullptr) {
    **(int **)(state + 8) = 0;
    *(int *)(state + 8) += 8;
    return 1;
  }

  if (*stackTop == 7) { // Type 7: C function (or userdata with metatable)
    // Handle method call: push "tolua_peer" to get C++ object
    pushString(state, "tolua_peer");
    removeFromStack(state); // Remove the previous value? (FUN_00625e70)

    // Copy the two stack slots (function and upvalues?) from old top to base
    *((int *)(state + 8)) = **((int **)(state + 8)); // Actually copy values
    *(((int *)(state + 8)) + 1) = *(stackTop + 1);
    *(int *)(state + 8) += 8;
    removeFromStack(state); // Another pop

    // Check next slot for type 5 (string?) and push another pair
    int *nextSlot = *(int **)(state + 8);
    if (nextSlot - 2 != nullptr && *(nextSlot - 2) == 5) {
      int basePtr = *(int *)(state + 0xc);
      *nextSlot = *(int *)(basePtr + 8);
      *(nextSlot + 1) = *(int *)(basePtr + 0xc);
      *(int *)(state + 8) += 8;
      removeFromStack(state);
      nextSlot = *(int **)(state + 8);
      if (nextSlot - 2 == nullptr || *(nextSlot - 2) != 0) {
        return 1;
      }
    }

    // Pad with zeros up to base+0x10
    int *target = *(int **)(state + 8);
    int limit = *(int *)(state + 0xc) + 0x10;
    while ((unsigned int)target < (unsigned int)limit) {
      **(int **)(state + 8) = 0;
      *(int *)(state + 8) += 8;
      target = *(int **)(state + 8);
    }

    // Copy first two slots to the new base+4 and advance
    int *oldBase = *(int **)(state + 0xc);
    *(int **)(state + 8) = oldBase + 4;
    *(oldBase + 4) = *oldBase;
    *(oldBase + 5) = *(oldBase + 1);
    *(int *)(state + 8) += 8;

    // Now iterate through the stack, converting arguments
    while (true) {
      int *current = *(int **)(state + 8);
      if (current - 2 == nullptr) break;

      int type = *(current - 2);
      int value;
      if (type == 5) {
        value = *(int *)(*(current - 1) + 8);
      } else if (type == 7) {
        value = *(int *)(*(current - 1) + 8);
      } else {
        break;
      }

      if (value == 0 || value == *(int *)(*(int *)(state + 0x10) + 0x38)) break;

      *current = 5;      // Convert to type 5 (maybe string?)
      *(current + 1) = value;
      *(int *)(state + 8) += 8;

      // Shift stack elements (removing one)
      int *src = *(int **)(state + 8) - 2;
      for (int *dst = src; dst < *(int **)(state + 8); dst++) {
        *dst = *(dst + 2);
        *(dst + 1) = *(dst + 3);
      }
      *(int *)(state + 8) -= 8;

      // Check for index operation: if top is type 3 or 4 and condition, do .geti
      int *check = (int *)(*(int *)(state + 0xc) + 8);
      if (check < *(int **)(state + 8) && check != nullptr &&
          (*check == 3 || (*check == 4 && checkCondition(check)))) {
        pushString(state, ".geti");
        int topVal = *(int *)(state + 8);
        int topType = *(int *)(topVal - 8);
        int *newVal;
        if (topType == 3) {
          if ((float)(int)*(float *)(topVal - 4) != *(float *)(topVal - 4))
            newVal = (int *)convertToNumber(); // FUN_00637ea0
          else
            newVal = (int *)convertToBoolean(); // FUN_00637f10
        } else if (topType == 4) {
          newVal = (int *)convertToString(); // FUN_00637f90
        } else {
          newVal = (int *)convertToNumber();
        }
        *(int *)(topVal - 8) = *newVal;
        *(int *)(topVal - 4) = newVal[1];
        int funcType = getFuncType(); // FUN_00625740
        if (funcType == 6) {
          // Duplicate function arguments and call
          int *oldBase = *(int **)(state + 0xc);
          int *stack = *(int **)(state + 8);
          *stack = *oldBase;
          *(stack + 1) = *(oldBase + 1);
          int oldC = *(int *)(state + 0xc);
          *(int *)(state + 8) += 8;
          stack = *(int **)(state + 8);
          *stack = *(int *)(oldC + 8);
          *(stack + 1) = *(int *)(oldC + 0xc);
          *(int *)(state + 8) += 8;
          callStackFunction(state, *(int *)(state + 8) - 0x18, 1); // FUN_006362d0
          return 1;
        }
      } else {
        // No .geti, directly convert and check
        int base = *(int *)(state + 0xc);
        int *stack = *(int **)(state + 8);
        *stack = *(int *)(base + 8);
        *(stack + 1) = *(int *)(base + 0xc);
        *(int *)(state + 8) += 8;
        int valIdx = *(int *)(state + 8);
        int valType = *(int *)(valIdx - 8);
        int *conv;
        if (valType == 3) {
          if ((float)(int)*(float *)(valIdx - 4) != *(float *)(valIdx - 4))
            conv = (int *)convertToNumber();
          else
            conv = (int *)convertToBoolean();
        } else if (valType == 4) {
          conv = (int *)convertToString();
        } else {
          conv = (int *)convertToNumber();
        }
        *(int *)(valIdx - 8) = *conv;
        *(int *)(valIdx - 4) = conv[1];
        int result = getFuncType(); // FUN_00625740
        if (result != 0) return 1;

        // If not, try .self method call
        *(int *)(state + 8) -= 8;
        pushString(state, ".self");
        int top = *(int *)(state + 8);
        int tType = *(int *)(top - 8);
        int *selfVal;
        if (tType == 3) {
          if ((float)(int)*(float *)(top - 4) != *(float *)(top - 4))
            selfVal = (int *)convertToNumber();
          else
            selfVal = (int *)convertToBoolean();
        } else if (tType == 4) {
          selfVal = (int *)convertToString();
        } else {
          selfVal = (int *)convertToNumber();
        }
        *(int *)(top - 8) = *selfVal;
        *(int *)(top - 4) = selfVal[1];
        int selfCheck = getFuncType(); // FUN_00625740
        if (selfCheck == 5) {
          // Get the object (userdata or C function)
          int *base = *(int **)(state + 0xc);
          int *selfObj;
          if (base < *(int **)(state + 8) && base != nullptr) {
            if (*base == 2) {
              selfObj = (int *)base[1];
            } else if (*base == 7) {
              selfObj = (int *)(base[1] + 0x10);
            } else {
              selfObj = nullptr;
            }
          } else {
            selfObj = nullptr;
          }
          unsigned int selfValue = *selfObj;
          removeTop(state); // FUN_00625f40
          pushString(state, ".self");
          int *stack = *(int **)(state + 8);
          *(stack + 1) = selfValue;
          *stack = 2; // Type 2: object
          *(int *)(state + 8) += 8;
          int idx = *(int *)(state + 8);
          int *newStack = getStackPointer(state, *(int *)(idx - 0x14)); // FUN_00638020
          *newStack = *(int *)(idx - 8);
          *(newStack + 1) = *(int *)(idx - 4);
          *(int *)(state + 8) -= 0x10;
          // Reorder stack
          int *src = *(int **)(state + 8);
          for (int *dst = src; src + 4 < dst; dst -= 2) {
            *dst = dst[-2];
            *(dst + 1) = dst[-1];
          }
          int *first = *(int **)(state + 8);
          *(src - 4) = *first;
          *(src - 3) = first[1];
          popStack(state); // FUN_00626130
          // Copy the object and function back
          int *stack2 = *(int **)(state + 8);
          *stack2 = stack2[-2];
          *(stack2 + 1) = stack2[-1];
          *(int *)(state + 8) += 8;
          int baseIdx = *(int *)(state + 0xc);
          int *stack3 = *(int **)(state + 8);
          *stack3 = *(int *)(baseIdx + 8);
          *(stack3 + 1) = *(int *)(baseIdx + 0xc);
          *(int *)(state + 8) += 8;
          // Reorder again
          int *src2 = *(int **)(state + 8);
          for (int *dst2 = src2; src2 + 4 < dst2; dst2 -= 2) {
            *dst2 = dst2[-2];
            *(dst2 + 1) = dst2[-1];
          }
          int *first2 = *(int **)(state + 8);
          *(src2 - 4) = *first2;
          *(src2 - 3) = first2[1];
          callMethod(state); // FUN_0063abc0
          return 1;
        }
      }

      // Ensure stack is padded to base+0x18
      if ((unsigned int)*(int *)(state + 8) < *(int *)(state + 0xc) + 0x18U) {
        do {
          **(int **)(state + 8) = 0;
          *(int *)(state + 8) += 8;
        } while ((unsigned int)*(int *)(state + 8) < *(int *)(state + 0xc) + 0x18U);
      }
      *(int *)(state + 8) = *(int *)(state + 0xc) + 0x18;
    }

    // Push a zero value and return
    **(int **)(state + 8) = 0;
    *(int *)(state + 8) += 8;
    return 1;
  }

  if (*stackTop == 5) { // Type 5: function (direct call)
    callDirect(state); // FUN_0063ad70
    return 1;
  }

  // Default: push a zero and return
  **(int **)(state + 8) = 0;
  *(int *)(state + 8) += 8;
  return 1;
}