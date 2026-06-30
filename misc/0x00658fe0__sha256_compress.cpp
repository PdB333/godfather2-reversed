// FUNC_NAME: sha256_compress
void sha256_compress(uint *state, const uchar *block)
{
  uint a, b, c, d, e, f, g, h;
  uint w[64];
  uint t1, t2;
  uint i;

  if (state == (uint *)0x0) {
    // Debug assertion: "md != NULL", line 54 of sha256.c
    FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","md != NULL",0x36,
                 "..\\src\\libtomcrypt\\sha256.c");
    _fprintf((FILE *)0x40, "_ARGCHK '%s' failure on line %d of file %s\n");
  }

  // Load state into local variables
  a = state[0]; // +0x00
  b = state[1]; // +0x04
  c = state[2]; // +0x08
  d = state[3]; // +0x0c
  e = state[4]; // +0x10
  f = state[5]; // +0x14
  g = state[6]; // +0x18
  h = state[7]; // +0x1c

  // Prepare message schedule w[0..15] from block (big-endian)
  for (i = 0; i < 16; i++) {
    w[i] = ((uint)block[0] << 24) | ((uint)block[1] << 16) | ((uint)block[2] << 8) | (uint)block[3];
    block += 4;
  }

  // Extend message schedule w[16..63]
  for (i = 16; i < 64; i++) {
    uint s0 = ROTR(w[i-15], 7) ^ ROTR(w[i-15], 18) ^ (w[i-15] >> 3);
    uint s1 = ROTR(w[i-2], 17) ^ ROTR(w[i-2], 19) ^ (w[i-2] >> 10);
    w[i] = w[i-16] + s0 + w[i-7] + s1;
  }

  // Compression loop (64 rounds)
  for (i = 0; i < 64; i++) {
    uint S1 = ROTR(e, 6) ^ ROTR(e, 11) ^ ROTR(e, 25);
    uint ch = (e & f) ^ ((~e) & g);
    uint temp1 = h + S1 + ch + K[i] + w[i];
    uint S0 = ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22);
    uint maj = (a & b) ^ (a & c) ^ (b & c);
    uint temp2 = S0 + maj;

    h = g;
    g = f;
    f = e;
    e = d + temp1;
    d = c;
    c = b;
    b = a;
    a = temp1 + temp2;
  }

  // Update state
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  state[4] += e;
  state[5] += f;
  state[6] += g;
  state[7] += h;
}