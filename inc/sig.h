/**
 * @file led_sig.h
 * @author Istvan Milak (istvan.milak@gmail.com)
 * @brief
 Periodic signal handler for microcontroller applications.
 Timer can drive throug the value array on the outputs, with a given phase offset
 * @version 0.1
 * @date 2019-12-02
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef __LED_SIG_H__
#define __LED_SIG_H__


/*Signal typedef*/
#include <inttypes.h>
#include "sig_config.h"


/**
 * @brief Type definiton of LED signal
 *
 */
typedef struct
{
	sig_val_t*      signal;             // buffer of signal
	sig_size_t      signal_size;        // length of signal
	sig_val_t*      pval;               // pointer of current value
	sig_size_t      phase_offset;       // phase offset for signal
} sig_t;



/**
 * @brief Initializing LED signal
 *
 * @param signal signal array
 * @param sig_size length of the signal array
 * @param phase_offset
 * @return led_sig_t
 */
extern sig_t        sig_init(sig_val_t *signal, sig_size_t sig_size, sig_size_t phase_offset);



/**
 * @brief Calculate the next value of the LED from the signal array. It can be iterated by a timer, etc.
 *
 * @param signal signal struct
 */
extern void         sig_tick(sig_t *signal);

/**
 * @brief Return a LED value which is pointed by pval
 *
 * @param signal signal struct
 * @return led_val_t LED val
 */
extern sig_val_t    sig_get_val(sig_t *signal);

#endif // __LED_SIG_H__
