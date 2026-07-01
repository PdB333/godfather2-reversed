// FUNC_NAME: SimNpc::evaluateHealthLevel
int __thiscall SimNpc::evaluateHealthLevel(SimNpc *this)
{
    // Virtual call at vtable+0x270, returns a byte representing the health/intensity level.
    // Returns a simplified category: 0 = low (<4), 1 = medium (==4), 2 = high (>4).
    byte level = (*(byte (__thiscall **)(SimNpc *))( * (int *)this + 0x270))(this);
    if (level < 4)
        return 0;   // Low
    if (level == 4)
        return 1;   // Medium
    return 2;        // High
}