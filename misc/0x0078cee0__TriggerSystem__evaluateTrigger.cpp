// FUNC_NAME: TriggerSystem::evaluateTrigger
void __thiscall TriggerSystem::evaluateTrigger(int *param_2)
{
    int object;

    // Some validation/preprocessing on the input parameter
    FUN_0046c6a0(param_2);

    // Check if the input value matches the stored trigger ID (this+0x14)
    // and if any of the four state flags (this+0x2c,0x30,0x34,0x38) are non-zero
    if ((*param_2 == *(this + 0x14)) &&
        ((((*(int *)(this + 0x2c) != 0 || *(int *)(this + 0x30) != 0) ||
          *(int *)(this + 0x34) != 0) || *(int *)(this + 0x38) != 0)))
    {
        // Try to find an object in the primary list (offset 0x2c)
        object = FUN_00446100(this + 0x2c, 0);
        if (object != 0)
        {
            // If found, search in the secondary list (offset 0x1c)
            object = FUN_00446100(this + 0x1c, 0);
            if (object != 0)
            {
                // Execute the specific action on the found object
                FUN_0078fc20(object);
                return;
            }
            // Fallback: execute default action if secondary list empty
            FUN_0078f5f0();
        }
    }
    // else nothing: condition not met or primary list empty
}