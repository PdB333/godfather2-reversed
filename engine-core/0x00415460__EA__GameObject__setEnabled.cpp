// FUNC_NAME: EA::GameObject::setEnabled
void __thiscall EA::GameObject::setEnabled(int param_1, char param_2)
{
    // param_1: this pointer (GameObject)
    // param_2: bool enable (0 = disable, nonzero = enable)
    // m_pSubObject at +0x20
    int* pSubObject = *(int**)(param_1 + 0x20);
    if (pSubObject != nullptr) {
        if (param_2 == 0) { // disable
            if (pSubObject != nullptr) {
                // Unlink/remove from manager (hash 0x79c328b9)
                FUN_0051cbc0(pSubObject, 0x79c328b9, 0);
            }
            if (pSubObject != nullptr) {
                // Set bit 0x20000000 in flags at +0x0C
                uint* flags = (uint*)(pSubObject + 0xC);
                *flags |= 0x20000000;
            }
        } else { // enable
            if (pSubObject != nullptr) {
                // Clear bit 0x20000000 in flags
                uint* flags = (uint*)(pSubObject + 0xC);
                *flags &= 0xDFFFFFFF;
            }
        }
    }
}