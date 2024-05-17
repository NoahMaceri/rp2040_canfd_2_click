#ifndef TLE9255W_H
#define TLE9255W_H

#define CANFD2_REG_MODE_CTRL              0x01
#define CANFD2_REG_HW_CTRL                0x02
#define CANFD2_REG_TXD_TO_CTRL            0x03
#define CANFD2_REG_SUPPLY_CTRL            0x04

#define CANFD2_REG_SWK_CTRL_1             0x05
#define CANFD2_REG_SWK_CTRL_2             0x06
#define CANFD2_REG_SWK_ID3_CTRL           0x07
#define CANFD2_REG_SWK_ID2_CTRL           0x08
#define CANFD2_REG_SWK_ID1_CTRL           0x09
#define CANFD2_REG_SWK_ID0_CTRL           0x0A
#define CANFD2_REG_SWK_MASK_ID3_CTRL      0x0B
#define CANFD2_REG_SWK_MASK_ID2_CTRL      0x0C
#define CANFD2_REG_SWK_MASK_ID1_CTRL      0x0D
#define CANFD2_REG_SWK_MASK_ID0_CTRL      0x0E
#define CANFD2_REG_SWK_DLC_CTRL           0x0F
#define CANFD2_REG_SWK_DATA7_CTRL         0x10
#define CANFD2_REG_SWK_DATA6_CTRL         0x11
#define CANFD2_REG_SWK_DATA5_CTRL         0x12
#define CANFD2_REG_SWK_DATA4_CTRL         0x13
#define CANFD2_REG_SWK_DATA3_CTRL         0x14
#define CANFD2_REG_SWK_DATA2_CTRL         0x15
#define CANFD2_REG_SWK_DATA1_CTRL         0x16
#define CANFD2_REG_SWK_DATA0_CTRL         0x17

#define CANFD2_REG_TRANS_STAT             0x18
#define CANFD2_REG_TRANS_UV_STAT          0x19
#define CANFD2_REG_ERR_STAT               0x1A
#define CANFD2_REG_WAKE_STAT              0x1B

#define CANFD2_REG_SWK_STAT               0x1C
#define CANFD2_REG_SWK_ECNT_STAT          0x1D

#define CANFD2_CTRL_MODE_SLEEP            0x01
#define CANFD2_CTRL_MODE_STANDBY          0x02
#define CANFD2_CTRL_MODE_REC_ONLY         0x04
#define CANFD2_CTRL_MODE_NORMAL_OP        0x08 

#define CANFD2_HW_CTRL_VBAT_CON           0x01
#define CANFD2_HW_CTRL_WAKE_TOG           0x02
#define CANFD2_HW_CTRL_LWU_POS            0x20
#define CANFD2_HW_CTRL_LWU_NEG            0x40
#define CANFD2_HW_CTRL_STTS_EN            0x80 

#define CANFD2_TXD_TO_1_4                 0x01
#define CANFD2_TXD_TO_2_5                 0x02
#define CANFD2_TXD_TO_5_10                0x03
#define CANFD2_TXD_TO_DISABLE             0x04

#define CANFD2_SUP_CTRL_VCC_UV_T_100      0x01
#define CANFD2_SUP_CTRL_VCC_UV_T_200      0x02
#define CANFD2_SUP_CTRL_VCC_UV_T_300      0x03
#define CANFD2_SUP_CTRL_VCC_UV_T_400      0x04
#define CANFD2_SUP_CTRL_VCC_UV_T_500      0x05
#define CANFD2_SUP_CTRL_VCC_UV_T_600      0x06
#define CANFD2_SUP_CTRL_VCC_UV_T_700      0x07
#define CANFD2_SUP_CTRL_VCC_UV_T_800      0x08
#define CANFD2_SUP_CTRL_VCC_UV_T_900      0x09
#define CANFD2_SUP_CTRL_VCC_UV_T_1000     0x0A
#define CANFD2_SUP_CTRL_VCC_UV_T_1100     0x0B
#define CANFD2_SUP_CTRL_VCC_UV_T_1200     0x0C
#define CANFD2_SUP_CTRL_VCC_UV_T_1300     0x0D
#define CANFD2_SUP_CTRL_VCC_UV_T_1400     0x0E
#define CANFD2_SUP_CTRL_VCC_UV_T_1500     0x0F

