#ifndef MD5_H
#define MD5_H

#include <string>
#include <cstring>
#include <iostream>

// md5 Source and Header files included in respective folders. For ease of use I included these so that we could create 
// reliable hashes without including standard C++ libraries (they can get messy)

typedef unsigned int uint4;
typedef unsigned char uint1;

class MD5 {
public:
    MD5();
    MD5(const std::string& text);
    void update(const unsigned char* buf, size_t length);
    void update(const char* buf, size_t length);
    MD5& finalize();
    std::string hexdigest() const;
private:
    void init();
    typedef unsigned char uint1; 
    typedef unsigned int uint4;  
    enum { blocksize = 64 }; 

    void transform(const uint1 block[blocksize]);
    static void decode(uint4 output[], const uint1 input[], size_t len);
    static void encode(uint1 output[], const uint4 input[], size_t len);

    bool finalized;
    uint1 buffer[blocksize]; 
    uint4 count[2];          
    uint4 state[4];          
    uint1 digest[16];        
};

std::string md5(const std::string str);

// Constants for MD5Transform routine.
inline uint4 F(uint4 x, uint4 y, uint4 z) { return (x & y) | (~x & z); }
inline uint4 G(uint4 x, uint4 y, uint4 z) { return (x & z) | (y & ~z); }
inline uint4 H(uint4 x, uint4 y, uint4 z) { return x ^ y ^ z; }
inline uint4 I(uint4 x, uint4 y, uint4 z) { return y ^ (x | ~z); }
inline uint4 rotate_left(uint4 x, int n) { return (x << n) | (x >> (32 - n)); }
inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{ a = rotate_left(a + F(b, c, d) + x + ac, s) + b; }
inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{ a = rotate_left(a + G(b, c, d) + x + ac, s) + b; }
inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{ a = rotate_left(a + H(b, c, d) + x + ac, s) + b; }
inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{ a = rotate_left(a + I(b, c, d) + x + ac, s) + b; }

#endif
