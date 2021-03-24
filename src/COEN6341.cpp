/**
 * @file COEN6341.cpp.
 * @author Srikrishnan Venkatasubramanian.
 * @brief The given source files acts as the main interface between the two modules csv and timer defined as classes.
 *	Based on the requirements defined in the project description, threads have been created to read data occasionally
 *	to emulate the behavior of data arriving from sensor every 1 second. Additionally separate threads have been created
 *	for updating the sensor data to their respective sensor variables defined in a structure. The main thread is used to
 *	output the values on the console.
 *
 */

#ifndef COEN6341_H
#define COEN6341_H/**< Header gaurd to include certain files*/
#include "csv.h"
#include "Timer.h"
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#endif
/// Global vector to store the data read every 1 second
vector<string>tokenized_data;
/// mutex definition
pthread_mutex_t mutex_realtime;

/** Structure that holds variables of different datatypes, representing different sensor variables to be updated
 * and displayed on the console*/
struct parameters
{
    double fuel_consumption;
    int Engine_speed;
    int Enginer_coolant_temperature;
    int current_gear;
    int vehicle_speed;
    double acceleration;
    int Brake_switch_indicator;
    int Transmission_oil_temp;
};

/// Global declaration of structure object line_data
struct parameters line_data;

/**
 * @brief The defined function is used along with a thread to read a line data every 1 second from the given dataset.csv
 * 				file.(since data is usually collected every 1 second from an actual system this is done to emulate the system,
 * 				where data is collected in a vector and the respective variables are updated according to the defined requirements.)
 * @param void* arg General pointer passed as an argument to a function. If the argument is to be used it needs to
 * 				be type casted appropriately before usage.
 * @return void*
 */

void* Store_data_in_vector(void* arg)
{
	csv read;////CSV class object
	Timer Realtime;/// Timer class object
	int timer_res,line_number=2;///Line number and timer result

		///set and activate a timer
		timer_res = Realtime.periodic_timer(OFFSET, PERIOD1s);/// Create a timer with a period 1s
		if (timer_res < 0 ){
			perror("Start periodic timer");
		}

		while(1)
		{
			Realtime.wait_next_activation();/// Wait for signal activation
			pthread_mutex_lock(&mutex_realtime);///Lock
			tokenized_data = read.read_csv_line(line_number);/// read the line and store it in the vector
			pthread_mutex_unlock(&mutex_realtime);///Unlock
			line_number++;///Increments the line number
		}


	return (NULL);
}

/**
 * @brief The defined function is used to update the fuel_consumption variable in the structure parameter every 10 ms
 * @param void* arg General pointer passed as an argument to a function. If the argument is to be used it needs to
 * 				be type casted appropriately before usage.
 * @return void*
 */
void* Fuel_consumption(void* arg)
{
	Timer Realtime; /// Timer class object
	//int thread_id = pthread_self();
	int timer_res;
	timer_res = Realtime.periodic_timer(OFFSET, PERIOD10ms);/// Create a timer with a period 10ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		Realtime.wait_next_activation(); /// Wait for signal activation
		pthread_mutex_lock(&mutex_realtime);///Lock variable
		line_data.fuel_consumption = stod(tokenized_data[0]); ///update the variable
		//cout<<"Thread Id Fuel "<<thread_id<<" 10ms "<<line_data.fuel_consumption<<endl;
		pthread_mutex_unlock(&mutex_realtime);///unlock the variable

	}

	return (NULL);
}

/**
 * @brief The defined function is used to update the Engine_speed variable in the structure parameter every 500 ms
 * @param void* arg General pointer passed as an argument to a function. If the argument is to be used it needs to
 * 				be type casted appropriately before usage.
 * @return void*
 */
void* Engine_speed(void* arg)
{
	Timer Realtime;
	//int thread_id = pthread_self();
	int timer_res;
	timer_res = Realtime.periodic_timer(OFFSET, PERIOD500ms);/// Create a timer with a period 500ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		Realtime.wait_next_activation();
		pthread_mutex_lock(&mutex_realtime);
		line_data.Engine_speed = stoi(tokenized_data[12]);
		//cout<<"Thread Id speed "<<thread_id<<" 500ms "<<data.Engine_speed<<endl;
		pthread_mutex_unlock(&mutex_realtime);


	}


	return (NULL);
}

