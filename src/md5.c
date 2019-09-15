#include <stdio.h> // sprintf
#include <stdint.h> // uint*_t, int*_t
#include <string.h> // memcpy, memset

#include "md5.h" // MD5_CTX

static uint32_t 
S[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
         5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
         4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
         6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static uint32_t 
K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
         0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
         0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
         0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
         0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
         0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
         0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
         0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
         0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
         0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
         0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
         0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
         0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
         0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
         0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
         0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

extern void 
MD5Init(MD5_CTX* context)
{
    context->words[0] = 0x67452301;
    context->words[1] = 0xefcdab89;
    context->words[2] = 0x98badcfe;
    context->words[3] = 0x10325476;
    context->length = 0;
    context->c_length = 0;
}

static void
MD5Process(MD5_CTX* context, const uint8_t message[static 64])
{
    uint32_t m[16];
    memcpy(m, message, 64);
    
    uint32_t a = context->words[0];
    uint32_t b = context->words[1];
    uint32_t c = context->words[2];
    uint32_t d = context->words[3];

    uint8_t i;
    uint32_t f, g;
    for (i = 0; i < 64; i++)
    {
        if (i < 16)
        {       
            f = (b & c) | (~b & d);
            g = i;
        }
        else if (i < 32)
        {
            f = (d & b) | (~d & c);
            g = ((5 * i) + 1) % 16;
        }
        else if (i < 48)
        {
            f = (b ^ c ^ d);
            g = ((3 * i) + 5) % 16;
        }
        else
        {
            f = c ^ (b | ~d);
            g = (7 * i) % 16;
        }
        f += a + K[i] + m[g];
        a = d;
        d = c;
        c = b;
        b = b + ((f << S[i]) | (f >> (32 - S[i]))); 
    }

    context->words[0] += a;
    context->words[1] += b;
    context->words[2] += c;
    context->words[3] += d;
}

extern void
MD5Update(MD5_CTX* context, const uint8_t* chunk, 
          const size_t length)
{
    context->length += length;
    
    size_t i; 
    size_t j = 0;
    size_t n = length / 64;
    for (i = 0; i < n; i++)
    {
        MD5Process(context, &(chunk[j]));
        j += 64;
    }
   
    if (length > j)
    {
        memcpy(context->carry, &(chunk[j]), length);
        context->c_length = (uint8_t) length;
    }
}

static inline uint32_t
SwapUInt32(const uint32_t x)
{
    uint32_t a = (x & 0xff000000u) >> 24;
    uint32_t b = (x & 0x00ff0000u) >> 8;
    uint32_t c = (x & 0x0000ff00u) << 8;
    uint32_t d = (x & 0x000000ffu) << 24;
    return a | b | c | d;
}

extern void
MD5End(MD5_CTX* context, char* out)
{
    context->carry[context->c_length] = 0x80;
    context->c_length++;

    if (context->c_length > 56)
    {
        memset(&(context->carry[56]), 0, 64 - context->c_length); 
        MD5Process(context, context->carry);
        context->c_length = 0;
    }

    context->length *= 8;
    uint32_t lo = (uint32_t) context->length;
    uint32_t ho = (uint32_t) (context->length >> 32);

    memset(&(context->carry[context->c_length]), 0, 56 - context->c_length);
    memcpy(&(context->carry[56]), &lo, sizeof(uint32_t));
    memcpy(&(context->carry[60]), &ho, sizeof(uint32_t));
    MD5Process(context, context->carry);

    out[0] = '\0';

    int i;
    char buf[9] = "";
    for (i = 0; i < 4; i++)
    {
        sprintf(buf, "%08x", SwapUInt32(context->words[i]));
        strcat(out, buf);
    }
}
