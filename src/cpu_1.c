/**
 * CPU Block 1 Instructions
 * 
 * @author patrik <patr1k@cyntacs.com>
 */

 #include "cpu.h"
 #include "cpu_instr_set.h"
 
 void cpu_ld_r8_r8(struct gbc* dev, enum cpu_reg_r8 r8dst, enum cpu_reg_r8 r8src)
 {
    if (r8dst == R8_HL && r8src == R8_HL) return cpu_halt(dev);

    DECOMP("LD %s, %s", R8_NAME(r8dst), R8_NAME(r8src))
    *cpu_r8_ptr(dev, r8dst) = cpu_r8_val(dev, r8src);
 }
 
 void cpu_halt(struct gbc* dev)
 {
     DECOMP("HALT")
 }
 
 void cpu_add_a_r8(struct gbc* dev, enum cpu_reg_r8 r8)
 {
    DECOMP("ADD A, %s", R8_NAME(r8))
    dev->cpu.AF.byte.A += cpu_r8_val(dev, r8);
 }