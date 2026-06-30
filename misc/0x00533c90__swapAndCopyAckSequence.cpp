// FUNC_NAME: swapAndCopyAckSequence  
// Function at 0x00533c90: Copies and swaps two 32-bit fields (offset 0 and 4) from src to dest,  
// then conditionally copies a third field from a pointer chain.  
// If src[1] and src[2] are both non-zero, dest[2] = *(uint32_t*)(src[2] + 4); otherwise dest[2] = 0.  
// Likely used in TNL packet processing to exchange sequence/ACK values and copy a linked packet pointer.  
void swapAndCopyAckSequence(uint32_t* dest, uint32_t* src) {  
    dest[0] = src[1];  // swap offset 0 and 4  
    dest[1] = src[0];  
    if (src[1] != 0 && src[2] != 0) {  
        dest[2] = *(uint32_t*)(src[2] + 4);  // copy field at offset 4 of the object pointed by src[2]  
    } else {  
        dest[2] = 0;  
    }  
}