/**
 * @brief The defined function is used to update the Enginer_coolant_temperature variable in the structure parameter every 2s
 * @param void* arg General pointer passed as an argument to a function. If the argument is to be used it needs to
 * 				be type casted appropriately before usage.
 * @return void*
 */
void* Engine_coolant_temperature(void* arg)
{
	Timer Realtime;
	//int thread_id = pthread_self();
	int timer_res;
	timer_res = Realtime.periodic_timer(OFFSET, PERIOD2s);/// Create a timer with a period 2s
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		Realtime.wait_next_activation();
		pthread_mutex_lock(&mutex_realtime);
		line_data.Enginer_coolant_temperature = stoi(tokenized_data[17]);
		//cout<<"Thread Id Engine Coolant "<<thread_id<<" 2s "<<Enginer_coolant_temperature <<endl;
		pthread_mutex_unlock(&mutex_realtime);
	}

	return (NULL);
}

/**
 * @brief The defined function is used to update the current_gear variable in the structure parameter every 100ms
 * @param void* arg General pointer passed as an argument to a function. If the argument is to be used it needs to
 * 				be type casted appropriately before usage.
 * @return void*
 */
void* Current_gear(void* arg)
{
	Timer Realtime;
	//int thread_id = pthread_self();
	int timer_res;
	timer_res = Realtime.periodic_timer(OFFSET, PERIOD100ms);/// Create a timer with a period 100ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		Realtime.wait_next_activation();
		pthread_mutex_lock(&mutex_realtime);
		line_data.current_gear = stoi(tokenized_data[33]);
		//cout<<"Thread Id Current gear "<<thread_id<<" 100ms "<<line_data.current_gear<<endl;
		pthread_mutex_unlock(&mutex_realtime);

	}

	return (NULL);
}
/**
 * @brief The defined function is used to update the Transmission_oil_temp variable in the structure parameter every 5s
 * @param void* arg General pointer passed as an argument to a function. If the argument is to be used it needs to
 * 				be type casted appropriately before usage.
 * @return void*
 */
void* Transmission_oil_temperature(void* arg)
{
	Timer Realtime;
	//int thread_id = pthread_self();
	int timer_res;
	timer_res = Realtime.periodic_timer(OFFSET, PERIOD5s);/// Create a timer with a period 5s
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		Realtime.wait_next_activation();
		pthread_mutex_lock(&mutex_realtime);
		line_data.Transmission_oil_temp = stoi(tokenized_data[34]);
		//cout<<"Thread Id Transmission Oil temperature  "<<thread_id<<" 5s "<<line_data.Transmission_oil_temp<<endl;
		pthread_mutex_unlock(&mutex_realtime);


	}

	return (NULL);
}

/**
 * @brief The defined function is used to update the vehicle_speed variable in the structure parameter every 100ms
 * @param void* arg General pointer passed as an argument to a function. If the argument is to be used it needs to
 * 				be type casted appropriately before usage.
 * @return void*
 */
void* vehicle_speed(void* arg)
{
	Timer Realtime;
	//int thread_id = pthread_self();
	int timer_res;
	timer_res = Realtime.periodic_timer(OFFSET, PERIOD100ms);/// Create a timer with a period 100ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		Realtime.wait_next_activation();
		pthread_mutex_lock(&mutex_realtime);
		line_data.vehicle_speed = stoi(tokenized_data[43]);
		//cout<<"Thread Id Vehicle speed  "<<thread_id<<" 100ms "<<line_data.vehicle_speed<<endl;
		pthread_mutex_unlock(&mutex_realtime);


	}

	return (NULL);
}

/**
 * @brief The defined function is used to update the accelerarion variable in the structure parameter every 150ms
 * @param void* arg General pointer passed as an argument to a function. If the argument is to be used it needs to
 * 				be type casted appropriately before usage.
 * @return void*
 */
