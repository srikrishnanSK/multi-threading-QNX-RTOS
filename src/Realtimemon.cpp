/*
 * @file Realtimemon.cpp
 * @author Srikrishnan Venkatasubramanian
 */

#include "Realtimemon.h"
/** Default constructor stub used to initialize the mutex*/
Realtimemon::Realtimemon() {
	 pthread_mutex_init(&mutex_realtime, NULL);

}

/** Default destructor stub used to destroy the mutex*/
Realtimemon::~Realtimemon() {
	pthread_mutex_destroy(&mutex_realtime);
}

/**
 * @brief       The defined function is used along with a thread to read a line data every 1 second from the given dataset.csv
 * 				file.(since data is usually collected every 1 second from an actual system this is done to emulate the system,
 * 				where data is collected in a vector and the respective variables are updated according to the defined requirements.)
 * @param void* arg  General pointer passed as an argument to a function. This is used to pass the class object from the main function
 * 				     that allows it to access available variables and methods of the base and derived class .
 * @return void*
 */

void* Realtimemon::Store_data_in_vector(void* arg)
{
	Realtimemon *monitor = static_cast<Realtimemon*>(arg);/// Type-casted to make it identifiable as an object of Realtimemon class
	int timer_res,line_number=2;///Line number and timer result
	///set and activate a timer
	timer_res = monitor->timer_create(PERIOD1s);/// Create a timer with a period 1s
	if (timer_res < 0 ){
			perror("Start periodic timer");
		}

		while(1)
		{
			monitor->wait_for_signal();/// Wait for signal activation
			monitor->lock_variable();///Lock variable using mutex
			monitor->tokenized_data = monitor->read_csv_line(line_number);/// read the line and store it in the vector
			monitor->unlock_variable();///Unlock variable using mutex
			line_number++;///Increments the line number
		}


	return (NULL);
}

/**
 * @brief The defined function is used to update the fuel_consumption variable in the structure parameter every 10 ms
 * @param void* arg General pointer passed as an argument to a function. This is used to pass the class object from the main function
 * 				    that allows it to access available variables and methods of the base and derived class .
 * @return void*
 */
void* Realtimemon::Fuel_consumption(void* arg)
{
	Realtimemon *monitor = static_cast<Realtimemon*>(arg);
	int timer_res;
	timer_res = monitor->timer_create(PERIOD10ms);/// Create a timer with a period 10ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		monitor->wait_for_signal(); /// Wait for signal activation
		monitor->lock_variable();///Lock variable using mutex
		monitor->line_data.fuel_consumption = stod(monitor->tokenized_data[0]); ///update the variable
		monitor->unlock_variable();///unlock the variable using mutex
	}
	return (NULL);
}

/**
 * @brief The defined function is used to update the Engine_speed variable in the structure parameter every 500 ms
 * @param void* arg General pointer passed as an argument to a function. This is used to pass the class object from the main function
 * 				     that allows it to access available variables and methods of the base and derived class .
 * @return void*
 */
void* Realtimemon::Engine_speed(void* arg)
{
	Realtimemon *monitor = static_cast<Realtimemon*>(arg);
	int timer_res;
	timer_res = monitor->timer_create(PERIOD500ms);/// Create a timer with a period 500ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		monitor->wait_for_signal();
		monitor->lock_variable();
		monitor->line_data.Engine_speed = stoi(monitor->tokenized_data[12]);
		monitor->unlock_variable();
	}
	return (NULL);
}

/**
 * @brief The defined function is used to update the Enginer_coolant_temperature variable in the structure parameter every 2s
 * @param void* arg General pointer passed as an argument to a function. This is used to pass the class object from the main function
 * 				     that allows it to access available variables and methods of the base and derived class ..
 * @return void*
 */
void* Realtimemon::Engine_coolant_temperature(void* arg)
{
	Realtimemon *monitor = static_cast<Realtimemon*>(arg);
	int timer_res;
	timer_res = monitor->timer_create(PERIOD2s);/// Create a timer with a period 2s
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		monitor->wait_for_signal();
		monitor->lock_variable();
		monitor->line_data.Engine_coolant_temperature = stoi(monitor->tokenized_data[17]);
		monitor->unlock_variable();
	}

	return (NULL);
}

/**
 * @brief The defined function is used to update the current_gear variable in the structure parameter every 100ms
 * @param void* General pointer passed as an argument to a function. This is used to pass the class object from the main function
 * 				that allows it to access available variables and methods of the base and derived class .
 * @return void*
 */
void* Realtimemon::Current_gear(void* arg)
{
	Realtimemon *monitor = static_cast<Realtimemon*>(arg);
	int timer_res;
	timer_res = monitor->timer_create(PERIOD100ms);/// Create a timer with a period 100ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		monitor->wait_for_signal();
		monitor->lock_variable();
		monitor->line_data.current_gear = stoi(monitor->tokenized_data[33]);
		monitor->unlock_variable();
	}
	return (NULL);
}
/**
 * @brief The defined function is used to update the Transmission_oil_temp variable in the structure parameter every 5s
 * @param void* arg General pointer passed as an argument to a function. This is used to pass the class object from the main function
 * 				     that allows it to access available variables and methods of the base and derived class .
 * @return void*
 */
