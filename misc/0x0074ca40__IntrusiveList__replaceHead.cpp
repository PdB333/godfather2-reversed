// FUNC_NAME: IntrusiveList::replaceHead
void __thiscall IntrusiveList::replaceHead(void* param_1, void* param_2)
{
    // +0x14: pointer to the first node (head)
    void** ppHead = reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(param_1) + 0x14);
    if (*ppHead != param_2) {
        if (*ppHead != nullptr) {
            // +0x14: remove old head from its list (likely detach node)
            FUN_004daf90(ppHead);
        }
        *ppHead = param_2;
        if (param_2 != nullptr) {
            // +0x18: store the previous head's link (next of the old head?) from param_2's internal pointer at +0x4
            *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(param_1) + 0x18) = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(param_2) + 0x4);
            // Set param_2's +0x4 to point to the head pointer (makes param_2's next link point back to the list head)
            *reinterpret_cast<void***>(reinterpret_cast<uint8_t*>(param_2) + 0x4) = ppHead;
        }
    }
}