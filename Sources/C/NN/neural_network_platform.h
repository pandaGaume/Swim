#ifndef __NEURAL_NETWORK_PLATFORM_H
#define	__NEURAL_NETWORK_PLATFORM_H

#include <math.h>
#include <osal.h>

#ifdef	__cplusplus
extern "C" {

#endif
#ifndef _UI32_MAX
#define _UI32_MAX     0xffffffff // maximum unsigned 32 bit value
#endif // !_UI32_MAX

/* return value from 0 to 1 */
#define nn_rand() (((float)BP_rand())/_UI32_MAX)
#define nn_exp(v) exp((v))
#define nn_tanh(v) tanh((v))
#define nn_pow(v,r) pow((v),(r))
#define nn_malloc(s) OS_malloc((s))

#ifdef	__cplusplus
}
#endif

#endif

