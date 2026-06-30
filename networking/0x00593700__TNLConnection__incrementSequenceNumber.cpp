// FUNC_NAME: TNLConnection::incrementSequenceNumber

void __fastcall TNLConnection::incrementSequenceNumber(TNLConnection* this)
{
    if (this != 0 && (this->field_0x13 & 1) != 0) {
        // active connection: increment local sequence number with window mask
        this->field_0x2d4 = (this->field_0x2d4 + 1) & g_sequenceMask; // g_sequenceMask = DAT_010c2678
        return;
    }
    // inactive or null: increment global fallback sequence counter
    g_globalSequenceCounter++; // DAT_012054b4
    return;
}