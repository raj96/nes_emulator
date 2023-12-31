#include <stdint.h>

#ifndef __instruction
#define __instruction

typedef struct __instruction {
	char *mnemonic;
	uint8_t opcode;
	uint8_t total_bytes;
	void (*addr_mode)(void);
	void (*operation)(void);
} instruction;

extern instruction *INSTRUCTIONS;

extern const instruction 
	adc_imm,
	adc_zp,
	adc_zpx,
	adc_abs,
	adc_abx,
	adc_aby,
	adc_idx,
	adc_idy,
	and_imm,
	and_zp,
	and_zpx,
	and_abs,
	and_abx,
	and_aby,
	and_idx,
	and_idy,
	asl_acc,
	asl_zp,
	asl_zpx,
	asl_abs,
	asl_abx,
	bcc_rel,
	bcs_rel,
	beq_rel,
	bmi_rel,
	bne_rel,
	bpl_rel,
	bvc_rel,
	bvs_rel,
	lda_imm,
	lda_abs,
	lda_abx,
	lda_aby,
	lda_zp,
	lda_zpx,
	lda_idx,
	lda_idy,
	ldx_imm,
	ldx_zp,
	ldx_zpy,
	ldx_abs,
	ldx_aby,
	ldy_imm,
	ldy_zp,
	ldy_zpx,
	ldy_abs,
	ldy_abx,
	sta_zp,
	sta_zpx,
	sta_abs,
	sta_abx,
	sta_aby,
	sta_idx,
	sta_idy,
	stx_zp,
	stx_zpy,
	stx_abs,
	sty_zp,
	sty_zpx,
	sty_abs,
	tax_imp,
	tay_imp,
	tsx_imp,
	txa_imp,
	txs_imp,
	tya_imp,
	pha_imp,
	php_imp,
	pla_imp,
	plp_imp,
	lsr_acc,
	lsr_zp,
	lsr_zpx,
	lsr_abs,
	lsr_abx,
	rol_acc,
	rol_zp,
	rol_zpx,
	rol_abs,
	rol_abx,
	ror_acc,
	ror_zp,
	ror_zpx,
	ror_abs,
	ror_abx,
	bit_zp,
	bit_abs,
	eor_imm,
	eor_zp,
	eor_zpx,
	eor_abs,
	eor_abx,
	eor_aby,
	eor_idx,
	eor_idy,
	ora_imm,
	ora_zp,
	ora_zpx,
	ora_abs,
	ora_abx,
	ora_aby,
	ora_idx,
	ora_idy,
	cmp_imm,
	cmp_zp,
	cmp_zpx,
	cmp_abs,
	cmp_abx,
	cmp_aby,
	cmp_idx,
	cmp_idy,
	cpx_imm,
	cpx_zp,
	cpx_abs,
	cpy_imm,
	cpy_zp,
	cpy_abs,
	sbc_imm,
	sbc_zp,
	sbc_zpx,
	sbc_abs,
	sbc_abx,
	sbc_aby,
	sbc_idx,
	sbc_idy,
	dec_zp,
	dec_zpx,
	dec_abs,
	dec_abx,
	dex_imp,
	dey_imp,
	inc_zp,
	inc_zpx,
	inc_abs,
	inc_abx,
	inx_imp,
	iny_imp,
	brk_imp,
	jmp_abs,
	jmp_ind,
	clc_imp,
	cld_imp,
	cli_imp,
	clv_imp,
	sec_imp,
	sed_imp,
	sei_imp,
	nop_imp,
	// Illegal Op-codes
	aac_imm,
	aac_imm2,
	aax_zp,
	aax_zpy,
	aax_idx,
	aax_abs,
	arr_imm,
	asr_imm,
	atx_imm,
	axa_aby,
	axa_idy,
	axs_imm,
	dcp_zp,
	dcp_zpx,
	dcp_abs,
	dcp_abx,
	dcp_aby,
	dcp_idx,
	dcp_idy,
	dop_zp,
	dop_zpx,
	dop_zpx2,
	dop_zp2,
	dop_zpx3,
	dop_zp3,
	dop_zpx4,
	dop_imm,
	dop_imm2,
	dop_imm3,
	dop_imm4,
	dop_zpx5,
	dop_imm5,
	dop_zpx6,
	isc_zp,
	isc_zpx,
	isc_abs,
	isc_abx,
	isc_aby,
	isc_idx,
	isc_idy,
	kil_imp,
	kil_imp2,
	kil_imp3,
	kil_imp4,
	kil_imp5,
	kil_imp6,
	kil_imp7,
	kil_imp8,
	kil_imp9,
	kil_imp10,
	kil_imp11,
	kil_imp12,
	lar_aby,
	lax_zp,
	lax_zpy,
	lax_abs,
	lax_aby,
	lax_idx,
	lax_idy,
	nop_imp2,
	nop_imp3,
	nop_imp4,
	nop_imp5,
	nop_imp6,
	nop_imp7,
	rla_zp,
	rla_zpx,
	rla_abs,
	rla_abx,
	rla_aby,
	rla_idx,
	rla_idy,
	rra_zp,
	rra_zpx,
	rra_abs,
	rra_abx,
	rra_aby,
	rra_idx,
	rra_idy,
	sbc_imm2,
	slo_zp,
	slo_zpx,
	slo_abs,
	slo_abx,
	slo_aby,
	slo_idx,
	slo_idy,
	sre_zp,
	sre_zpx,
	sre_abs,
	sre_abx,
	sre_aby,
	sre_idx,
	sre_idy,
	sxa_aby,
	sya_abx,
	top_abs,
	top_abx,
	top_abx2,
	top_abx3,
	top_abx4,
	top_abx5,
	top_abx6,
	xaa_imm,
	xas_aby;

void init_instructions();
void register_instruction(instruction);
instruction fetch_instruction(uint8_t opcode);
void deinit_instructions();

void register_branch_instruction_set();
void register_load_instruction_set();
void register_trans_instruction_set();
void register_stack_instruction_set();
void register_shift_instruction_set();
void register_logic_instruction_set();
void register_arith_instruction_set();
void register_inc_instruction_set();
void register_ctrl_instruction_set();
void register_flags_instruction_set();
void register_nop_instruction_set();
void register_illegal_instruction_set();

#endif