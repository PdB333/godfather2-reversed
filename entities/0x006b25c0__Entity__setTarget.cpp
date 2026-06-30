// FUNC_NAME: Entity::setTarget

void __thiscall Entity::setTarget(int thisPtr, int target)
{
    // Compare current target at offset 0xD8 (likely m_pTarget)
    if (*(int *)(thisPtr + 0xD8) != target)
    {
        // Update target pointer
        *(int *)(thisPtr + 0xD8) = target;

        // If new target is valid, perform type-dependent focus setup
        if (target != 0)
        {
            // Check class type hash at offset 0x40 (0x637b907 == Player type)
            if (*(int *)(thisPtr + 0x40) == 0x637b907)
            {
                // Player-specific target handling (e.g., set focus level 2)
                FUN_00898480(target, 2);
            }
            else
            {
                // Generic NPC/vehicle target handling (focus level 2)
                FUN_008982e0(target, 2);
            }
        }
    }
}