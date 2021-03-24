/**
 * 		@file Timer.cpp.
 *      @author Srikrishnan Venkatasubramanian.
 *
 */

#include "Timer.h"
///Signal
sigset_t sigst;

/** Default constructor stub that has been auto-generated and can be used based on requirement and design*/
Timer::Timer() {

}

/** Default Destructor stub that has been auto-generated and can be used based on requirement and design*/
Timer::~Timer() {
}

/**
 * @brief The below function is used to suspend the calling process until a signal has been recieved.
 * @param   No arguments
 * @return	    void.
 */
void Timer::wait_next_activation()
{
	int dummy;
	sigwait(&sigst, &dummy);
}

/**
 * @brief This function is used to calculate and set the required structure values for creating and setting a
 * 				specified periodic timer.
 * @param uint64_t constant in microsecond defined in the header. It is used for calculating and setting the
 * 				requested time period in the struct itimerspec.
 * @param int period Given as an input by the user. Defines the time interval for which the timer should be created
 * @return int returns -1 if error is setting the given time period.
 */

int Timer::periodic_timer(uint64_t offset, int period)
{
	struct itimerspec timer_spec;
		struct sigevent sigev;
		timer_t timer;
		const int signal = SIGALRM;
		int res;

		/** set timer parameters */
		timer_spec.it_value.tv_sec = offset / ONE_MILLION;
		timer_spec.it_value.tv_nsec = (offset % ONE_MILLION) * ONE_THOUSAND;
		timer_spec.it_interval.tv_sec = period / ONE_MILLION;
		timer_spec.it_interval.tv_nsec = (period % ONE_MILLION) * ONE_THOUSAND;

		sigemptyset(&sigst); /** initialize a signal set*/
		sigaddset(&sigst, signal); /** add SIGALRM to the signal set*/
		sigprocmask(SIG_BLOCK, &sigst, NULL); /** block the signal*/

		/** set the signal event a timer expiration */
		memset(&sigev, 0, sizeof(struct sigevent));
		sigev.sigev_notify = SIGEV_SIGNAL_THREAD;
		sigev.sigev_signo = signal;

		/** create timer with clock set to realtime */
		res = timer_create(CLOCK_REALTIME, &sigev, &timer);

		if (res < 0) {
			perror("Timer Create");
			exit(-1);
		}

		/** activates the timer */
		return timer_settime(timer, 0, &timer_spec, NULL);
}
