// FUNC_NAME: UIWindow::handleMessage
int __thiscall UIWindow::handleMessage(int *this, int param2, int param3, int param4, int messageId, int param6)
{
    if (messageId == 0x31) {
        int createdObject = createObject(); // FUN_007ab320
        this[0x1d] = createdObject; // +0x74
        if (createdObject != 0) {
            // Call virtual function at vtable+0x2c (index 11)
            (**(code **)(*this + 0x2c))(0x9c3d372f, 1, 1, 1, g_floatParam, 1.0f);
        }
        // Initialize stack string
        int stackString = g_stringData;
        int stackZero = 0;
        char stackChar = 0;
        stringCopy(&stackString, 0); // FUN_00408a00
        return 1;
    }
    if (messageId != 0x32) {
        return defaultHandler(param2, param3, param4, messageId, param6); // FUN_007abec0
    }
    destroyHandler(); // FUN_007dd8a0
    return 1;
}