#define CANFD2_SUP_CTRL_VIO_UV_T_100      0x10
#define CANFD2_SUP_CTRL_VIO_UV_T_200      0x20
#define CANFD2_SUP_CTRL_VIO_UV_T_300      0x30
#define CANFD2_SUP_CTRL_VIO_UV_T_400      0x40
#define CANFD2_SUP_CTRL_VIO_UV_T_500      0x50
#define CANFD2_SUP_CTRL_VIO_UV_T_600      0x60
#define CANFD2_SUP_CTRL_VIO_UV_T_700      0x70
#define CANFD2_SUP_CTRL_VIO_UV_T_800      0x80
#define CANFD2_SUP_CTRL_VIO_UV_T_900      0x90
#define CANFD2_SUP_CTRL_VIO_UV_T_1000     0xA0
#define CANFD2_SUP_CTRL_VIO_UV_T_1100     0xB0
#define CANFD2_SUP_CTRL_VIO_UV_T_1200     0xC0
#define CANFD2_SUP_CTRL_VIO_UV_T_1300     0xD0
#define CANFD2_SUP_CTRL_VIO_UV_T_1400     0xE0
#define CANFD2_SUP_CTRL_VIO_UV_T_1500     0xF0 

#define CANFD2_SWK_CTRL_1_CFG_VAL         0x01

#define CANFD2_SWK_CTRL_2_BR_125K         0x01
#define CANFD2_SWK_CTRL_2_BR_250K         0x02
#define CANFD2_SWK_CTRL_2_BR_500K         0x03
#define CANFD2_SWK_CTRL_2_BR_1M           0x04
#define CANFD2_SWK_CTRL_2_BR_RATIO_4      0x00
#define CANFD2_SWK_CTRL_2_BR_RATIO_10     0x10
#define CANFD2_SWK_CTRL_2_SWK_EN          0x80

#define CANFD2_SWK_ID3_CTRL_IDE           0x20

#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_0  0x00
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_1  0x01
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_2  0x02
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_3  0x03
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_4  0x04
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_5  0x05
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_6  0x06
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_7  0x07
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_8  0x08

#define CANFD2_TRANS_STAT_TSD             0x02
#define CANFD2_TRANS_STAT_TXD_TO          0x04
#define CANFD2_TRANS_STAT_POR             0x80

#define CANFD2_TRANS_UV_STAT_VIO_STUV     0x01
#define CANFD2_TRANS_UV_STAT_VIO_LTUV     0x02
#define CANFD2_TRANS_UV_STAT_VCC_STUV     0x10
#define CANFD2_TRANS_UV_STAT_VCC_LTUV     0x20
#define CANFD2_TRANS_UV_STAT_VBAT_UV      0x80

#define CANFD2_ERR_STAT_CMD_ERR           0x01
#define CANFD2_ERR_STAT_COM_ERR           0x02

#define CANFD2_WAKE_STAT_WUF              0x01
#define CANFD2_WAKE_STAT_WUP              0x02
#define CANFD2_WAKE_STAT_LWU              0x04
#define CANFD2_WAKE_STAT_LWU_DIR          0x08

#define CANFD2_SWK_STAT_SWK_ACT          0x01
#define CANFD2_SWK_STAT_CANSIL           0x02
#define CANFD2_SWK_STAT_CANTO            0x04
#define CANFD2_SWK_STAT_SYNC             0x08
#define CANFD2_SWK_STAT_SYSERR           0x10

#define CANFD2_OP_MODE_SLEEP              0x01
#define CANFD2_OP_MODE_STANDBY            0x02
#define CANFD2_OP_MODE_RECEIVE_ONLY       0x03
#define CANFD2_OP_MODE_NORMAL             0x04
#define CANFD2_OP_MODE_UNKNOWN            0x05

#define DUMMY                                0
#define CANFD2_READ_CMD_MASK              0x7F
#define CANFD2_WRITE_CMD                  0x80

#endif  // _TLE9255W_H_