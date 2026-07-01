// FUNC_NAME: FloatStateMachine::processFloat
// Address: 0x00633990
// Role: State machine that converts a float to a string when state==3, then delegates to FUN_00638920.
// Structure offsets:
//   +0x00: state (int)
//   +0x04: value (float)

int __thiscall FloatStateMachine::processFloat(void* param_1)
{
    char buffer[92];

    // Only proceed if state is 3
    if (this->state != 3) {
        return 0;
    }

    // Format the float as a string with 14 significant digits (like printf("%.14g"))
    sprintf(buffer, "%.14g", (double)this->value);

    // Advance state to 4 (next step)
    this->state = 4;

    // Calculate length of formatted string (excluding null terminator)
    char* ptr = buffer;
    while (*ptr != '\0') {
        ptr++;
    }
    int len = (int)(ptr - (buffer + 1)); // Actually original code: (pcVar2 - (local_60+1)) gives len-1? Wait, careful.
    // In original: pcVar2 = local_60; do { cVar1 = *pcVar2; pcVar2 = pcVar2+1; } while (cVar1 != '\0'); iVar3 = FUN_00638920(param_1,local_60,(int)pcVar2 - (int)(local_60+1));
    // That gives: (end_ptr - (buffer+1)) = length of string (since end_ptr points to one past null, buffer+1 is start+1, so difference is strlen)
    // Example: "abc\0" -> start=buffer, end points to after \0 => buffer+4. buffer+1 => buffer+1. diff = 3. So len = strlen.
    len = (int)(ptr - (buffer + 1)); // This equals strlen(buffer)

    // Call the next processing function with the formatted string and its length
    int result = FUN_00638920(param_1, buffer, len);

    // Store the result back into the value field (cast to float)
    this->value = (float)result;

    return 1;
}