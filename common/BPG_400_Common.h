#ifndef BPG_400_COMMON_h
#define BPG_400_COMMON_h

#include <inttypes.h>
#include "BPG_400_Fixed_Point.h"

#define BPG_400_PACKET_LEN  9

#ifndef SHF_BIT
#define SHF_BIT(a)      (1 << a)
#endif

#ifndef CLR_BIT
#define CLR_BIT(a,b)    a &= ~(1 << b)
#endif

#ifndef SET_BIT
#define SET_BIT(a,b)    a |= (1 << b)
#endif

#ifndef CHK_BIT
#define CHK_BIT(a,b)    ((a & (1u << b)) ? 1 : 0)
#endif

///////////////////////////////////////////////
//  Output Byte Structure
///////////////////////////////////////////////
enum BPG_400_OUTPUT_BYTES {
    BPG_LEN,
    BPG_PAGE_NO,
    BPG_STATUS,
    BPG_ERROR,
    BPG_MEAS_HI,
    BPG_MEAS_LO,
    BPG_SW_VER,
    BPG_SENS_TYPE,
    BPG_CHECKSUM
};

///////////////////////////////////////////////
//      Fixed Value Bytes
///////////////////////////////////////////////
#define BPG_400_LEN_VAL         7
#define BPG_400_PAGE_NO_VAL     5
#define BPG_400_SENS_TYPE_VAL   10

///////////////////////////////////////////////
//      Status Byte
///////////////////////////////////////////////
enum BPG_400_STATUS_OFFSETS {
    BPG_STAT_EMISSION,
    BPG_STAT_1_BAR_ADJ  = 2,
    BPG_STAT_TOGGLE,
    BPG_STAT_UNITS,
    BPG_STAT_RESERVED   = 6
};

enum BPG_400_EMISSION_TYPES {
    BPG_400_EMISSION_OFF,
    BPG_400_25UA_EMISSION,
    BPG_400_5MA_EMISSION,
    BPG_400_DEGAS_EMISSION
};

enum BPG_400_UNIT_TYPES {
    BPG_400_UNIT_MBAR,
    BPG_400_UNIT_TORR   = (1 << 4),
    BPG_400_UNIT_PA     = (1 << 5),
    BPG_400_UNIT_MASK   = ((1 << 5) | (1 << 4))
};

///////////////////////////////////////////////
//      Error Byte
///////////////////////////////////////////////
enum BPG_400_ERROR_OFFSETS {
    BPG_ERROR_RESERVED,
    BPG_ERROR_SENSOR_ERR = 4
};

enum BPG_400_SENSOR_ERRORS {
    BPG_PIRANI_ADJ_FAIL = ((1 << 6) | (1 << 4)),
    BPG_BA_ERROR        = (1 << 7),
    BPG_PIRANI_ERROR    = ((1 << 7) | (1 << 4))
};

///////////////////////////////////////////////
//      Data Structure
///////////////////////////////////////////////
struct BPG_400_Output {
    uint8_t BPG_Output[BPG_400_PACKET_LEN];
    uint8_t last_toggle_stat;
};

///////////////////////////////////////////////
//      Functions
///////////////////////////////////////////////
uint8_t BPG_RETURN_CHECKSUM(struct BPG_400_Output *bpgdat);



#endif