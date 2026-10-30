#ifndef PANS_INCLUDE_PANS_MACROS_H
#define PANS_INCLUDE_PANS_MACROS_H

#include <cassert>
#include <iostream>
#include <cstdint>

//自定义断言 并在内部调用默认断言 
#define PANS_ASSERT(x) \
    if(!(x))[[unlikely]]\
    {\
        std::cerr <<__FILE__<< ":" <<__LINE__<<" ASSERT FAILED: "<<#x<<"\nStacktrace: to do \n";\
        assert(x);\
    }

#define PANS_ASSERT2(x,w)\
    if(!(x))[[unlikely]]\
    {\
        std::cerr <<__FILE__<< ":" <<__LINE__<<"Assert: " << #x << " failed. [" << w << "].\nStacktrace: to do \n";\
        assert(x);\
    }

//带值返回的断言
#define ASSERT_RETVAL(x, val) \
    do {                     \
        if (x) break;        \
        PANS_ASSERT(x);      \
        return val;          \
    } while (0)
// break：退出宏内部的 do…while
// return：退出调用这个宏的整个函数
#define ASSERT_RETVAL2(x,val,info)\
    do{\
        if(x)[[likely]] break;\
        PANS_ASSERT2(x,info);\
        return val;\
    }while(0)
    
//
#define ASSERT_RETNONE(x)\
    do{\
        if(x) [[likely]] break;\
        PANS_ASSERT(x);\
        return;\
    }while(0)
#define ASSERT_RETNONE2(x,info)\
    do{\
        if(x) [[likely]] break;\
        PANS_ASSERT2(x,info);\
        return;\
    }while(0)
//
#define ASSERT_NOEFFECT(x)\
    do{\
        if(x) [[likely]] break;\
        PANS_ASSERT(x);\
    }while(0)
#define ASSERT_NOEFFECT2(x,info)\
    do{\
        if(x) [[likely]] break;\
        PANS_ASSERT2(x,info);\
    }while(0)

//下面这四个宏的break continue是为了影响外面的而不是宏内部的 所以不能用while
#define ASSERT_CONTINUE(x)\
    if (!(x)) [[unlikely]] {\
        PANS_ASSERT(x);\
        continue;\
    } else {}

#define ASSERT_CONTINUE2(x,info)\
    if (!(x)) [[unlikely]] {\
        PANS_ASSERT2(x,info);\
        continue;\
    } else {}

#define ASSERT_BREAK(x)\
    if (!(x)) [[unlikely]] {\
        PANS_ASSERT(x);\
        break;\
    } else {}

#define ASSERT_BREAK2(x,info)\
    if (!(x)) [[unlikely]] {\
        PANS_ASSERT2(x,info);\
        break;\
    } else {}

#define INVALID64 (~0ULL)
#define INVALID32 0xFFFFFFFF
#define INVALID16 0xFFFF
#define INVALID8 0xFF

#define MAX_U8 0xFF
#define MAX_U16 0xFFFF
#define MAX_U32 0xFFFFFFFF
#define MAX_U64 (~0ULL)

using u8 = std::uint8_t;
using s8 = std::int8_t;
using u16 = std::uint16_t;
using s16 = std::int16_t;
using u32 = std::uint32_t;
using s32 = std::int32_t;
using u64 = std::uint64_t;
using s64 = std::int64_t;

#endif