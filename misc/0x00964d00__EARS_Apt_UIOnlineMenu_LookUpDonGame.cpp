// Xbox PDB: EARS_Apt_UIOnlineMenu_LookUpDonGame
// FUNC_NAME: DonControlManager::onReceiveDonRequest
void __thiscall DonControlManager::onReceiveDonRequest(int *this, undefined4 param_2, undefined4 param_3)
{
    // Set flag 0x4000 on the don request state at offset +0x1bd (4-byte field).
    // This marks that a don request has been received.
    this[0x1bd] = this[0x1bd] | 0x4000;

    // If the global DAT_01223484 (likely a flag indicating online/multiplayer mode) is nonzero,
    // proceed to play a notification sound and send acknowledgement.
    if (DAT_01223484 != 0) {
        // Call vtable function at offset +0x0c (likely playSound or notifyUI).
        (**(code **)(*this + 0xc))();

        // Display a chat/UI message indicating a don request was received.
        FUN_00983120("$mp_online_receive_don_request", 0, 0);

        // Send an acknowledgement or process the received request data.
        FUN_008a2cc0(param_2, param_3);
    }
    return;
}