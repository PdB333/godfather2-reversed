// FUNC_NAME: checkAndProcess (address 0x006250c0)
// Role: Checks a flag (bit 0) in a context structure; if not set, delegates to a processing function with the data field.

// External function called when flag is clear
extern int __fastcall FUN_006250e0(int data);

// Context structure: byte flag + 3 bytes padding + int data
struct ProcessContext {
    byte flags; // +0x00: flag bits (bit 0 = processed)
    // padding to align int
    int data;   // +0x04: data passed to processing function
};

// __fastcall: first argument in ECX
int __fastcall checkAndProcess(ProcessContext* ctx) {
    // If the processed flag (bit 0) is already set, return immediately
    if (ctx->flags & 1) {
        return 1;
    }
    // Otherwise, process the data and return the result
    return FUN_006250e0(ctx->data);
}