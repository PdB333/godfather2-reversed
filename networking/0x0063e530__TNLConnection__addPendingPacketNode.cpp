// FUNC_NAME: TNLConnection::addPendingPacketNode

struct PacketData {
    int field_0x00;       // +0x00
    int field_0x04;       // +0x04
    int field_0x08;       // +0x08
    int field_0x0C;       // +0x0C
    int field_0x10;       // +0x10
    int field_0x14;       // +0x14
    int field_0x18;       // +0x18
    int field_0x1C;       // +0x1C
    int field_0x20;       // +0x20 (written by this function)
    int field_0x24;       // +0x24
    int field_0x28;       // +0x28
    int field_0x2C;       // +0x2C
    int field_0x30;       // +0x30
    int field_0x34;       // +0x34
    int field_0x38;       // +0x38
    int field_0x3C;       // +0x3C
    int field_0x40;       // +0x40
    char field_0x44;      // +0x44
    char field_0x45;      // +0x45
    char field_0x46;      // +0x46
    char field_0x47;      // +0x47 (written with 2)
};

struct PacketNode {
    PacketData* data;           // +0x00 (*unaff_EDI = iVar1)
    int timestamp;              // +0x04 (unaff_EDI[1] = iVar2)
    PacketNode* next;           // +0x08 (unaff_EDI[2] = connection->next)
    TNLConnection* connection;  // +0x0C (unaff_EDI[3] = param_1)
    int field_0x10;             // +0x10 (unaff_EDI[4] = connection->field_0x20)
    int field_0x14;             // +0x14 (unaff_EDI[5] = 0)
    int field_0x18;             // +0x18 (unaff_EDI[6] = 0)
    int field_0x1C;             // +0x1C (unaff_EDI[7] = 0)
    int sequence;               // +0x20 (unaff_EDI[8] = -1, likely invalid sequence)
    int field_0x24;             // +0x24 (unaff_EDI[9] = 0)
    int field_0x28;             // +0x28 (unaff_EDI[10] = 0)
    int field_0x2C;             // +0x2C (unaff_EDI[0xb] = 0)
    int field_0x30;             // +0x30 (unaff_EDI[0xc] = 0)
    int field_0x34;             // +0x34 (unaff_EDI[0xd] = 0)
};

// Allocate a new packet data buffer and initialize it
PacketData* allocatePacketData() {
    // Calls memory allocator (likely TNL malloc)
    return (PacketData*)FUN_006382f0();  // from Ghidra address 0x006382f0
}

// Get system tick count
int getTickCount() {
    return FUN_00637c50(0, 0);  // from Ghidra address 0x00637c50
}

// This function takes a node pointer in EDI (passed via __fastcall or custom convention)
// and a pointer to the connection object in param_1 (stack).
// It initializes the node and inserts it at the head of the connection's pending packet list.
void __fastcall TNLConnection::addPendingPacketNode(TNLConnection* connection, PacketNode* node) {
    // Allocate data buffer for the packet
    PacketData* data = allocatePacketData();
    
    // Initialize the node fields
    node->data = data;
    node->next = (PacketNode*)connection->pendingListHead;  // connection+0x1c
    node->connection = connection;
    node->field_0x10 = connection->field_0x20;               // connection+0x20
    connection->pendingListHead = node;                      // update head pointer
    
    node->field_0x18 = 0;
    node->field_0x1C = 0;
    node->sequence = -1;       // invalid/unsent sequence
    node->field_0x24 = 0;
    node->field_0x28 = 0;
    
    // Get current time for timestamp
    int time = getTickCount();
    
    node->field_0x2C = 0;
    node->field_0x30 = 0;
    node->field_0x34 = 0;
    node->field_0x14 = 0;
    node->timestamp = time;
    
    // Initialize fields in the data buffer
    data->field_0x20 = connection->field_0x2C;  // copy from connection
    data->field_0x47 = 2;                       // set packet type to 2 (e.g., reliable)
}