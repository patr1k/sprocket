#pragma once

#include "gameboy.h"
#include <stdint.h>

#define CPU_INSTR(name) void cpu_##name(struct gbc *dev)

void (*cpu_isa[0x100])(struct gbc *);
void (*cpu_isa_cb[0x100])(struct gbc *);

/**
 * Block 0 Instructions
 */
CPU_INSTR(nop);

CPU_INSTR(ld_BC_d16);
CPU_INSTR(ld_DE_d16);
CPU_INSTR(ld_HL_d16);
CPU_INSTR(ld_SP_d16);

CPU_INSTR(ld_BCmem_A);
CPU_INSTR(ld_DEmem_A);
CPU_INSTR(ld_HLi_A);
CPU_INSTR(ld_HLd_A);

CPU_INSTR(ld_A_BCmem);
CPU_INSTR(ld_A_DEmem);
CPU_INSTR(ld_A_HLi);
CPU_INSTR(ld_A_HLd);

CPU_INSTR(ld_a16_SP);

CPU_INSTR(inc_BC);
CPU_INSTR(inc_DE);
CPU_INSTR(inc_HL);
CPU_INSTR(inc_SP);

CPU_INSTR(dec_BC);
CPU_INSTR(dec_DE);
CPU_INSTR(dec_HL);
CPU_INSTR(dec_SP);

CPU_INSTR(add_HL_BC);
CPU_INSTR(add_HL_DE);
CPU_INSTR(add_HL_HL);
CPU_INSTR(add_HL_SP);

CPU_INSTR(inc_B);
CPU_INSTR(inc_C);
CPU_INSTR(inc_D);
CPU_INSTR(inc_E);
CPU_INSTR(inc_H);
CPU_INSTR(inc_L);
CPU_INSTR(inc_HLmem);
CPU_INSTR(inc_A);

CPU_INSTR(dec_B);
CPU_INSTR(dec_C);
CPU_INSTR(dec_D);
CPU_INSTR(dec_E);
CPU_INSTR(dec_H);
CPU_INSTR(dec_L);
CPU_INSTR(dec_HLmem);
CPU_INSTR(dec_A);

CPU_INSTR(ld_B_d8);
CPU_INSTR(ld_C_d8);
CPU_INSTR(ld_D_d8);
CPU_INSTR(ld_E_d8);
CPU_INSTR(ld_H_d8);
CPU_INSTR(ld_L_d8);
CPU_INSTR(ld_HLmem_d8);
CPU_INSTR(ld_A_d8);

CPU_INSTR(rlca);
CPU_INSTR(rrca);
CPU_INSTR(rla);
CPU_INSTR(rra);

CPU_INSTR(daa);
CPU_INSTR(cpl);

CPU_INSTR(scf);
CPU_INSTR(ccf);

CPU_INSTR(jr_r8);
CPU_INSTR(jr_nz_r8);
CPU_INSTR(jr_z_r8);
CPU_INSTR(jr_nc_r8);
CPU_INSTR(jr_c_r8);

CPU_INSTR(stop);

/**
 * Block 1 Instructions
 */
CPU_INSTR(halt);

CPU_INSTR(ld_B_B);
CPU_INSTR(ld_B_C);
CPU_INSTR(ld_B_D);
CPU_INSTR(ld_B_E);
CPU_INSTR(ld_B_H);
CPU_INSTR(ld_B_L);
CPU_INSTR(ld_B_HLmem);
CPU_INSTR(ld_B_A);

CPU_INSTR(ld_C_B);
CPU_INSTR(ld_C_C);
CPU_INSTR(ld_C_D);
CPU_INSTR(ld_C_E);
CPU_INSTR(ld_C_H);
CPU_INSTR(ld_C_L);
CPU_INSTR(ld_C_HLmem);
CPU_INSTR(ld_C_A);

CPU_INSTR(ld_D_B);
CPU_INSTR(ld_D_C);
CPU_INSTR(ld_D_D);
CPU_INSTR(ld_D_E);
CPU_INSTR(ld_D_H);
CPU_INSTR(ld_D_L);
CPU_INSTR(ld_D_HLmem);
CPU_INSTR(ld_D_A);

