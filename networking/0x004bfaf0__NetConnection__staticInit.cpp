// FUNC_NAME: NetConnection::staticInit
// Function address: 0x004bfaf0
// This function initializes the global class descriptor for the NetConnection class
// and registers it in the runtime type system linked list.
void NetConnection::staticInit()
{
    // Clear reference count / link fields
    gNetConnectionClassDescriptor.field_60 = 0;  // +0x60
    gNetConnectionClassDescriptor.field_64 = 0;  // +0x64
    gNetConnectionClassDescriptor.field_68 = 0;  // +0x68
    gNetConnectionClassDescriptor.field_6C = 0;  // +0x6C

    // Set vtable pointer to the static NetConnection vtable
    gNetConnectionClassDescriptor.vtable = &sNetConnectionVTable;  // +0x00

    // Copy class name into the descriptor buffer
    strncpy(gNetConnectionClassDescriptor.name, "NetConnection", 0x3F);  // +0x20, size 0x3F

    // Store the previous head of the class registry list
    gNetConnectionClassDescriptor.previousDescriptor = gClassRegistryHead;  // +0x70

    // Initialize various unknown fields to zero
    gNetConnectionClassDescriptor.field_04 = 0;   // +0x04
    gNetConnectionClassDescriptor.field_08 = 0;   // +0x08
    gNetConnectionClassDescriptor.field_0C = -1;  // +0x0C (0xFFFFFFFF sentinel?)
    gNetConnectionClassDescriptor.field_10 = 0;   // +0x10
    gNetConnectionClassDescriptor.field_14 = 0;   // +0x14
    gNetConnectionClassDescriptor.field_18 = 0;   // +0x18
    gNetConnectionClassDescriptor.field_1C = 0;   // +0x1C

    // Link this descriptor as the new head of the global class registry
    gClassRegistryHead = &gNetConnectionClassDescriptor;  // previously DAT_012059ec
}