void* Realtimemon::Transmission_oil_temperature(void* arg)
{
	Realtimemon *monitor = static_cast<Realtimemon*>(arg);
	int timer_res;
	timer_res = monitor->timer_create(PERIOD5s);/// Create a timer with a period 5s
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		monitor->wait_for_signal();
		monitor->lock_variable();
		monitor->line_data.Transmission_oil_temp = stoi(monitor->tokenized_data[34]);
		monitor->unlock_variable();


	}

	return (NULL);
}

/**
 * @brief The defined function is used to update the vehicle_speed variable in the structure parameter every 100ms
 * @param void* arg General pointer passed as an argument to a function. This is used to pass the class object from the main function
 * 				     that allows it to access available variables and methods of the base and derived class .
 * @return void*
 */
void* Realtimemon::vehicle_speed(void* arg)
{
	Realtimemon *monitor = static_cast<Realtimemon*>(arg);
	int timer_res;
	timer_res = monitor->timer_create(PERIOD100ms);/// Create a timer with a period 100ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		monitor->wait_for_signal();
		monitor->lock_variable();
		monitor->line_data.vehicle_speed = stoi(monitor->tokenized_data[43]);
		monitor->unlock_variable();
	}

	return (NULL);
}

/**
 * @brief The defined function is used to update the accelerarion variable in the structure parameter every 150ms
 * @param void* arg General pointer passed as an argument to a function. This is used to pass the class object from the main function
 * 				    that allows it to access available variables and methods of the base and derived class .
 * @return void*
 */
void* Realtimemon::Acceleration_speed_longitudinal(void* arg)
{
	Realtimemon *monitor = static_cast<Realtimemon*>(arg);
	int timer_res;
	timer_res = monitor->timer_create(PERIOD150ms);/// Create a timer with a period 150ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		monitor->wait_for_signal();
		monitor->lock_variable();
		monitor->line_data.acceleration = stod(monitor->tokenized_data[44]);
		monitor->unlock_variable();
	}

	return (NULL);
}

/**
 * @brief The defined function is used to update the brake_switch_indicator variable in the structure parameter every 100ms
 * @param void* arg General pointer passed as an argument to a function. This is used to pass the class object from the main function
 * 				    that allows it to access available variables and methods of the base and derived class .
 * @return void*
 */
void* Realtimemon::Indication_of_break_switch(void* arg)
{
	Realtimemon *monitor = static_cast<Realtimemon*>(arg);
	int timer_res;
	timer_res = monitor->timer_create(PERIOD100ms);/// Create a timer with a period 100ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		monitor->wait_for_signal();
		monitor->lock_variable();
		monitor->line_data.Brake_switch_indicator = stoi(monitor->tokenized_data[45]);
		monitor->unlock_variable();
	}

	return (NULL);
}

/**
 * @brief The defined function is used to create a timer for user defined time period. Since elements of the base Timer class is protected
 * 		  its methods can only be accessed within the scope of the derived class. Below defined functions provides an efficient way
 * 		  to access base class outside anywhere maintaining at most safety and security and allows us to pass only one argument.
 * @param int period The time period for which the timer has to be created
 * @return int On successful timer creation yields 0 and error returns -1
 */
int Realtimemon::timer_create(int period)
{
	return periodic_timer(OFFSET, period);
}

/**
 * @brief The defined function is used to signal wait check that suspends the calling thread until there is a status change.
 *  	  Since elements of the base Timer class is protected its methods can only be accessed within the scope of the derived class.
 *  	  Below defined functions provides an efficient way to access base class outside anywhere maintaining at most safety and
 *  	  security and allows us to pass only one argument.
 * @param  void
 * @return void
 */
void Realtimemon::wait_for_signal(void)
{
	wait_next_activation();
}

/**
 * @brief The defined function is used to lock a variable using mutex, thus preventing multiple threads trying to access a shared
 * 		  variable at the same time.Since elements of the base Timer class is protected its methods can only be accessed within the
 * 		  scope of the derived class.Below defined functions provides an efficient way to access base class outside anywhere maintaining at most safety and
 *  	  security and allows us to pass only one argument.
 * @param  void
 * @return void
 */
void Realtimemon::lock_variable(void)
{
	pthread_mutex_lock(&mutex_realtime);///Lock variable
}

/**
 * @brief The defined function is used to unlock a variable using mutex, thus releasing it to be accessed by other threads trying to
 * 		  update the variable.Since elements of the base Timer class is protected its methods can only be accessed within the
 * 		  scope of the derived class.Below defined functions provides an efficient way to access base class outside anywhere maintaining at most safety and
 *  	  security and allows us to pass only one argument.
 * @param  void
 * @return void
 */

void Realtimemon::unlock_variable(void)
{
	pthread_mutex_unlock(&mutex_realtime);///Unlock Variable
}
/**
 * @brief The defined function is used to display the data from the respective sensor variables every 500ms
 * @param void
 * @return void
 */
void Realtimemon::update_console(void)
{
	cout<<"Fuel Consumption: "<<line_data.fuel_consumption<<" "<<"Engine Speed: "<<line_data.Engine_speed<<" "<<"Engine Coolant Temperature: "<<line_data.Engine_coolant_temperature<<" "<<"Current Gear: "<<line_data.current_gear<<" "<<"Transmission Oil temperature: "<<line_data.Transmission_oil_temp<<" "<<"Vehicle Speed: "<<line_data.vehicle_speed<<" "<<"Acceleration speed Longitudinal:"<<line_data.acceleration<<" "<<"Indication of break switch: "<<line_data.Brake_switch_indicator<<" "<<endl;
}

