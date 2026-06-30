// FUNC_NAME: NetMessage::sendFloatAsString
// Function address: 0x00633990
// Part of a state machine that converts a float to a string representation and sends it over the network.
// State 3 -> convert float to string via sprintf, set state to 4, call sendStringMessage, store result back to float field.

int __thiscall NetMessage::sendFloatAsString(int conn) {
    char buffer[92];
    
    // Check current state; must be 3 to proceed
    if (this->state != 3) {
        return 0;
    }
    
    // Convert the float value to a string with high precision (14 significant digits)
    _sprintf(buffer, "%.14g", this->value); // +0x04
    
    // Update state to 4 (string sent out)
    this->state = 4; // +0x00
    
    // Compute string length (excluding null terminator) and call network send function
    int len = strlen(buffer);
    int result = FUN_00638920(conn, buffer, len);
    
    // Store the result (likely a handle or ID) back into the float field (reuse)
    this->value = result; // +0x04
    
    return 1;
}