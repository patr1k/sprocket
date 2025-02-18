#include "cpu_isa.h"

void (*cpu_isa[0x100])(struct gbc *);
void (*cpu_isa_cb[0x100])(struct gbc *);

void cpu_HARD_LOCK(struct gbc *dev)
{
    DECOMP("0x%x !!! HARD LOCK !!!", dev->cpu.IR)
    dev->cpu.mode.flag.LOCKED = 1;
}

void cpu_CB_EXT(struct gbc *dev)
{
    dev->cpu.IR = dev->mem[dev->cpu.PC.val++];
    cpu_isa_cb[dev->cpu.IR](dev);
}

void (*cpu_isa[0x100])(struct gbc *) = {
    /* 0x00 */ cpu_nop,
    /* 0x01 */ cpu_ld_BC_d16,
    /* 0x02 */ cpu_ld_BCmem_A,
    /* 0x03 */ cpu_inc_BC,
    /* 0x04 */ cpu_inc_B,
    /* 0x05 */ cpu_dec_B,
    /* 0x06 */ cpu_ld_B_d8,
    /* 0x07 */ cpu_rlca,
    /* 0x08 */ cpu_ld_a16_SP,
    /* 0x09 */ cpu_add_HL_BC,
    /* 0x0A */ cpu_ld_A_BCmem,
    /* 0x0B */ cpu_dec_BC,
    /* 0x0C */ cpu_inc_C,
    /* 0x0D */ cpu_dec_C,
    /* 0x0E */ cpu_ld_C_d8,
    /* 0x0F */ cpu_rrca,

    /* 0x10 */ cpu_stop,
    /* 0x11 */ cpu_ld_DE_d16,
    /* 0x12 */ cpu_ld_DEmem_A,
    /* 0x13 */ cpu_inc_DE,
    /* 0x14 */ cpu_inc_D,
    /* 0x15 */ cpu_dec_D,
    /* 0x16 */ cpu_ld_D_d8,
    /* 0x17 */ cpu_rla,
    /* 0x18 */ cpu_jr_r8,
    /* 0x19 */ cpu_add_HL_DE,
    /* 0x1A */ cpu_ld_A_DEmem,
    /* 0x1B */ cpu_dec_DE,
    /* 0x1C */ cpu_inc_E,
    /* 0x1D */ cpu_dec_E,
    /* 0x1E */ cpu_ld_E_d8,
    /* 0x1F */ cpu_rra,

    /* 0x20 */ cpu_jr_nz_r8,
    /* 0x21 */ cpu_ld_HL_d16,
    /* 0x22 */ cpu_ld_HLi_A,
    /* 0x23 */ cpu_inc_HL,
    /* 0x24 */ cpu_inc_H,
    /* 0x25 */ cpu_dec_H,
    /* 0x26 */ cpu_ld_H_d8,
    /* 0x27 */ cpu_daa,
    /* 0x28 */ cpu_jr_z_r8,
    /* 0x29 */ cpu_add_HL_HL,
    /* 0x2A */ cpu_ld_A_HLi,
    /* 0x2B */ cpu_dec_HL,
    /* 0x2C */ cpu_inc_L,
    /* 0x2D */ cpu_dec_L,
    /* 0x2E */ cpu_ld_L_d8,
    /* 0x2F */ cpu_cpl,

    /* 0x30 */ cpu_jr_nc_r8,
    /* 0x31 */ cpu_ld_SP_d16,
    /* 0x32 */ cpu_ld_HLd_A,
    /* 0x33 */ cpu_inc_SP,
    /* 0x34 */ cpu_inc_HLmem,
    /* 0x35 */ cpu_dec_HLmem,
    /* 0x36 */ cpu_ld_HLmem_d8,
    /* 0x37 */ cpu_scf,
    /* 0x38 */ cpu_jr_c_r8,
    /* 0x39 */ cpu_add_HL_SP,
    /* 0x3A */ cpu_ld_A_HLd,
    /* 0x3B */ cpu_dec_SP,
    /* 0x3C */ cpu_inc_A,
    /* 0x3D */ cpu_dec_A,
    /* 0x3E */ cpu_ld_A_d8,
    /* 0x3F */ cpu_ccf,

    /* 0x40 */ cpu_ld_B_B,
    /* 0x41 */ cpu_ld_B_C,
    /* 0x42 */ cpu_ld_B_D,
    /* 0x43 */ cpu_ld_B_E,
    /* 0x44 */ cpu_ld_B_H,
    /* 0x45 */ cpu_ld_B_L,
    /* 0x46 */ cpu_ld_B_HLmem,
    /* 0x47 */ cpu_ld_B_A,
    /* 0x48 */ cpu_ld_C_B,
    /* 0x49 */ cpu_ld_C_C,
    /* 0x4A */ cpu_ld_C_D,
    /* 0x4B */ cpu_ld_C_E,
    /* 0x4C */ cpu_ld_C_H,
    /* 0x4D */ cpu_ld_C_L,
    /* 0x4E */ cpu_ld_C_HLmem,
    /* 0x4F */ cpu_ld_C_A,

    /* 0x50 */ cpu_ld_D_B,
    /* 0x51 */ cpu_ld_D_C,
    /* 0x52 */ cpu_ld_D_D,
    /* 0x53 */ cpu_ld_D_E,
    /* 0x54 */ cpu_ld_D_H,
    /* 0x55 */ cpu_ld_D_L,
    /* 0x56 */ cpu_ld_D_HLmem,
    /* 0x57 */ cpu_ld_D_A,
    /* 0x58 */ cpu_ld_E_B,
    /* 0x59 */ cpu_ld_E_C,
    /* 0x5A */ cpu_ld_E_D,
    /* 0x5B */ cpu_ld_E_E,
    /* 0x5C */ cpu_ld_E_H,
    /* 0x5D */ cpu_ld_E_L,
    /* 0x5E */ cpu_ld_E_HLmem,
    /* 0x5F */ cpu_ld_E_A,

    /* 0x60 */ cpu_ld_H_B,
    /* 0x61 */ cpu_ld_H_C,
    /* 0x62 */ cpu_ld_H_D,
    /* 0x63 */ cpu_ld_H_E,
    /* 0x64 */ cpu_ld_H_H,
    /* 0x65 */ cpu_ld_H_L,
    /* 0x66 */ cpu_ld_H_HLmem,
    /* 0x67 */ cpu_ld_H_A,
    /* 0x68 */ cpu_ld_L_B,
    /* 0x69 */ cpu_ld_L_C,
    /* 0x6A */ cpu_ld_L_D,
    /* 0x6B */ cpu_ld_L_E,
    /* 0x6C */ cpu_ld_L_H,
    /* 0x6D */ cpu_ld_L_L,
    /* 0x6E */ cpu_ld_L_HLmem,
    /* 0x6F */ cpu_ld_L_A,

    /* 0x70 */ cpu_ld_HLmem_B,
    /* 0x71 */ cpu_ld_HLmem_C,
    /* 0x72 */ cpu_ld_HLmem_D,
    /* 0x73 */ cpu_ld_HLmem_E,
    /* 0x74 */ cpu_ld_HLmem_H,
    /* 0x75 */ cpu_ld_HLmem_L,
    /* 0x76 */ cpu_halt,
    /* 0x77 */ cpu_ld_HLmem_A,
    /* 0x78 */ cpu_ld_A_B,
    /* 0x79 */ cpu_ld_A_C,
    /* 0x7A */ cpu_ld_A_D,
    /* 0x7B */ cpu_ld_A_E,
    /* 0x7C */ cpu_ld_A_H,
    /* 0x7D */ cpu_ld_A_L,
    /* 0x7E */ cpu_ld_A_HLmem,
    /* 0x7F */ cpu_ld_A_A,

    /* 0x80 */ cpu_add_A_B,
    /* 0x81 */ cpu_add_A_C,
    /* 0x82 */ cpu_add_A_D,
    /* 0x83 */ cpu_add_A_E,
    /* 0x84 */ cpu_add_A_H,
    /* 0x85 */ cpu_add_A_L,
    /* 0x86 */ cpu_add_A_HLmem,
    /* 0x87 */ cpu_add_A_A,
    /* 0x88 */ cpu_adc_A_B,
    /* 0x89 */ cpu_adc_A_C,
    /* 0x8A */ cpu_adc_A_D,
    /* 0x8B */ cpu_adc_A_E,
    /* 0x8C */ cpu_adc_A_H,
    /* 0x8D */ cpu_adc_A_L,
    /* 0x8E */ cpu_adc_A_HLmem,
    /* 0x8F */ cpu_adc_A_A,

    /* 0x90 */ cpu_sub_A_B,
    /* 0x91 */ cpu_sub_A_C,
    /* 0x92 */ cpu_sub_A_D,
    /* 0x93 */ cpu_sub_A_E,
    /* 0x94 */ cpu_sub_A_H,
    /* 0x95 */ cpu_sub_A_L,
    /* 0x96 */ cpu_sub_A_HLmem,
    /* 0x97 */ cpu_sub_A_A,
    /* 0x98 */ cpu_sbc_A_B,
    /* 0x99 */ cpu_sbc_A_C,
    /* 0x9A */ cpu_sbc_A_D,
    /* 0x9B */ cpu_sbc_A_E,
    /* 0x9C */ cpu_sbc_A_H,
    /* 0x9D */ cpu_sbc_A_L,
    /* 0x9E */ cpu_sbc_A_HLmem,
    /* 0x9F */ cpu_sbc_A_A,

    /* 0xA0 */ cpu_and_A_B,
    /* 0xA1 */ cpu_and_A_C,
    /* 0xA2 */ cpu_and_A_D,
    /* 0xA3 */ cpu_and_A_E,
    /* 0xA4 */ cpu_and_A_H,
    /* 0xA5 */ cpu_and_A_L,
    /* 0xA6 */ cpu_and_A_HLmem,
    /* 0xA7 */ cpu_and_A_A,
    /* 0xA8 */ cpu_xor_A_B,
    /* 0xA9 */ cpu_xor_A_C,
    /* 0xAA */ cpu_xor_A_D,
    /* 0xAB */ cpu_xor_A_E,
    /* 0xAC */ cpu_xor_A_H,
    /* 0xAD */ cpu_xor_A_L,
    /* 0xAE */ cpu_xor_A_HLmem,
    /* 0xAF */ cpu_xor_A_A,

    /* 0xB0 */ cpu_or_A_B,
    /* 0xB1 */ cpu_or_A_C,
    /* 0xB2 */ cpu_or_A_D,
    /* 0xB3 */ cpu_or_A_E,
    /* 0xB4 */ cpu_or_A_H,
    /* 0xB5 */ cpu_or_A_L,
    /* 0xB6 */ cpu_or_A_HLmem,
    /* 0xB7 */ cpu_or_A_A,
    /* 0xB8 */ cpu_cp_A_B,
    /* 0xB9 */ cpu_cp_A_C,
    /* 0xBA */ cpu_cp_A_D,
    /* 0xBB */ cpu_cp_A_E,
    /* 0xBC */ cpu_cp_A_H,
    /* 0xBD */ cpu_cp_A_L,
    /* 0xBE */ cpu_cp_A_HLmem,
    /* 0xBF */ cpu_cp_A_A,

    /* 0xC0 */ cpu_ret_NZ,
    /* 0xC1 */ cpu_pop_BC,
    /* 0xC2 */ cpu_jp_NZ_a16,
    /* 0xC3 */ cpu_jp_a16,
    /* 0xC4 */ cpu_call_NZ_a16,
    /* 0xC5 */ cpu_push_BC,
    /* 0xC6 */ cpu_add_A_d8,
    /* 0xC7 */ cpu_rst_00h,
    /* 0xC8 */ cpu_ret_Z,
    /* 0xC9 */ cpu_ret,
    /* 0xCA */ cpu_jp_Z_a16,
    /* 0xCB */ cpu_CB_EXT,
    /* 0xCC */ cpu_call_Z_a16,
    /* 0xCD */ cpu_call_a16,
    /* 0xCE */ cpu_adc_A_d8,
    /* 0xCF */ cpu_rst_08h,

    /* 0xD0 */ cpu_ret_NC,
    /* 0xD1 */ cpu_pop_DE,
    /* 0xD2 */ cpu_jp_NC_a16,
    /* 0xD3 */ cpu_HARD_LOCK,
    /* 0xD4 */ cpu_call_NC_a16,
    /* 0xD5 */ cpu_push_DE,
    /* 0xD6 */ cpu_sub_A_d8,
    /* 0xD7 */ cpu_rst_10h,
    /* 0xD8 */ cpu_ret_C,
    /* 0xD9 */ cpu_reti,
    /* 0xDA */ cpu_jp_C_a16,
    /* 0xDB */ cpu_HARD_LOCK,
    /* 0xDC */ cpu_call_C_a16,
    /* 0xDD */ cpu_HARD_LOCK,
    /* 0xDE */ cpu_sbc_A_d8,
    /* 0xDF */ cpu_rst_18h,

    /* 0xE0 */ cpu_ldh_a8_A,
    /* 0xE1 */ cpu_pop_HL,
    /* 0xE2 */ cpu_ldh_Cmem_A,
    /* 0xE3 */ cpu_HARD_LOCK,
    /* 0xE4 */ cpu_HARD_LOCK,
    /* 0xE5 */ cpu_push_HL,
    /* 0xE6 */ cpu_and_A_d8,
    /* 0xE7 */ cpu_rst_20h,
    /* 0xE8 */ cpu_add_SP_r8,
    /* 0xE9 */ cpu_jp_HL,
    /* 0xEA */ cpu_ld_a16_A,
    /* 0xEB */ cpu_HARD_LOCK,
    /* 0xEC */ cpu_HARD_LOCK,
    /* 0xED */ cpu_HARD_LOCK,
    /* 0xEE */ cpu_xor_A_d8,
    /* 0xEF */ cpu_rst_28h,

    /* 0xF0 */ cpu_ldh_A_a8,
    /* 0xF1 */ cpu_pop_AF,
    /* 0xF2 */ cpu_ldh_A_Cmem,
    /* 0xF3 */ cpu_di,
    /* 0xF4 */ cpu_HARD_LOCK,
    /* 0xF5 */ cpu_push_AF,
    /* 0xF6 */ cpu_or_A_d8,
    /* 0xF7 */ cpu_rst_30h,
    /* 0xF8 */ cpu_ld_HL_SPr8,
    /* 0xF9 */ cpu_ld_SP_HL,
    /* 0xFA */ cpu_ld_A_a16,
    /* 0xFB */ cpu_ei,
    /* 0xFC */ cpu_HARD_LOCK,
    /* 0xFD */ cpu_HARD_LOCK,
    /* 0xFE */ cpu_cp_A_d8,
    /* 0xFF */ cpu_rst_38h,
};

