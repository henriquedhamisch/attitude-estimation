// #include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

const char DELIMITER = ';';
const char NEW_LINE = '\n';

vector<float> time_stamp;
vector<float> accel_x;
vector<float> accel_y;
vector<float> accel_z;


int main(){
    fstream log;
    log.open("data.log", ios::in);          // Open log file into the stream object

    while(log.is_open()){
        string line;
        while(getline(log, line, NEW_LINE)){
            stringstream line_ss(line);
            for (int i=0 ; i<=3; i++){
                string value;
                getline(line_ss, value, DELIMITER);

                if(i == 0) { time_stamp.push_back(stof(value)); }
                else if(i == 1) { accel_x.push_back(stof(value)); }
                else if(i == 2) { accel_y.push_back(stof(value)); }
                else if(i == 3) { accel_z.push_back(stof(value)); }
            }
        }
        log.close();
    }

    return 0;
}
