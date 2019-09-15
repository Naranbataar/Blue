#ifndef MD5_H
#define MD5_H

typedef struct {
    uint32_t words[4];
    uint64_t length;
    uint8_t carry[64];
    uint8_t c_length;
    uint8_t _padding[7];
} MD5_CTX;

void
MD5Init(MD5_CTX* context);

void
MD5Update(MD5_CTX* context, const uint8_t* chunk, const size_t length);

void
MD5End(MD5_CTX* context, char* out);

#endif