void (*cpu_isa_cb[0x100])(struct gbc *) = {
    /* 0x00 */ cpu_rlc_B,
    /* 0x01 */ cpu_rlc_C,
    /* 0x02 */ cpu_rlc_D,
    /* 0x03 */ cpu_rlc_E,
    /* 0x04 */ cpu_rlc_H,
    /* 0x05 */ cpu_rlc_L,
    /* 0x06 */ cpu_rlc_HLmem,
    /* 0x07 */ cpu_rlc_A,
    /* 0x08 */ cpu_rrc_B,
    /* 0x09 */ cpu_rrc_C,
    /* 0x0A */ cpu_rrc_D,
    /* 0x0B */ cpu_rrc_E,
    /* 0x0C */ cpu_rrc_H,
    /* 0x0D */ cpu_rrc_L,
    /* 0x0E */ cpu_rrc_HLmem,
    /* 0x0F */ cpu_rrc_A,

    /* 0x10 */ cpu_rl_B,
    /* 0x11 */ cpu_rl_C,
    /* 0x12 */ cpu_rl_D,
    /* 0x13 */ cpu_rl_E,
    /* 0x14 */ cpu_rl_H,
    /* 0x15 */ cpu_rl_L,
    /* 0x16 */ cpu_rl_HLmem,
    /* 0x17 */ cpu_rl_A,
    /* 0x18 */ cpu_rr_B,
    /* 0x19 */ cpu_rr_C,
    /* 0x1A */ cpu_rr_D,
    /* 0x1B */ cpu_rr_E,
    /* 0x1C */ cpu_rr_H,
    /* 0x1D */ cpu_rr_L,
    /* 0x1E */ cpu_rr_HLmem,
    /* 0x1F */ cpu_rr_A,

    /* 0x20 */ cpu_sla_B,
    /* 0x21 */ cpu_sla_C,
    /* 0x22 */ cpu_sla_D,
    /* 0x23 */ cpu_sla_E,
    /* 0x24 */ cpu_sla_H,
    /* 0x25 */ cpu_sla_L,
    /* 0x26 */ cpu_sla_HLmem,
    /* 0x27 */ cpu_sla_A,
    /* 0x28 */ cpu_sra_B,
    /* 0x29 */ cpu_sra_C,
    /* 0x2A */ cpu_sra_D,
    /* 0x2B */ cpu_sra_E,
    /* 0x2C */ cpu_sra_H,
    /* 0x2D */ cpu_sra_L,
    /* 0x2E */ cpu_sra_HLmem,
    /* 0x2F */ cpu_sra_A,

    /* 0x30 */ cpu_swap_B,
    /* 0x31 */ cpu_swap_C,
    /* 0x32 */ cpu_swap_D,
    /* 0x33 */ cpu_swap_E,
    /* 0x34 */ cpu_swap_H,
    /* 0x35 */ cpu_swap_L,
    /* 0x36 */ cpu_swap_HLmem,
    /* 0x37 */ cpu_swap_A,
    /* 0x38 */ cpu_srl_B,
    /* 0x39 */ cpu_srl_C,
    /* 0x3A */ cpu_srl_D,
    /* 0x3B */ cpu_srl_E,
    /* 0x3C */ cpu_srl_H,
    /* 0x3D */ cpu_srl_L,
    /* 0x3E */ cpu_srl_HLmem,
    /* 0x3F */ cpu_srl_A,

    /* 0x40 */ cpu_bit_0_B,
    /* 0x41 */ cpu_bit_0_C,
    /* 0x42 */ cpu_bit_0_D,
    /* 0x43 */ cpu_bit_0_E,
    /* 0x44 */ cpu_bit_0_H,
    /* 0x45 */ cpu_bit_0_L,
    /* 0x46 */ cpu_bit_0_HLmem,
    /* 0x47 */ cpu_bit_0_A,
    /* 0x48 */ cpu_bit_1_B,
    /* 0x49 */ cpu_bit_1_C,
    /* 0x4A */ cpu_bit_1_D,
    /* 0x4B */ cpu_bit_1_E,
    /* 0x4C */ cpu_bit_1_H,
    /* 0x4D */ cpu_bit_1_L,
    /* 0x4E */ cpu_bit_1_HLmem,
    /* 0x4F */ cpu_bit_1_A,

    /* 0x50 */ cpu_bit_2_B,
    /* 0x51 */ cpu_bit_2_C,
    /* 0x52 */ cpu_bit_2_D,
    /* 0x53 */ cpu_bit_2_E,
    /* 0x54 */ cpu_bit_2_H,
    /* 0x55 */ cpu_bit_2_L,
    /* 0x56 */ cpu_bit_2_HLmem,
    /* 0x57 */ cpu_bit_2_A,
    /* 0x58 */ cpu_bit_3_B,
    /* 0x59 */ cpu_bit_3_C,
    /* 0x5A */ cpu_bit_3_D,
    /* 0x5B */ cpu_bit_3_E,
    /* 0x5C */ cpu_bit_3_H,
    /* 0x5D */ cpu_bit_3_L,
    /* 0x5E */ cpu_bit_3_HLmem,
    /* 0x5F */ cpu_bit_3_A,

    /* 0x60 */ cpu_bit_4_B,
    /* 0x61 */ cpu_bit_4_C,
    /* 0x62 */ cpu_bit_4_D,
    /* 0x63 */ cpu_bit_4_E,
    /* 0x64 */ cpu_bit_4_H,
    /* 0x65 */ cpu_bit_4_L,
    /* 0x66 */ cpu_bit_4_HLmem,
    /* 0x67 */ cpu_bit_4_A,
    /* 0x68 */ cpu_bit_5_B,
    /* 0x69 */ cpu_bit_5_C,
    /* 0x6A */ cpu_bit_5_D,
    /* 0x6B */ cpu_bit_5_E,
    /* 0x6C */ cpu_bit_5_H,
    /* 0x6D */ cpu_bit_5_L,
    /* 0x6E */ cpu_bit_5_HLmem,
    /* 0x6F */ cpu_bit_5_A,

    /* 0x70 */ cpu_bit_6_B,
    /* 0x71 */ cpu_bit_6_C,
    /* 0x72 */ cpu_bit_6_D,
    /* 0x73 */ cpu_bit_6_E,
    /* 0x74 */ cpu_bit_6_H,
    /* 0x75 */ cpu_bit_6_L,
    /* 0x76 */ cpu_bit_6_HLmem,
    /* 0x77 */ cpu_bit_6_A,
    /* 0x78 */ cpu_bit_7_B,
    /* 0x79 */ cpu_bit_7_C,
    /* 0x7A */ cpu_bit_7_D,
    /* 0x7B */ cpu_bit_7_E,
    /* 0x7C */ cpu_bit_7_H,
    /* 0x7D */ cpu_bit_7_L,
    /* 0x7E */ cpu_bit_7_HLmem,
    /* 0x7F */ cpu_bit_7_A,

    /* 0x80 */ cpu_res_0_B,
    /* 0x81 */ cpu_res_0_C,
    /* 0x82 */ cpu_res_0_D,
    /* 0x83 */ cpu_res_0_E,
    /* 0x84 */ cpu_res_0_H,
    /* 0x85 */ cpu_res_0_L,
    /* 0x86 */ cpu_res_0_HLmem,
    /* 0x87 */ cpu_res_0_A,
    /* 0x88 */ cpu_res_1_B,
    /* 0x89 */ cpu_res_1_C,
    /* 0x8A */ cpu_res_1_D,
    /* 0x8B */ cpu_res_1_E,
    /* 0x8C */ cpu_res_1_H,
    /* 0x8D */ cpu_res_1_L,
    /* 0x8E */ cpu_res_1_HLmem,
    /* 0x8F */ cpu_res_1_A,

    /* 0x90 */ cpu_res_2_B,
    /* 0x91 */ cpu_res_2_C,
    /* 0x92 */ cpu_res_2_D,
    /* 0x93 */ cpu_res_2_E,
    /* 0x94 */ cpu_res_2_H,
    /* 0x95 */ cpu_res_2_L,
    /* 0x96 */ cpu_res_2_HLmem,
    /* 0x97 */ cpu_res_2_A,
    /* 0x98 */ cpu_res_3_B,
    /* 0x99 */ cpu_res_3_C,
    /* 0x9A */ cpu_res_3_D,
    /* 0x9B */ cpu_res_3_E,
    /* 0x9C */ cpu_res_3_H,
    /* 0x9D */ cpu_res_3_L,
    /* 0x9E */ cpu_res_3_HLmem,
    /* 0x9F */ cpu_res_3_A,

    /* 0xA0 */ cpu_res_4_B,
    /* 0xA1 */ cpu_res_4_C,
    /* 0xA2 */ cpu_res_4_D,
    /* 0xA3 */ cpu_res_4_E,
    /* 0xA4 */ cpu_res_4_H,
    /* 0xA5 */ cpu_res_4_L,
    /* 0xA6 */ cpu_res_4_HLmem,
    /* 0xA7 */ cpu_res_4_A,
    /* 0xA8 */ cpu_res_5_B,
    /* 0xA9 */ cpu_res_5_C,
    /* 0xAA */ cpu_res_5_D,
    /* 0xAB */ cpu_res_5_E,
    /* 0xAC */ cpu_res_5_H,
    /* 0xAD */ cpu_res_5_L,
    /* 0xAE */ cpu_res_5_HLmem,
    /* 0xAF */ cpu_res_5_A,

    /* 0xB0 */ cpu_res_6_B,
    /* 0xB1 */ cpu_res_6_C,
    /* 0xB2 */ cpu_res_6_D,
    /* 0xB3 */ cpu_res_6_E,
    /* 0xB4 */ cpu_res_6_H,
    /* 0xB5 */ cpu_res_6_L,
    /* 0xB6 */ cpu_res_6_HLmem,
    /* 0xB7 */ cpu_res_6_A,
    /* 0xB8 */ cpu_res_7_B,
    /* 0xB9 */ cpu_res_7_C,
    /* 0xBA */ cpu_res_7_D,
    /* 0xBB */ cpu_res_7_E,
    /* 0xBC */ cpu_res_7_H,
    /* 0xBD */ cpu_res_7_L,
    /* 0xBE */ cpu_res_7_HLmem,
    /* 0xBF */ cpu_res_7_A,

    /* 0xC0 */ cpu_set_0_B,
    /* 0xC1 */ cpu_set_0_C,
    /* 0xC2 */ cpu_set_0_D,
    /* 0xC3 */ cpu_set_0_E,
    /* 0xC4 */ cpu_set_0_H,
    /* 0xC5 */ cpu_set_0_L,
    /* 0xC6 */ cpu_set_0_HLmem,
    /* 0xC7 */ cpu_set_0_A,
    /* 0xC8 */ cpu_set_1_B,
    /* 0xC9 */ cpu_set_1_C,
    /* 0xCA */ cpu_set_1_D,
    /* 0xCB */ cpu_set_1_E,
    /* 0xCC */ cpu_set_1_H,
    /* 0xCD */ cpu_set_1_L,
    /* 0xCE */ cpu_set_1_HLmem,
    /* 0xCF */ cpu_set_1_A,

    /* 0xD0 */ cpu_set_2_B,
    /* 0xD1 */ cpu_set_2_C,
    /* 0xD2 */ cpu_set_2_D,
    /* 0xD3 */ cpu_set_2_E,
    /* 0xD4 */ cpu_set_2_H,
    /* 0xD5 */ cpu_set_2_L,
    /* 0xD6 */ cpu_set_2_HLmem,
    /* 0xD7 */ cpu_set_2_A,
    /* 0xD8 */ cpu_set_3_B,
    /* 0xD9 */ cpu_set_3_C,
    /* 0xDA */ cpu_set_3_D,
    /* 0xDB */ cpu_set_3_E,
    /* 0xDC */ cpu_set_3_H,
    /* 0xDD */ cpu_set_3_L,
    /* 0xDE */ cpu_set_3_HLmem,
    /* 0xDF */ cpu_set_3_A,

    /* 0xE0 */ cpu_set_4_B,
    /* 0xE1 */ cpu_set_4_C,
    /* 0xE2 */ cpu_set_4_D,
    /* 0xE3 */ cpu_set_4_E,
    /* 0xE4 */ cpu_set_4_H,
    /* 0xE5 */ cpu_set_4_L,
    /* 0xE6 */ cpu_set_4_HLmem,
    /* 0xE7 */ cpu_set_4_A,
    /* 0xE8 */ cpu_set_5_B,
    /* 0xE9 */ cpu_set_5_C,
    /* 0xEA */ cpu_set_5_D,
    /* 0xEB */ cpu_set_5_E,
    /* 0xEC */ cpu_set_5_H,
    /* 0xED */ cpu_set_5_L,
    /* 0xEE */ cpu_set_5_HLmem,
    /* 0xEF */ cpu_set_5_A,

    /* 0xF0 */ cpu_set_6_B,
    /* 0xF1 */ cpu_set_6_C,
    /* 0xF2 */ cpu_set_6_D,
    /* 0xF3 */ cpu_set_6_E,
    /* 0xF4 */ cpu_set_6_H,
    /* 0xF5 */ cpu_set_6_L,
    /* 0xF6 */ cpu_set_6_HLmem,
    /* 0xF7 */ cpu_set_6_A,
    /* 0xF8 */ cpu_set_7_B,
    /* 0xF9 */ cpu_set_7_C,
    /* 0xFA */ cpu_set_7_D,
    /* 0xFB */ cpu_set_7_E,
    /* 0xFC */ cpu_set_7_H,
    /* 0xFD */ cpu_set_7_L,
    /* 0xFE */ cpu_set_7_HLmem,
    /* 0xFF */ cpu_set_7_A,
};