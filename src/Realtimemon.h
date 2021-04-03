/*
 *  @file Realtimemon.h
 *  @author Srikrishnan Venkatasubramanian
 *  @brief  Realtimemon class is a derived class that inherits methods from the base class Timer and csv. This class contains
 *  	    methods and variables which is used for performing line by line read from dataset.csv file, update the variables
 *  	    of interest in a shared memory location according to defined time periods, and display them to the console every 250ms.
 */

#ifndef SRC_REALTIMEMON_H_
#define SRC_REALTIMEMON_H_/**<Header gaurd to include certain files*/
#include "csv.h"
#include "Timer.h"
#include <unistd.h>
#include <pthread.h>


class Realtimemon:private csv, private Timer {
	/**<Class Realtime monitoring inheriting the csv and timer class privately*/
private:
	/// vector to store the line data read from the dataset every 1 second
	vector<string>tokenized_data;
	/// mutex definition
	pthread_mutex_t mutex_realtime;
	/** Structure that holds variables of different datatypes, representing different sensor variables of interest to be updated
	 * and displayed on the console*/
	struct parameters
	{
	    double fuel_consumption;
	    int Engine_speed;
	    int Engine_coolant_temperature;
	    int current_gear;
	    int vehicle_speed;
	    double acceleration;
	    int Brake_switch_indicator;
	    int Transmission_oil_temp;
	};

	/// declaration of structure object line_data
	struct parameters line_data;

public:
	Realtimemon();//Constructor
	virtual ~Realtimemon();//Destructor
	static void* Store_data_in_vector(void* arg);
	static void* Fuel_consumption(void* arg);
	static void* Engine_speed(void* arg);
	static void* Engine_coolant_temperature(void* arg);
	static void* Current_gear(void* arg);
	static void* Transmission_oil_temperature(void* arg);
	static void* vehicle_speed(void* arg);
	static void* Acceleration_speed_longitudinal(void* arg);
	static void* Indication_of_break_switch(void* arg);
	int timer_create(int period);
	void wait_for_signal(void);
	void update_console(void);
	void lock_variable(void);
	void unlock_variable(void);
};

#endif /* SRC_REALTIMEMON_H_ */