CPU_INSTR(ld_E_B);
CPU_INSTR(ld_E_C);
CPU_INSTR(ld_E_D);
CPU_INSTR(ld_E_E);
CPU_INSTR(ld_E_H);
CPU_INSTR(ld_E_L);
CPU_INSTR(ld_E_HLmem);
CPU_INSTR(ld_E_A);

CPU_INSTR(ld_H_B);
CPU_INSTR(ld_H_C);
CPU_INSTR(ld_H_D);
CPU_INSTR(ld_H_E);
CPU_INSTR(ld_H_H);
CPU_INSTR(ld_H_L);
CPU_INSTR(ld_H_HLmem);
CPU_INSTR(ld_H_A);

CPU_INSTR(ld_L_B);
CPU_INSTR(ld_L_C);
CPU_INSTR(ld_L_D);
CPU_INSTR(ld_L_E);
CPU_INSTR(ld_L_H);
CPU_INSTR(ld_L_L);
CPU_INSTR(ld_L_HLmem);
CPU_INSTR(ld_L_A);

CPU_INSTR(ld_HLmem_B);
CPU_INSTR(ld_HLmem_C);
CPU_INSTR(ld_HLmem_D);
CPU_INSTR(ld_HLmem_E);
CPU_INSTR(ld_HLmem_H);
CPU_INSTR(ld_HLmem_L);
CPU_INSTR(ld_HLmem_A);

CPU_INSTR(ld_A_B);
CPU_INSTR(ld_A_C);
CPU_INSTR(ld_A_D);
CPU_INSTR(ld_A_E);
CPU_INSTR(ld_A_H);
CPU_INSTR(ld_A_L);
CPU_INSTR(ld_A_HLmem);
CPU_INSTR(ld_A_A);

/**
 * Block 2 Instructions
 */
CPU_INSTR(add_A_B);
CPU_INSTR(add_A_C);
CPU_INSTR(add_A_D);
CPU_INSTR(add_A_E);
CPU_INSTR(add_A_H);
CPU_INSTR(add_A_L);
CPU_INSTR(add_A_HLmem);
CPU_INSTR(add_A_A);

CPU_INSTR(adc_A_B);
CPU_INSTR(adc_A_C);
CPU_INSTR(adc_A_D);
CPU_INSTR(adc_A_E);
CPU_INSTR(adc_A_H);
CPU_INSTR(adc_A_L);
CPU_INSTR(adc_A_HLmem);
CPU_INSTR(adc_A_A);

CPU_INSTR(sub_A_B);
CPU_INSTR(sub_A_C);
CPU_INSTR(sub_A_D);
CPU_INSTR(sub_A_E);
CPU_INSTR(sub_A_H);
CPU_INSTR(sub_A_L);
CPU_INSTR(sub_A_HLmem);
CPU_INSTR(sub_A_A);

CPU_INSTR(sbc_A_B);
CPU_INSTR(sbc_A_C);
CPU_INSTR(sbc_A_D);
CPU_INSTR(sbc_A_E);
CPU_INSTR(sbc_A_H);
CPU_INSTR(sbc_A_L);
CPU_INSTR(sbc_A_HLmem);
CPU_INSTR(sbc_A_A);

CPU_INSTR(and_A_B);
CPU_INSTR(and_A_C);
CPU_INSTR(and_A_D);
CPU_INSTR(and_A_E);
CPU_INSTR(and_A_H);
CPU_INSTR(and_A_L);
CPU_INSTR(and_A_HLmem);
CPU_INSTR(and_A_A);

CPU_INSTR(xor_A_B);
CPU_INSTR(xor_A_C);
CPU_INSTR(xor_A_D);
CPU_INSTR(xor_A_E);
CPU_INSTR(xor_A_H);
CPU_INSTR(xor_A_L);
CPU_INSTR(xor_A_HLmem);
CPU_INSTR(xor_A_A);

CPU_INSTR(or_A_B);
CPU_INSTR(or_A_C);
CPU_INSTR(or_A_D);
CPU_INSTR(or_A_E);
CPU_INSTR(or_A_H);
CPU_INSTR(or_A_L);
CPU_INSTR(or_A_HLmem);
CPU_INSTR(or_A_A);

CPU_INSTR(cp_A_B);
CPU_INSTR(cp_A_C);
CPU_INSTR(cp_A_D);
CPU_INSTR(cp_A_E);
CPU_INSTR(cp_A_H);
CPU_INSTR(cp_A_L);
CPU_INSTR(cp_A_HLmem);
CPU_INSTR(cp_A_A);

