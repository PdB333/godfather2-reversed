// FUNC_NAME: CounterManager::advanceToNextUniqueId
// Function at 0x00574170 - Calculates the next unique ID by taking the maximum of two dereferenced pointers + 1.
// Used in an ID allocation system, possibly for entity or event IDs.

void __fastcall advanceToNextUniqueId(int unused /* ECX */, CounterState* state /* EDX */)
{
    int valA;
    int valB;

    // Dereference pointer A (offset +0x08 in the state struct)
    if (state->ptrA == nullptr)
    {
        valA = -1;
    }
    else
    {
        valA = *state->ptrA;
    }

    // Dereference pointer B (offset +0x0C in the state struct)
    if (state->ptrB == nullptr)
    {
        valB = -1;
    }
    else
    {
        valB = *state->ptrB;
    }

    // Store the max+1 into the output field (offset +0x00)
    if (valA <= valB)
    {
        state->result = valB + 1;
    }
    else
    {
        state->result = valA + 1;
    }
}