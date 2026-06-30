// FUNC_NAME: NodeChain::relinkChain
// Address: 0x00626640
// This function traverses a chain of nodes (linked via offset +0x8) and inserts each node
// into one of four bucket lists based on the node's type field (+0x4, values 5-8).
// The chain is terminated when the next node's flags field (+0x5) has bit 4 set (0x10).
// The head pointer of each list is updated via the second parameter.
// Node layout:
//   +0x00: (unknown)
//   +0x04: type (5-8)
//   +0x05: flags (bit0 = 1: processed, bit4 = 1: chain end)
//   +0x08: nextA (chain pointer for traversal and for list A)
//   +0x18: nextB (list B)
//   +0x40: nextC (list C)
//   +0x4c: nextD (list D)

void __fastcall NodeChain::relinkChain(Node* this, Node** headPtr)
{
    Node* node = this;
    while (true)
    {
        node->flags |= 1; // mark as processed

        // Determine which list to insert into based on type (5-8)
        uint typeIndex = node->type - 5;
        if (typeIndex <= 4)
        {
            Node* oldHead = *headPtr;

            switch (typeIndex)
            {
            case 0: // type 5 -> list A (+0x8)
                node->nextA = oldHead;
                break;
            case 1: // type 6 -> list B (+0x18)
                node->nextB = oldHead;
                break;
            case 2: // type 7 -> list C (+0x4c)
                node->nextC = oldHead;
                break;
            case 3: // type 8 -> list D (+0x40)
                node->nextD = oldHead;
                break;
            // case 4 (type 9) is not handled; falls through (no insertion)
            }

            *headPtr = node; // update head to current node
        }

        Node* next = node->nextA; // advance along the chain

        // Check if next node is the chain terminator (flag bit4 set)
        if (next->flags & 0x10)
            break;

        // Prepare next node for processing
        next->flags |= 1;
        uint nextTypeIndex = next->type - 5;
        if (nextTypeIndex > 4)
            break; // invalid type, stop

        node = next; // continue with next node
    }
}