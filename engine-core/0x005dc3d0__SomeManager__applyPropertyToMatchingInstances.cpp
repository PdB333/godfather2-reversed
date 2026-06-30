// FUNC_NAME: SomeManager::applyPropertyToMatchingInstances
int __thiscall SomeManager::applyPropertyToMatchingInstances(int param_1, undefined4 param_2)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    undefined4 *in_EAX;
    undefined1 *puVar5;
    undefined4 *puVar6;
    
    iVar4 = param_1;
    puVar5 = (undefined1 *)*in_EAX; // +0x00: m_identifierString
    if (puVar5 == (undefined1 *)0x0) {
        puVar5 = &DAT_0120546e; // default string
    }
    param_1 = GetIdFromString(puVar5); // Convert string to integer ID (key)
    if (*(int *)(iVar4 + 0xc) != 0) { // +0x0c: m_extraData
        puVar6 = (undefined4 *)GetValueBuffer(&param_1); // Allocate/get storage for the ID
        *puVar6 = param_2;
    }
    iVar1 = *(int *)(iVar4 + 8); // +0x08: m_head (first node)
    if ((iVar1 != 0) && (*(int *)(iVar4 + 4) != 0)) { // +0x04: m_nodeCount or m_active
        iVar2 = **(int **)(iVar1 + 0x1c); // Node::m_next (double indirect? actually node->next->next?)
        while( true ) {
            iVar3 = *(int *)(*(int *)(iVar4 + 8) + 0x1c); // head->m_next
            if ((iVar1 == 0) || (iVar1 != *(int *)(iVar4 + 8))) {
                Assert(); // node or head mismatch
            }
            if (iVar2 == iVar3) break; // wrapped around
            if (iVar1 == 0) {
                Assert();
            }
            if (iVar2 == *(int *)(iVar1 + 0x1c)) {
                Assert();
            }
            if (*(int *)(*(int *)(iVar2 + 0x10) + 0x2b4) == param_1) { // Target::m_keyId at +0x2b4 (in object pointed by node->m_target)
                if (iVar2 == *(int *)(iVar1 + 0x1c)) {
                    Assert();
                }
                *(undefined4 *)(*(int *)(iVar2 + 0x10) + 0x29c) = param_2; // Set Target::m_value at +0x29c
            }
            YieldOrNext(); // Advance iteration (likely updates iVar1/iVar2 internally)
        }
        return 1;
    }
    return 0;
}