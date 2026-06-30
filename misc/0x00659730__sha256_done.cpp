// FUNC_NAME: sha256_done
// Function address: 0x00659730
// Role: Finalizes SHA-256 hash computation (libtomcrypt sha256_done)

#include <cstring> // for memset, but not strictly needed in reconstruction

typedef struct {
    uint32_t count[2];      // +0x00: bit count (low, high)
    uint32_t state[8];      // +0x08: hash state (8 x 32-bit words)
    uint32_t curlen;        // +0x28: bytes processed in current block
    unsigned char buf[64];  // +0x2c: current block buffer
} sha256_state;

// Prototype for compression function (address 0x00658fe0)
extern void sha256_compress(sha256_state *md, const unsigned char *buf);

int sha256_done(sha256_state *md, unsigned char *hash)
{
    uint32_t i, j;
    uint32_t low, high;

    // NULL checks (original code uses _ARGCHK macro, but we replicate behaviour)
    if (md == 0) {
        // Debug print (omitted in release builds; shown here for fidelity)
        // _ARGCHK("md != NULL" failed)
        // In the original, after printing it continues – we skip early return
    }
    if (hash == 0) {
        // _ARGCHK("hash != NULL" failed)
    }

    // If curlen < 64, do final block processing
    if (md->curlen < 64) {
        // Update bit count with current block length * 8 (bits)
        low = md->count[0];
        high = md->count[1];
        md->count[0] = low + (md->curlen * 8);
        md->count[1] = high + (low > md->count[0] ? 1 : 0); // carry

        // Pad with 0x80
        md->buf[md->curlen] = 0x80;
        md->curlen++;

        // If we have more than 56 bytes, pad rest of block with zeros and compress
        if (md->curlen > 56) {
            while (md->curlen < 64) {
                md->buf[md->curlen] = 0;
                md->curlen++;
            }
            sha256_compress(md, md->buf);
            md->curlen = 0;
        }

        // Pad remaining bytes up to 56 (the last 8 bytes are for length)
        while (md->curlen < 56) {
            md->buf[md->curlen] = 0;
            md->curlen++;
        }

        // Store the 64-bit bit count in big-endian order in the last 8 bytes
        md->buf[56] = (unsigned char)(md->count[1] >> 24);
        md->buf[57] = (unsigned char)(md->count[1] >> 16);
        md->buf[58] = (unsigned char)(md->count[1] >> 8);
        md->buf[59] = (unsigned char)(md->count[1]);
        md->buf[60] = (unsigned char)(md->count[0] >> 24);
        md->buf[61] = (unsigned char)(md->count[0] >> 16);
        md->buf[62] = (unsigned char)(md->count[0] >> 8);
        md->buf[63] = (unsigned char)(md->count[0]);

        // Final compression
        sha256_compress(md, md->buf);

        // Output the hash in big-endian byte order
        // For each state word, bytes are reversed (MSB first)
        hash[0]  = (unsigned char)((unsigned char*)md)[0x0b]; // state[0] byte 3
        hash[1]  = (unsigned char)((unsigned char*)md)[0x0a]; // state[0] byte 2
        hash[2]  = (unsigned char)((unsigned char*)md)[0x09]; // state[0] byte 1
        hash[3]  = (unsigned char)(md->state[0]);             // state[0] byte 0 (LSB)

        hash[4]  = (unsigned char)((unsigned char*)md)[0x0f]; // state[1] byte 3
        hash[5]  = (unsigned char)((unsigned char*)md)[0x0e];
        hash[6]  = (unsigned char)((unsigned char*)md)[0x0d];
        hash[7]  = (unsigned char)(md->state[1]);

        hash[8]  = (unsigned char)((unsigned char*)md)[0x13]; // state[2] byte 3
        hash[9]  = (unsigned char)((unsigned char*)md)[0x12];
        hash[10] = (unsigned char)((unsigned char*)md)[0x11];
        hash[11] = (unsigned char)(md->state[2]);

        hash[12] = (unsigned char)((unsigned char*)md)[0x17]; // state[3] byte 3
        hash[13] = (unsigned char)((unsigned char*)md)[0x16];
        hash[14] = (unsigned char)((unsigned char*)md)[0x15];
        hash[15] = (unsigned char)(md->state[3]);

        hash[16] = (unsigned char)((unsigned char*)md)[0x1b]; // state[4] byte 3
        hash[17] = (unsigned char)((unsigned char*)md)[0x1a];
        hash[18] = (unsigned char)((unsigned char*)md)[0x19];
        hash[19] = (unsigned char)(md->state[4]);

        hash[20] = (unsigned char)((unsigned char*)md)[0x1f]; // state[5] byte 3
        hash[21] = (unsigned char)((unsigned char*)md)[0x1e];
        hash[22] = (unsigned char)((unsigned char*)md)[0x1d];
        hash[23] = (unsigned char)(md->state[5]);

        hash[24] = (unsigned char)((unsigned char*)md)[0x23]; // state[6] byte 3
        hash[25] = (unsigned char)((unsigned char*)md)[0x22];
        hash[26] = (unsigned char)((unsigned char*)md)[0x21];
        hash[27] = (unsigned char)(md->state[6]);

        hash[28] = (unsigned char)((unsigned char*)md)[0x27]; // state[7] byte 3
        hash[29] = (unsigned char)((unsigned char*)md)[0x26];
        hash[30] = (unsigned char)((unsigned char*)md)[0x25];
        hash[31] = (unsigned char)(md->state[7]);

        return 0; // success
    }
    return 0x10; // CRYPT_INVALID_ARG (or error code)
}