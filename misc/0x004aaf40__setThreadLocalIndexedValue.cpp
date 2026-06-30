// FUNC_NAME: setThreadLocalIndexedValue
// Address: 0x004aaf40
// This function writes an integer value to a per-thread context table,
// indexed by the object's slot offset (param_1 + 0x18).
// It retrieves a base address through a chain of TLS-based indirections.
void __thiscall setThreadLocalIndexedValue(int param_2)
{
    // Read the Thread Local Storage (TLS) pointer from FS:[0x2c]
    // On Windows, the TEB's offset 0x2c holds a pointer to the TLS array.
    int* tlsArray = *(int**)__readfsdword(0x2c);
    
    // Dereference the first TLS slot to get an intermediate value.
    int tlsValue = *tlsArray;
    
    // Add offset 8 to get a secondary pointer.
    int* secondaryPtr = (int*)(tlsValue + 8);
    
    // Dereference to obtain the base address used for the final write.
    int base = *secondaryPtr;
    
    // Retrieve the index from the object's member at offset 0x18.
    int index = *(int*)(this + 0x18);
    
    // Write the parameter to base + 100 + index.
    *(int*)(base + 100 + index) = param_2;
}