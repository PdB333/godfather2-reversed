// FUNC_NAME: InputDeviceManager::~InputDeviceManager
void __fastcall InputDeviceManager::~InputDeviceManager(int *this)
{
    cleanupGlobalLists();    // FUN_008a4dc0 - static cleanup of global lists
    releaseObject(this[5]);  // FUN_009c8f10 - release member at offset +0x14
    int *node = (int *)*this; // head of linked list at +0x00
    if (node != (int *)0) {
        releaseObject(*(int *)(node + 2)); // FUN_009c8f10 - release node->m_pChild at +0x08
        releaseNode(node);                  // FUN_009c8eb0 - free the node
    }
}