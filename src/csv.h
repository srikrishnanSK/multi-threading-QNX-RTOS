/**
 *  @file csv.h.
 *  @author Srikrishnan Venkatasubramanian.
 *  @brief The Comma separated files (CSV) contains data of varying datatypes integer, string, double, float and depends on the provided dataset
 *	where the data collected may vary based on the given application. The csv class has been created to read a particular line from a given
 *	file and tokenize them according to requirement. The functions have been defined based on the requirements provided in the project
 *	description. Each line in the given dataset represents data from different sensors that have been collected every 1 second.
 */

#ifndef CSV_H_
#define CSV_H_ /**< Header gaurd to include certain files*/
#define FILENAME "/tmp/dataset.csv"/**<Default path to the file on the target.*/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

class csv {
protected:
	csv();///Constructor
	virtual ~csv();///Destructor
    vector<string> read_csv_line(int line_number);///Gets the particular line number to be read
    std::fstream& GotoLine(std::fstream& file, unsigned int num);///Take the file handler and line number to be read from the given file
};

#endif /** CSV_H_ */
