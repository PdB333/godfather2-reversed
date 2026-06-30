// FUNC_NAME: PacketList::insertAfter
void PacketList::insertAfter(PacketNode* targetNode)
{
    // this->head is DAT_0119cbbc (global head pointer)
    bool notHead = (this != head); // unaff_ESI != DAT_0119cbbc

    // Set forward/backward links
    this->next = targetNode->next; // this->next at +0x60
    this->prev = targetNode;       // this->prev at +0x5C

    if (notHead)
    {
        uint flags = *this->flags; // flags at +0x00
        uint masked = flags & 0x7FFF; // lower 15 bits
        if ((masked != 0x19) &&
            (( ((flags >> 0xF) & 1) == 0) || // bit 15 clear OR
             ((masked != 0xB && masked != 0x18 && masked != 0x17)))))
        {
            // Update state for nodes that are not special types
            updateNodeState(this); // FUN_0059c230
        }
    }

    // Fix neighbors' links
    if (this->next != nullptr)
    {
        this->next->prev = this; // +0x5C of next
    }
    targetNode->next = this; // +0x60 of target
}