void* Acceleration_speed_longitudinal(void* arg)
{
	Timer Realtime;
	//int thread_id = pthread_self();
	int timer_res;
	timer_res = Realtime.periodic_timer(OFFSET, PERIOD150ms);/// Create a timer with a period 150ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		Realtime.wait_next_activation();
		pthread_mutex_lock(&mutex_realtime);
		line_data.acceleration = stod(tokenized_data[44]);
		//cout<<"Thread Id Acceleration speed "<<thread_id<<" 150ms "<<line_data.acceleration<<endl;
		pthread_mutex_unlock(&mutex_realtime);


	}

	return (NULL);
}

/**
 * @brief The defined function is used to update the brake_switch_indicator variable in the structure parameter every 100ms
 * @param void* arg General pointer passed as an argument to a function. If the argument is to be used it needs to
 * 				be type casted appropriately before usage.
 * @return void*
 */
void* Indication_of_break_switch(void* arg)
{
	Timer Realtime;
	//int thread_id = pthread_self();
	int timer_res;
	timer_res = Realtime.periodic_timer(OFFSET, PERIOD100ms);/// Create a timer with a period 100ms
	if (timer_res < 0 ){
		perror("Start periodic timer");
	}

	while(1)
	{
		Realtime.wait_next_activation();
		pthread_mutex_lock(&mutex_realtime);
		line_data.Brake_switch_indicator = stoi(tokenized_data[45]);
		//cout<<"Thread Id brake switch "<<thread_id<<" 100ms "<<line_data.Brake_switch_indicator<<endl;
		pthread_mutex_unlock(&mutex_realtime);
	}

	return (NULL);
}

/**
 * @brief The defined function is used to display the data from the respective sensor variables every 500ms
 * @param No arguments
 * @return void
 */
void update_console()
{
	cout<<"Fuel Consumption: "<<line_data.fuel_consumption<<" "<<"Engine Speed: "<<line_data.Engine_speed<<" "<<"Engine Coolant Temperature: "<<line_data.Enginer_coolant_temperature<<" "<<"Current Gear: "<<line_data.current_gear<<" "<<"Transmission Oil temperature: "<<line_data.Transmission_oil_temp<<" "<<"Vehicle Speed: "<<line_data.vehicle_speed<<" "<<"Acceleration speed Longitudinal:"<<line_data.acceleration<<" "<<"Indication of break switch: "<<line_data.Brake_switch_indicator<<" "<<endl;
}

/**
 * @brief The defined function is used to create threads, initiate mutex and destroy them on completion
 * @param No arguments
 * @return void
 */
int main(void)
{
	  pthread_t get_data,Fuel_conmp,Eng_speed,Eng_coolant_temp,Curr_gear,Transm_oil_temp,Vehicle_speed,Accl_Spd,break_switch;
	  Timer Realtime;/// Timer class object
	  pthread_create(&get_data,NULL,&Store_data_in_vector,NULL);
	  pthread_create(&Fuel_conmp,NULL,&Fuel_consumption,NULL);
	  pthread_create(&Eng_speed,NULL,&Engine_speed,NULL);
	  pthread_create(&Eng_coolant_temp,NULL,&Engine_coolant_temperature,NULL);
	  pthread_create(&Curr_gear,NULL,&Current_gear,NULL);
	  pthread_create(&Transm_oil_temp,NULL,&Transmission_oil_temperature,NULL);
	  pthread_create(&Vehicle_speed,NULL,&vehicle_speed,NULL);
      pthread_create(&Accl_Spd,NULL,&Acceleration_speed_longitudinal,NULL);
	  pthread_create(&break_switch,NULL,&Indication_of_break_switch,NULL);
	  pthread_mutex_init(&mutex_realtime, NULL);
	  int res;

		///set and activate a timer
		res = Realtime.periodic_timer(OFFSET, PERIOD500ms);/// Create a timer with a period 500ms
		if (res < 0 ){
			perror("Start periodic timer");
			return -1;
		}

		while (1) {
			Realtime.wait_next_activation(); /// Wait for signal activation
			pthread_mutex_lock(&mutex_realtime);///Lock variable
			update_console();///Display to the console
			pthread_mutex_unlock(&mutex_realtime);///Unlock Variable
		}
		pthread_mutex_destroy(&mutex_realtime);
		return 0;
}

