// FUNC_NAME: Entity::Register
void __thiscall Entity::Register(int param_1)
{
    // Store the passed parameter (likely an ID or pointer) at offset 0x20
    *(int *)(this + 0x20) = param_1;

    // Global constant (e.g., some type flag or size)
    int globalConstant = DAT_011260b4;

    // Get the pointer to the insertion index from a global manager (DAT_01206880 + 0x14)
    int **ppInsert = (int **)(DAT_01206880 + 0x14);

    // Write vtable pointer for the new node in the linked list
    *(*ppInsert) = (int)&PTR_LAB_0112611c;
    (*ppInsert)++; // Advance

    // Write the passed parameter
    *(*ppInsert) = param_1;
    (*ppInsert)++; // Advance

    // Write the global constant
    *(*ppInsert) = globalConstant;
    (*ppInsert)++; // Advance (pointer left at next free slot)
}