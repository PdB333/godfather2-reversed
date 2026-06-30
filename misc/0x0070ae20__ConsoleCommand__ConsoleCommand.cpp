// FUNC_NAME: ConsoleCommand::ConsoleCommand
class ConsoleCommand {
public:
    ConsoleCommand(const char* name, int arg1, int arg2, int arg3) {
        // Call base class constructor (likely ConsoleCommandBase or similar)
        FUN_0064cc90();

        // Set vtable pointer to ConsoleCommand vtable
        this->vtable = &PTR_LAB_00d61500;   // +0x00

        // Copy command name (max 63 chars)
        _strncpy(this->name, name, 0x3f);   // +0x08

        // Store arguments
        this->arg1 = arg1;   // +0x04
        this->arg3 = arg2;   // +0x0C  (offset from param_1[3])
        this->arg2 = arg3;   // +0x08  (offset from param_1[2])

        // Initialize linked list pointers
        this->next = nullptr;   // +0x10
        this->prev = nullptr;   // +0x14
        this->unk1 = nullptr;   // +0x18
        this->unk2 = nullptr;   // +0x1C

        // Link into global command list (head insertion)
        this->listNode = g_CommandListHead; // +0x70 (offset 0x1c * 4)
        g_CommandListHead = this;
    }

private:
    // Vtable base pointer at +0x00
    void* vtable;                  // +0x00
    int arg1;                      // +0x04
    int arg2;                      // +0x08  (note: this is actually from param_5)
    int arg3;                      // +0x0C  (from param_4)
    char name[0x40];              // +0x10? Actually offset 0x08, so size 0x40
    // Next and prev pointers for global command list
    ConsoleCommand* next;          // +0x10? Actually offset 0x10, but we have 0x1C for list node
    ConsoleCommand* prev;          // +0x14
    ConsoleCommand* unk1;          // +0x18
    ConsoleCommand* listNode;      // +0x70? Wait, offset 0x1c is param_1[0x1c] which is 0x70 bytes from start, but that seems wrong. Let's recalc: param_1 is uint*, so param_1[0x1c] = *(uint*)((char*)param_1 + 0x1c * 4) = offset 0x70. But the code sets param_1[0x1c] = DAT_012059ec, then DAT_012059ec = param_1. So it's a next pointer at offset 0x70? That seems large; perhaps the struct is larger. Let's adjust: param_1[0x1c] means at index 0x1c (28) in uint* array, so offset = 28*4 = 112 = 0x70. That's the offset of the next pointer in the linked list. So the struct has many fields. The name starts at param_1+8 (offset 32 bytes? Actually param_1+8 is offset 8*4=32 bytes, but _strncpy uses char* cast to param_1+8 which is a uint* +8 -> char* = (char*)param_1 + 8*4 = offset 32 from start. So name starts at offset 32. The first entries: vtable at +0, arg1 at +4, arg2 at +8? Wait param_1[1] is at +4, param_1[2] at +8, param_1[3] at +12. That's arg1, arg2, arg3. Then name at +32. Then next fields zeroed at +16, +20, +24, +28. That's consistent: param_1[4] = 0 at +16, param_1[5]=0 at +20, param_1[6]=0 at +24, param_1[7]=0 at +28. Then param_1[0x1c] = DAT at offset 0x70 (28*4=112) which is far beyond. So the struct is large. That suggests many other fields between offset 32 and 112. Possibly name is at offset 0x08? Wait, param_1+8 as char*: param_1 is uint*, adding 8 means offset 8*4=32 bytes. So name starts at byte offset 32 from this. That's unusual. Maybe the decompilation is misleading: param_1+8 in _strncpy might mean param_1[8] as in array index? Actually Ghidra's C: (char *)(param_1 + 8) means param_1 is a pointer to uint, +8 adds 8*sizeof(uint)=32 bytes, then cast to char*. So yes, offset 32. That's okay. Then the linked list pointer at offset 0x70 (112) makes sense.
};

// Global head of command list
extern ConsoleCommand* g_CommandListHead; // 0x012059ec