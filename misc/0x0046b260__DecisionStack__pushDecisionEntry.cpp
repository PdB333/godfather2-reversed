// FUNC_NAME: DecisionStack::pushDecisionEntry
// 0x0046b260: Member function that evaluates two internal metrics (via getMetric(1) and getMetric(2)) and pushes a decision entry onto a stack.
// The stack is an array of 8-byte pairs (two ints) pointed to by offset +0x8 in this. The first pair element is always 1 (a flag),
// the second is 1 if metric1 < metric2, else 0. The internal stack pointer is advanced by 8 bytes after storing.
// Returns 1 always.

int DecisionStack::pushDecisionEntry() {
    int metric1 = getMetric(1);   // FUN_0046af90(1)
    int metric2 = getMetric(2);   // FUN_0046af90(2)
    int* stackPtr = *(int**)(this + 8); // +0x8: pointer to current position in stack of pairs
    stackPtr[0] = 1;                     // first int in pair: constant 1 (entry type flag)
    stackPtr[1] = (metric1 < metric2) ? 1 : 0; // comparison result
    *(int**)(this + 8) = stackPtr + 2;   // move stack pointer forward by 8 bytes (2 ints)
    return 1;
}