// FUNC_NAME: PlayerSM::updateCounter
void __thiscall PlayerSM::updateCounter(int *this)
{
    int result;
    int *vtablePtr;
    float time;
    Vector3 position; // temporary for virtual call
    // Stack struct for condition check: 3 floats + 1 float
    struct ConditionData {
        float x, y, z;
        float w;
    } condition;

    // Check if internal data pointer is valid
    if (this[0] != 0)
    {
        // Get vtable pointer from offset -0x48 relative to data pointer
        vtablePtr = (int *)(this[0] - 0x48);
        if (vtablePtr != 0)
        {
            // Call virtual function at vtable+0x24 to get position (or similar)
            (*(void (**)(void))(vtablePtr[9]))(&position);
            // Re-fetch vtable pointer (redundant check)
            if (this[0] == 0)
                vtablePtr = 0;
            else
                vtablePtr = (int *)(this[0] - 0x48);
            // Call virtual function at vtable+0x28 to get time/speed
            time = (*(float (**)(void))(vtablePtr[10]))();
            // Reset some internal flag
            FUN_004262f0(0);
            // Pack position and time into condition struct
            condition.x = position.x;
            condition.y = position.y;
            condition.z = position.z;
            condition.w = time;
            // Check condition (returns 2 if true)
            result = FUN_004bdae0(&condition);
            if (result == 2)
            {
                // Increment counter at offset 8
                this[2]++;
                return;
            }
        }
    }
    // Reset counter if condition fails or data invalid
    this[2] = 0;
}