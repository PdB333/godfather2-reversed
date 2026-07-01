//FUNC_NAME: ComparisonCondition::evaluate
// Address: 0x00901fb0
// Role: Evaluates a comparison condition with threshold and bitmask flags, then triggers an action if conditions are met.

void __thiscall ComparisonCondition::evaluate(int thisPtr, int* conditionData)
{
    float value1;
    float value2;
    int* someObject;
    int* manager;
    int contextObject;
    uint flags;
    uint hashResult;
    int basePtr;
    float10 tempFloat;

    // Check initial conditions: conditionData[0] must match this+0x14, conditionData[1] must be non-null and its +4 offset non-null
    if ((conditionData[0] == *(int*)(thisPtr + 0x14)) &&
        (someObject = (int*)conditionData[1], someObject != nullptr) &&
        (*(int*)(someObject + 4) != nullptr) &&
        ((basePtr = *(int*)(someObject + 4) - 0x48, basePtr != 0) &&
         (manager = (int*)FUN_0043b870(DAT_01131018), manager != nullptr)))
    {
        // Get two values from the manager's virtual functions
        tempFloat = (**(float10 (__thiscall**)(int*))(*manager + 0x28))(manager);
        value1 = (float)tempFloat;
        tempFloat = (**(float10 (__thiscall**)(int*))(*manager + 0x2c))(manager);
        value2 = (float)tempFloat;

        flags = *(uint*)(thisPtr + 0x28);
        // Check comparison mode: bit 0 = less, bit 1 = equal, bit 2 = greater
        if ((((flags & 1) != 0) && (value1 < *(float*)(thisPtr + 0x24) * value2)) ||
            (((flags & 2) != 0) && (value1 == *(float*)(thisPtr + 0x24) * value2)) ||
            (((flags & 4) != 0) && (*(float*)(thisPtr + 0x24) * value2 < value1)))
        {
            contextObject = (**(int (__thiscall**)(int*))(*manager + 0x34))(manager);
            flags = FUN_0084d420(*(undefined4*)(contextObject + 0x30));
            // Check bitmask at this+0x2c
            if ((*(uint*)(thisPtr + 0x2c) & flags) != 0)
            {
                // If byte flag at this+0x30 bit 0 is set, perform hash validation
                if ((*(byte*)(thisPtr + 0x30) & 1) != 0)
                {
                    hashResult = FUN_0046a1f0(basePtr, 0x38523fc3, 0x383225a1); // hash constants for condition validation
                    basePtr = FUN_0084daa0(hashResult);
                    if (basePtr == 0)
                    {
                        return;
                    }
                }
                // Trigger action: pass this+0x1c, someObject, and 0
                FUN_0045c400(thisPtr + 0x1c, someObject, 0);
            }
        }
    }
    return;
}