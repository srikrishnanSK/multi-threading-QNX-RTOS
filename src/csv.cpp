/**
 *  @file csv.cpp.
 *  @author Srikrishnan Venkatasubramanian.
 */

#include "csv.h"
/** Default constructor stub that can be used based on requirement and design*/
csv::csv() {


}

/** Default destructor stub that can be used based on requirement and design*/
csv::~csv() {

}

/**
 * @brief The below function is used to read a particular line from a file. It sets the file pointer for seekg
 * 				to the line number.
 * @param std::fstream& file File handler provided as input from the read_csv_line(int line_number) function.
 * @param unsigned int num Line number to be read from the file.
 * @return std::fstream File pointer.
 */
std::fstream& csv::GotoLine(std::fstream& file, unsigned int num)
{
    file.seekg(std::ios::beg);
    for(unsigned int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;

}

/**
 * @brief Reads a particular line from a file, and tokenizes them into words using the delimitter ",". The
 * 				words are then stored into a vector which is returned by the function.
 * @param int line_number Get the line number to be read from a particular file.
 * @return vector<string>
 */
vector<string> csv::read_csv_line(int line_number)
{
    fstream file(FILENAME);
    string line,word;
    vector<string> data;
    data.clear();
    GotoLine(file, line_number);
    getline(file,line);
    stringstream tokenize(line);
    while (getline(tokenize, word, ','))
    {

        data.push_back(word);
    }
return data;
}


