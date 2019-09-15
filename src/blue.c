#include <ftw.h> /* nftw */
#include <stdio.h> /* FILE, fopen, fread, fclose, fprintf */
#include <stdint.h> /* uint*_t, int*_t */
#include <string.h> /* memcpy, memset */

#include "md5.h" /* MD5_CTX, MD5Init, MD5Update, MD5End */
#include "blue.h" /* SIGNATURE */

static uint8_t 
MD5Compare(const char* filename, const char* hash)
{
    uint8_t ret = 0;

    MD5_CTX ctx;
    MD5Init(&ctx);
    
    FILE* fp = fopen(filename, "rb");
    if (fp != NULL)
    {
        size_t bytes;
        uint8_t data[1024];
        do 
        {
            bytes = fread(data, 1, 1024, fp);
            MD5Update(&ctx, data, bytes);
        } 
        while (bytes != 0);
        fclose(fp);
        
        char digest[16] = {0};
        MD5End(&ctx, digest);

        uint8_t i;
        for (i = 0; i < 16; i++)
        {
            if (digest[i] != hash[i])
            {
                ret = 1;
                break;
            }
        }
    }
    else
    {
        fprintf(stderr, "blue: Couldn't open '%s' for hash comparison", 
                filename);
        ret = 1;
    }
    return ret;
}

static SIGNATURE nftw_sign;
static int 
SearchFileTree(const char *fpath, const struct stat *sb, int tflag, 
               struct FTW *ftwbuf)
{
    (void)(ftwbuf);    
    if (tflag == FTW_F)
    {
        if (sb->st_size == nftw_sign.size)
        {
            if (MD5Compare(fpath, nftw_sign.hash) == 0)
            {
                printf("%s\n", fpath);
            }
        }
    }
    return 0;
}

extern int
BlueSearch(const SIGNATURE sign, const char* root)
{
    nftw_sign = sign;
    return nftw(root, SearchFileTree, 100, FTW_DEPTH | FTW_PHYS);
}
