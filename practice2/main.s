	.arch armv8-a
	.file	"main.c"
// GNU C99 (Debian 11.2.0-13) version 11.2.0 (aarch64-linux-gnu)
//	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// options passed: -mlittle-endian -mabi=lp64 -std=c99 -fasynchronous-unwind-tables
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"HI"
	.align	3
.LC1:
	.string	"%s"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -16]!	//,,,
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp	//,
// main.c:7:     printf("%s", N);
	adrp	x0, .LC0	// tmp94,
	add	x1, x0, :lo12:.LC0	//, tmp94,
	adrp	x0, .LC1	// tmp95,
	add	x0, x0, :lo12:.LC1	//, tmp95,
	bl	printf		//
// main.c:8:     return 0;
	mov	w0, 0	// _3,
// main.c:9: }
	ldp	x29, x30, [sp], 16	//,,,
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret	
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 11.2.0-13) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