/**
 * Block 3 Instructions
 */
CPU_INSTR(add_A_d8);
CPU_INSTR(adc_A_d8);
CPU_INSTR(sub_A_d8);
CPU_INSTR(sbc_A_d8);
CPU_INSTR(and_A_d8);
CPU_INSTR(xor_A_d8);
CPU_INSTR(or_A_d8);
CPU_INSTR(cp_A_d8);

CPU_INSTR(ret_NZ);
CPU_INSTR(ret_Z);
CPU_INSTR(ret_NC);
CPU_INSTR(ret_C);
CPU_INSTR(ret);
CPU_INSTR(reti);

CPU_INSTR(jp_NZ_a16);
CPU_INSTR(jp_Z_a16);
CPU_INSTR(jp_NC_a16);
CPU_INSTR(jp_C_a16);
CPU_INSTR(jp_a16);
CPU_INSTR(jp_HL);

CPU_INSTR(call_NZ_a16);
CPU_INSTR(call_Z_a16);
CPU_INSTR(call_NC_a16);
CPU_INSTR(call_C_a16);
CPU_INSTR(call_a16);

CPU_INSTR(rst_00h);
CPU_INSTR(rst_08h);
CPU_INSTR(rst_10h);
CPU_INSTR(rst_18h);
CPU_INSTR(rst_20h);
CPU_INSTR(rst_28h);
CPU_INSTR(rst_30h);
CPU_INSTR(rst_38h);

CPU_INSTR(pop_BC);
CPU_INSTR(pop_DE);
CPU_INSTR(pop_HL);
CPU_INSTR(pop_AF);

CPU_INSTR(push_BC);
CPU_INSTR(push_DE);
CPU_INSTR(push_HL);
CPU_INSTR(push_AF);

CPU_INSTR(ldh_a8_A);
CPU_INSTR(ldh_Cmem_A);
CPU_INSTR(ld_a16_A);
CPU_INSTR(ldh_A_a8);
CPU_INSTR(ldh_A_Cmem);
CPU_INSTR(ld_A_a16);
CPU_INSTR(di);
CPU_INSTR(ei);

CPU_INSTR(add_SP_r8);
CPU_INSTR(ld_HL_SPr8);
CPU_INSTR(ld_SP_HL);

/**
 * Block 3 Instructions (0xCB Extension)
 */
CPU_INSTR(rlc_B);
CPU_INSTR(rlc_C);
CPU_INSTR(rlc_D);
CPU_INSTR(rlc_E);
CPU_INSTR(rlc_H);
CPU_INSTR(rlc_L);
CPU_INSTR(rlc_HLmem);
CPU_INSTR(rlc_A);

CPU_INSTR(rrc_B);
CPU_INSTR(rrc_C);
CPU_INSTR(rrc_D);
CPU_INSTR(rrc_E);
CPU_INSTR(rrc_H);
CPU_INSTR(rrc_L);
CPU_INSTR(rrc_HLmem);
CPU_INSTR(rrc_A);

CPU_INSTR(rl_B);
CPU_INSTR(rl_C);
CPU_INSTR(rl_D);
CPU_INSTR(rl_E);
CPU_INSTR(rl_H);
CPU_INSTR(rl_L);
CPU_INSTR(rl_HLmem);
CPU_INSTR(rl_A);

CPU_INSTR(rr_B);
CPU_INSTR(rr_C);
CPU_INSTR(rr_D);
CPU_INSTR(rr_E);
CPU_INSTR(rr_H);
CPU_INSTR(rr_L);
CPU_INSTR(rr_HLmem);
CPU_INSTR(rr_A);

CPU_INSTR(sla_B);
CPU_INSTR(sla_C);
CPU_INSTR(sla_D);
CPU_INSTR(sla_E);
CPU_INSTR(sla_H);
CPU_INSTR(sla_L);
CPU_INSTR(sla_HLmem);
CPU_INSTR(sla_A);

CPU_INSTR(sra_B);
CPU_INSTR(sra_C);
CPU_INSTR(sra_D);
CPU_INSTR(sra_E);
CPU_INSTR(sra_H);
CPU_INSTR(sra_L);
CPU_INSTR(sra_HLmem);
CPU_INSTR(sra_A);

