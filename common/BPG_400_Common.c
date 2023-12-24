#include "BPG_400_Common.h"


uint8_t BPG_RETURN_CHECKSUM(struct BPG_400_Output *bpgdat){
    uint8_t retval = 0;
    
    if(bpgdat) {
        // Checksum from bytes 1-7
        for(uint16_t n = 1; n < (BPG_400_PACKET_LEN - 1); ++n) retval += bpgdat->BPG_Output[n];
    }

    return retval;
}


uint32_t BPG_GET_PRES(struct BPG_400_Output *bpgdat){
    uint32_t retval = UINT32_MAX;
    
    if(bpgdat){
        BPFIX numer = int_2_BPFIX(bpgdat->BPG_Output[BPG_MEAS_HI] << 8 + bpgdat->BPG_Output[BPG_MEAS_LO]);
        BPFIX divvy = int_2_BPFIX(4000);
        BPFIX tmp;

        switch(bpgdat->BPG_Output[BPG_STATUS] & BPG_400_UNIT_MASK){
            case BPG_400_UNIT_MBAR:
                // 12.5
                tmp = int_2_BPFIX(12);
                tmp |= (1 << (SHAMT - 1));      // + 0.5
                divvy = sub_BPFIX(divvy, tmp);
            break;
            case BPG_400_UNIT_TORR:
                // 12.625
                tmp = int_2_BPFIX(12);
                tmp |= (1 << (SHAMT - 1)) | (1 << (SHAMT - 3)); // + 0.625
                divvy = sub_BPFIX(divvy, tmp);
            break;
            case BPG_400_UNIT_PA:
                // 10.5
                tmp = int_2_BPFIX(10);
                tmp |= (1 << (SHAMT - 1));      // + 0.5
                divvy = sub_BPFIX(divvy, tmp);
            break;
        }

    // 10 ** (numer / divvy) == ans
        tmp = div_BPFIX(numer, divvy);

    }

    return retval;
}