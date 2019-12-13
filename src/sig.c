/**
 * @file led_sig.c
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
#include "sig.h"

/*can be implemented*/

sig_val_t (*sig_get_val)(sig_t *) = sig_get_val_ram; //default is the RAM reader

/*Initilaizing led signal*/
sig_t sig_init(sig_val_t *signal, sig_size_t sig_size, sig_size_t phase_offset)
{
	sig_t sig;
	sig.signal = signal;
	sig.signal_size = sig_size;
	sig.phase_offset = phase_offset;
	sig.pval = (signal + (phase_offset % sig.signal_size));
	return sig;
}

/*Call by timer interrupt*/
void sig_tick(sig_t *signal)
{

	signal->pval = (signal->pval == signal->signal + signal->signal_size  - 1) ?
                                    signal->signal : ++signal->pval;

}

/*Get current value from signal*/
sig_val_t sig_get_val_ram(sig_t *signal)
{
	return *(signal->pval);
}