CPU_INSTR(swap_B);
CPU_INSTR(swap_C);
CPU_INSTR(swap_D);
CPU_INSTR(swap_E);
CPU_INSTR(swap_H);
CPU_INSTR(swap_L);
CPU_INSTR(swap_HLmem);
CPU_INSTR(swap_A);

CPU_INSTR(srl_B);
CPU_INSTR(srl_C);
CPU_INSTR(srl_D);
CPU_INSTR(srl_E);
CPU_INSTR(srl_H);
CPU_INSTR(srl_L);
CPU_INSTR(srl_HLmem);
CPU_INSTR(srl_A);

CPU_INSTR(bit_0_B);
CPU_INSTR(bit_1_B);
CPU_INSTR(bit_2_B);
CPU_INSTR(bit_3_B);
CPU_INSTR(bit_4_B);
CPU_INSTR(bit_5_B);
CPU_INSTR(bit_6_B);
CPU_INSTR(bit_7_B);

CPU_INSTR(bit_0_C);
CPU_INSTR(bit_1_C);
CPU_INSTR(bit_2_C);
CPU_INSTR(bit_3_C);
CPU_INSTR(bit_4_C);
CPU_INSTR(bit_5_C);
CPU_INSTR(bit_6_C);
CPU_INSTR(bit_7_C);

CPU_INSTR(bit_0_D);
CPU_INSTR(bit_1_D);
CPU_INSTR(bit_2_D);
CPU_INSTR(bit_3_D);
CPU_INSTR(bit_4_D);
CPU_INSTR(bit_5_D);
CPU_INSTR(bit_6_D);
CPU_INSTR(bit_7_D);

CPU_INSTR(bit_0_E);
CPU_INSTR(bit_1_E);
CPU_INSTR(bit_2_E);
CPU_INSTR(bit_3_E);
CPU_INSTR(bit_4_E);
CPU_INSTR(bit_5_E);
CPU_INSTR(bit_6_E);
CPU_INSTR(bit_7_E);

CPU_INSTR(bit_0_H);
CPU_INSTR(bit_1_H);
CPU_INSTR(bit_2_H);
CPU_INSTR(bit_3_H);
CPU_INSTR(bit_4_H);
CPU_INSTR(bit_5_H);
CPU_INSTR(bit_6_H);
CPU_INSTR(bit_7_H);

CPU_INSTR(bit_0_L);
CPU_INSTR(bit_1_L);
CPU_INSTR(bit_2_L);
CPU_INSTR(bit_3_L);
CPU_INSTR(bit_4_L);
CPU_INSTR(bit_5_L);
CPU_INSTR(bit_6_L);
CPU_INSTR(bit_7_L);

CPU_INSTR(bit_0_HLmem);
CPU_INSTR(bit_1_HLmem);
CPU_INSTR(bit_2_HLmem);
CPU_INSTR(bit_3_HLmem);
CPU_INSTR(bit_4_HLmem);
CPU_INSTR(bit_5_HLmem);
CPU_INSTR(bit_6_HLmem);
CPU_INSTR(bit_7_HLmem);

CPU_INSTR(bit_0_A);
CPU_INSTR(bit_1_A);
CPU_INSTR(bit_2_A);
CPU_INSTR(bit_3_A);
CPU_INSTR(bit_4_A);
CPU_INSTR(bit_5_A);
CPU_INSTR(bit_6_A);
CPU_INSTR(bit_7_A);

CPU_INSTR(res_0_B);
CPU_INSTR(res_1_B);
CPU_INSTR(res_2_B);
CPU_INSTR(res_3_B);
CPU_INSTR(res_4_B);
CPU_INSTR(res_5_B);
CPU_INSTR(res_6_B);
CPU_INSTR(res_7_B);

CPU_INSTR(res_0_C);
CPU_INSTR(res_1_C);
CPU_INSTR(res_2_C);
CPU_INSTR(res_3_C);
CPU_INSTR(res_4_C);
CPU_INSTR(res_5_C);
CPU_INSTR(res_6_C);
CPU_INSTR(res_7_C);

CPU_INSTR(res_0_D);
CPU_INSTR(res_1_D);
CPU_INSTR(res_2_D);
CPU_INSTR(res_3_D);
CPU_INSTR(res_4_D);
CPU_INSTR(res_5_D);
CPU_INSTR(res_6_D);
CPU_INSTR(res_7_D);

