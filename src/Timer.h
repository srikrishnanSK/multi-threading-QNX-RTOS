/**
 * 		@file Timer.h.
 *      @author Srikrishnan Venkatasubramanian.
 *		@brief Timers allows us to perform some tasks periodically at defined intervals or perform a task one-time from a defined time.
 *		Timers helps in easing the operations related to multi-threaded programming allowing us to wake up different
 *		threads at different times to perform respective tasks. The Timer class has been created mainly for handling the
 *		above defined activities. It has two functions where one is used to create a periodic timer and the other is used to
 *		emit a signal to indicate that the time. The type of signal used depends upon the defined requirements of the given
 *		application.
 *
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_ /**< Header gaurd to include certain files*/
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#define ONE_THOUSAND	1000
#define ONE_MILLION		1000000
#define OFFSET 1000000
/**< offset and period are in microsends. */
#define PERIOD10ms 10000 /**< Constant timer period macro for 10ms */
#define PERIOD500ms 500000 /**< Constant timer period macro for 500ms */
#define PERIOD2s 2000000 /**< Constant timer period macro for 2s */
#define PERIOD100ms 100000 /**< Constant timer period macro for 100ms */
#define PERIOD250ms 250000 /**< Constant timer period macro for 100ms */
#define PERIOD5s 5000000 /**< Constant timer period macro for 5s */
#define PERIOD150ms 150000 /**< Constant timer period macro for 150ms */
#define PERIOD500ms 500000 /**< Constant timer period macro for 500ms */
#define PERIOD1s 1000000 /**< Constant timer period macro for 1s */

class Timer {
protected:
	Timer();///Constructor
	virtual ~Timer();///Destructor
	void wait_next_activation(void);///Signaling function
	int periodic_timer(uint64_t offset, int period);///create a periodic timer
};

#endif /// SRC_TIMER_H_
