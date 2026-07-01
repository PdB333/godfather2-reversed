// FUNC_NAME: LinkedListIterator::advance
int* __fastcall LinkedListIterator::advance(int* param_1) // this in ECX
{
    // Check that the list container is valid (pointer at +0x00)
    if (*param_1 == 0) {
        debugAssert(); // FUN_00b97aea - assertion failure
    }
    // Check that we haven't reached the tail (list container's tail pointer at +0x18)
    if (param_1[1] == *(int*)(*param_1 + 0x18)) {
        debugAssert(); // FUN_00b97aea - assertion failure: advancing past end
    }
    // Advance to the next node in the singly-linked list (node->next)
    param_1[1] = *(int*)param_1[1];
    return param_1;
}