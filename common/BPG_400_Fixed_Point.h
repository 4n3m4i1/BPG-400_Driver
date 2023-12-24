#ifndef BPG_400_FIXED_PT_h
#define BPG_400_FIXED_PT_h

#include <inttypes.h>
// Macros for BPFIX fixed point

#define SHAMT       20
typedef uint32_t    BPFIX;
typedef int64_t     _sn2xFix;
typedef uint64_t    _uns2xFix;
//#define multfix14_16(a,b) ((fix14_16)((((signed long long)(a))*((signed long long)(b)))>>15)) //multiply two fixed 16.15
#define add_BPFIX(a,b)          (a + b)
#define sub_BPFIX(a,b)          (a - b)
#define mul_BPFIX(a,b)          ((BPFIX)((((_uns2xFix)(a))*((_uns2xFix)(b)))>>SHAMT)) //multiply two fixed 16.15
#define div_BPFIX(a,b)          ((BPFIX)(((_uns2xFix)(a) << SHAMT) / ((_uns2xFix)(b))) >> SHAMT) // ??

#define abs_BPFIX(a)            abs(a)
#define int_2_BPFIX(a)          ((BPFIX)(a << SHAMT))
#define BPFIX_2_int64(a)        ((_sn2xFix)(a >> SHAMT))
#define BPFIX_2_uint64(a)       ((_uns2xFix)(a >> SHAMT))
#define char_2_BPFIX(a)         (((BPFIX)(a)) << SHAMT)


// Don't include to save prog space even tho compiler probably is smart enough
#ifdef FIX_2_FLOAT

#define FL_CVT_CONST        32768.0 // prev 32768.0
#define float_2_BPFIX(a)      ((BPFIX)((a)*FL_CVT_CONST)) // 2^SHAMT
#define BPFIX_2_float(a)      ((float)(a)/FL_CVT_CONST)

#endif


#endif