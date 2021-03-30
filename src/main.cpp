/*
 *@file main.cpp
 *@author Srikrishnan Venkatasubramanian
 *
 */

#include "Realtimemon.h"

/**
 * @brief   The defined function acts the entry point that allows us to achieve the defined project requirements. 9 threads are created
 * 		   	of which one thread is used to read data from csv, 8 are used to update the variables of interest using a shared structure, and
 * 		   	main thread is used to display the variables to the console. Further, Realtimemon class object is created aand is used to access
 * 		   	class methods and passed as an object to required threads.
 * @param  void
 * @return int returns 0 on success and -1 on failure
 */
int main(void)
{

		  pthread_t get_data,Fuel_conmp,Eng_speed,Eng_coolant_temp,Curr_gear,Transm_oil_temp,Vehicle_speed,Accl_Spd,break_switch;
		  Realtimemon *monitor = new Realtimemon();
		  pthread_create(&get_data,NULL,&monitor->Store_data_in_vector,monitor);
		  pthread_create(&Fuel_conmp,NULL,&monitor->Fuel_consumption,monitor);
		  pthread_create(&Eng_speed,NULL,&monitor->Engine_speed,monitor);
		  pthread_create(&Eng_coolant_temp,NULL,&monitor->Engine_coolant_temperature,monitor);
		  pthread_create(&Curr_gear,NULL,&monitor->Current_gear,monitor);
		  pthread_create(&Transm_oil_temp,NULL,&monitor->Transmission_oil_temperature,monitor);
		  pthread_create(&Vehicle_speed,NULL,&monitor->vehicle_speed,monitor);
	      pthread_create(&Accl_Spd,NULL,&monitor->Acceleration_speed_longitudinal,monitor);
		  pthread_create(&break_switch,NULL,&monitor->Indication_of_break_switch,monitor);
		  int res;

		  ///set and activate a timer
		  res = monitor->timer_create(PERIOD250ms);
		  if (res < 0 ){
				perror("Start periodic timer");
				return -1;
			}

			while (1) {
				monitor->wait_for_signal();/// Wait for signal activation
				monitor->lock_variable();
				monitor->update_console();///Display to the console
				monitor->unlock_variable();
			}
			delete monitor;
			return 0;

}




