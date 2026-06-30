// FUNC_NAME: TNLConnection::comparePacketSequence
bool __fastcall TNLConnection::comparePacketSequence(int *this, int *other)
{
    // +0x2C (0x0B*4): flags field (bit 5 = 0x20 indicates extended sequence)
    // +0x14 (0x05*4): sequence number (standard)
    // +0x1C (0x07*4): sequence number (extended)
    // +0x00: packet type/version field

    uint thisExtended = this[0x0B] & 0x20;
    int thisSeq;
    if ((thisExtended == 0) || (this[0] < 2)) {
        thisSeq = this[5];  // standard sequence
    } else {
        thisSeq = this[7];  // extended sequence
    }

    uint otherExtended = other[0x0B] & 0x20;
    int otherSeq;
    if ((otherExtended == 0) || (other[0] < 2)) {
        otherSeq = other[5];  // standard sequence
    } else {
        otherSeq = other[7];  // extended sequence
    }

    if (thisSeq == otherSeq) {
        // Same sequence - check if this is newer based on extended flag
        int thisNewer;
        if ((thisExtended == 0) || (this[0] < 4)) {
            thisNewer = 0;
        } else {
            thisNewer = this[5];
        }
        // Return true if this is newer (negative comparison trick)
        return (thisNewer < 0);
    } else {
        // Different sequences - determine which is newer
        int thisCompare;
        if ((thisExtended == 0) || (this[0] < 2)) {
            thisCompare = this[5];
        } else {
            thisCompare = this[7];
        }

        if ((otherExtended != 0) && (1 < other[0])) {
            return (thisCompare < other[7]);
        }
        return (thisCompare < other[5]);
    }
}