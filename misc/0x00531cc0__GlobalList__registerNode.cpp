// FUNC_NAME: GlobalList::registerNode

// Address: 0x00531cc0
// This function appears to be a constructor/initializer for a global node that registers 
// itself into a singly-linked list. It calls two virtual methods (at offsets 4 and 0x10) 
// and then links the node into a global head pointer (DAT_012058ec).
// The structure at DAT_0121bc10 holds:
//   +0x00: ??? (not used directly here, likely vtable or other data)
//   +0x04: function pointer (first call) -> returned value used as argument to FUN_0060d740
//   +0x08: result of FUN_0060d740 (some handle/id)
//   +0x0C: counter (DAT_012058f8)
//   +0x10: function pointer (second call)
//   +0x14: next pointer pointing to previous head (DAT_012058ec)

void GlobalList::registerNode(void)
{
    undefined4 handle;

    // Call first virtual method at offset 4 from the global node structure.
    handle = (*(code **)(DAT_0121bc10 + 4))();

    // Convert the result using some registration function.
    _DAT_0121bc18 = FUN_0060d740(handle);

    // Call second virtual method at offset 0x10.
    (*(code **)(DAT_0121bc10 + 0x10))();

    // Store the old global head into the node's "next" field (+0x14).
    _DAT_0121bc14 = DAT_012058ec;

    // Increment global counter.
    DAT_012058f8 = DAT_012058f8 + 1;

    // Set global head to point to this node.
    DAT_012058ec = &DAT_0121bc10;

    // Store the counter value into the node's counter field (+0x0C).
    _DAT_0121bc1c = DAT_012058f8;

    return;
}