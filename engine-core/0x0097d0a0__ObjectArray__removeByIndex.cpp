// FUNC_NAME: ObjectArray::removeByIndex
void __thiscall ObjectArray::removeByIndex(int param_1, int param_2)
{
    // Decrement the count of active elements (offset +0x9c)
    *(int *)(param_1 + 0x9c) = *(int *)(param_1 + 0x9c) - 1;

    // If the removed index is not the last element, swap the last element into the removed slot
    if (param_2 != *(int *)(param_1 + 0x9c)) {
        *(undefined4 *)(param_1 + 0x7c + param_2 * 4) =
            *(undefined4 *)(param_1 + 0x7c + *(int *)(param_1 + 0x9c) * 4);
    }

    // Check if all internal counters (offsets +0x78, +0x54, +0x30, +0x9c) sum to zero
    if (*(int *)(param_1 + 0x78) + *(int *)(param_1 + 0x54) + *(int *)(param_1 + 0x30) +
        *(int *)(param_1 + 0x9c) == 0) {
        // All resources released – perform global cleanup
        FUN_0097c5d0();
    }

    // If the count reached zero, release the global singleton/manager
    if (*(int *)(param_1 + 0x9c) == 0) {
        FUN_004086d0(&DAT_0112a638);
    }
}