CPU_INSTR(res_0_E);
CPU_INSTR(res_1_E);
CPU_INSTR(res_2_E);
CPU_INSTR(res_3_E);
CPU_INSTR(res_4_E);
CPU_INSTR(res_5_E);
CPU_INSTR(res_6_E);
CPU_INSTR(res_7_E);

CPU_INSTR(res_0_H);
CPU_INSTR(res_1_H);
CPU_INSTR(res_2_H);
CPU_INSTR(res_3_H);
CPU_INSTR(res_4_H);
CPU_INSTR(res_5_H);
CPU_INSTR(res_6_H);
CPU_INSTR(res_7_H);

CPU_INSTR(res_0_L);
CPU_INSTR(res_1_L);
CPU_INSTR(res_2_L);
CPU_INSTR(res_3_L);
CPU_INSTR(res_4_L);
CPU_INSTR(res_5_L);
CPU_INSTR(res_6_L);
CPU_INSTR(res_7_L);

CPU_INSTR(res_0_HLmem);
CPU_INSTR(res_1_HLmem);
CPU_INSTR(res_2_HLmem);
CPU_INSTR(res_3_HLmem);
CPU_INSTR(res_4_HLmem);
CPU_INSTR(res_5_HLmem);
CPU_INSTR(res_6_HLmem);
CPU_INSTR(res_7_HLmem);

CPU_INSTR(res_0_A);
CPU_INSTR(res_1_A);
CPU_INSTR(res_2_A);
CPU_INSTR(res_3_A);
CPU_INSTR(res_4_A);
CPU_INSTR(res_5_A);
CPU_INSTR(res_6_A);
CPU_INSTR(res_7_A);

CPU_INSTR(set_0_B);
CPU_INSTR(set_1_B);
CPU_INSTR(set_2_B);
CPU_INSTR(set_3_B);
CPU_INSTR(set_4_B);
CPU_INSTR(set_5_B);
CPU_INSTR(set_6_B);
CPU_INSTR(set_7_B);

CPU_INSTR(set_0_C);
CPU_INSTR(set_1_C);
CPU_INSTR(set_2_C);
CPU_INSTR(set_3_C);
CPU_INSTR(set_4_C);
CPU_INSTR(set_5_C);
CPU_INSTR(set_6_C);
CPU_INSTR(set_7_C);

CPU_INSTR(set_0_D);
CPU_INSTR(set_1_D);
CPU_INSTR(set_2_D);
CPU_INSTR(set_3_D);
CPU_INSTR(set_4_D);
CPU_INSTR(set_5_D);
CPU_INSTR(set_6_D);
CPU_INSTR(set_7_D);

CPU_INSTR(set_0_E);
CPU_INSTR(set_1_E);
CPU_INSTR(set_2_E);
CPU_INSTR(set_3_E);
CPU_INSTR(set_4_E);
CPU_INSTR(set_5_E);
CPU_INSTR(set_6_E);
CPU_INSTR(set_7_E);

CPU_INSTR(set_0_H);
CPU_INSTR(set_1_H);
CPU_INSTR(set_2_H);
CPU_INSTR(set_3_H);
CPU_INSTR(set_4_H);
CPU_INSTR(set_5_H);
CPU_INSTR(set_6_H);
CPU_INSTR(set_7_H);

CPU_INSTR(set_0_L);
CPU_INSTR(set_1_L);
CPU_INSTR(set_2_L);
CPU_INSTR(set_3_L);
CPU_INSTR(set_4_L);
CPU_INSTR(set_5_L);
CPU_INSTR(set_6_L);
CPU_INSTR(set_7_L);

CPU_INSTR(set_0_HLmem);
CPU_INSTR(set_1_HLmem);
CPU_INSTR(set_2_HLmem);
CPU_INSTR(set_3_HLmem);
CPU_INSTR(set_4_HLmem);
CPU_INSTR(set_5_HLmem);
CPU_INSTR(set_6_HLmem);
CPU_INSTR(set_7_HLmem);

CPU_INSTR(set_0_A);
CPU_INSTR(set_1_A);
CPU_INSTR(set_2_A);
CPU_INSTR(set_3_A);
CPU_INSTR(set_4_A);
CPU_INSTR(set_5_A);
CPU_INSTR(set_6_A);
CPU_INSTR(set_7_A);