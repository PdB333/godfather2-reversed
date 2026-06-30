// FUNC_NAME: Iterator::advance
void __fastcall Iterator::advance(int* param_1)
{
    // param_1 points to the iterator's current node pointer (e.g., "current" member).
    // The node structure: offset 0 = data, offset 4 = next pointer.
    // This advances the iterator to the next node in the linked list.
    *param_1 = *(int*)(*param_1 + 4);
}