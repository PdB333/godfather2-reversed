// FUNC_NAME: SomeManager::findMatchingElement
int __fastcall SomeManager::findMatchingElement(void* this) {
    int* pNode = reinterpret_cast<int*>(this) + 0x58 / 4; // +0x58: embedded node (4 ints: next, prev, data, etc.)
    int result = 0;

    // Check if the node list is non-empty and not a sentinel
    // Sentinels are identified by specific negative constants (e.g., 0xBBADBABA, 0xBEEFBEEF, etc.)
    bool listNonEmpty = (pNode[0] != 0 || pNode[1] != 0 || pNode[2] != 0 || pNode[3] != 0);
    bool isSentinel = (pNode[0] == -0x45245246 && pNode[1] == -0x41104111 && pNode[2] == -0x153ea5ab && pNode[3] == -0x6eeff6ef);
    if (listNonEmpty && !isSentinel) {
        result = getFirstNode(pNode, 0); // FUN_00446100: get first element from list
        while (result != 0) {
            // Check if bit 3 of some flag at +0x108 is clear; if so stop searching
            if (((*(uint*)(reinterpret_cast<char*>(this) + 0x108) >> 3) & 1) == 0) {
                break;
            }
            // Compare the result of getCurrentCondition (FUN_0043b490) with a stored comparison value at +0x150
            // If they match, stop; otherwise continue to next
            if (getCurrentCondition() == *(int*)(reinterpret_cast<char*>(this) + 0x150)) { // +0x150: comparison value
                break;
            }
            result = getNextNode(pNode, result); // FUN_00446100: get next element
        }
    }
    return result;
}