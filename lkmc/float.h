#ifndef LKMC_FLOAT_H
#define LKMC_FLOAT_H

/* https://cirosantilli.com/linux-kernel-module-cheat#ieee-754 */

#define LKMC_FLOAT_64_SIGN_BITS 1
#define LKMC_FLOAT_64_EXP_BITS 11
#define LKMC_FLOAT_64_MANTISSA_BITS 52
#define LKMC_FLOAT_64_EXP_BIAS ((1 << (LKMC_FLOAT_64_EXP_BITS - 1)) - 1)
#define LKMC_FLOAT_64_EXP_INFINITY_BIASED ((1 << LKMC_FLOAT_64_EXP_BITS) - 1)
#define LKMC_FLOAT_64_EXP_INFINITY (LKMC_FLOAT_64_EXP_INFINITY_BIASED - LKMC_FLOAT_64_EXP_BIAS)
#define LKMC_FLOAT_64(sign, exp, mantissa) ((((sign << LKMC_FLOAT_64_EXP_BITS) | exp + LKMC_FLOAT_64_EXP_BIAS) << LKMC_FLOAT_64_MANTISSA_BITS) | mantissa)
#define LKMC_FLOAT_64_PLUS_INFINITY LKMC_FLOAT_64(0x0, LKMC_FLOAT_64_EXP_INFINITY, 0x0)
#define LKMC_FLOAT_64_MINUS_INFINITY LKMC_FLOAT_64(0x1, LKMC_FLOAT_64_EXP_INFINITY, 0x0)
#define LKMC_FLOAT_64_QNAN(x) LKMC_FLOAT_64(0x0, LKMC_FLOAT_64_EXP_INFINITY, (x) | (1 << (LKMC_FLOAT_64_MANTISSA_BITS - 1)))
#define LKMC_FLOAT_64_QNAN_DEFAULT LKMC_FLOAT_64_QNAN(1 << (LKMC_FLOAT_64_MANTISSA_BITS - 2))
#define LKMC_FLOAT_64_SNAN(x) LKMC_FLOAT_64(0x0, LKMC_FLOAT_64_EXP_INFINITY, x)
#define LKMC_FLOAT_64_SNAN_DEFAULT LKMC_FLOAT_64_SNAN(1 << (LKMC_FLOAT_64_MANTISSA_BITS - 2))

#endif
