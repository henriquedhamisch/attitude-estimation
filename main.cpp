// #include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

const char DELIMITER = ';';
const char NEW_LINE = '\n';
const float MI = 0.01;
const float RAD_TO_DEG = 180/M_PI;

vector<float> time_stamp;
vector<float> accel_x;
vector<float> accel_y;
vector<float> accel_z;


int sign(int value){
    if(value > 0) {return 1;}
    else if(value == 0) {return 0;}
    else {return -1;}
}

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

    int rows = time_stamp.size();

    vector<float> roll_angle;
    vector<float> pitch_angle;

    for (int i=0 ; i<rows ; i++){
        roll_angle.push_back(atan2(accel_x[i], sign(accel_z[i]*sqrt(pow(accel_z[i],2) + MI*pow(accel_x[i],2))))*RAD_TO_DEG);
        pitch_angle.push_back(atan2(-accel_x[i], sqrt(pow(accel_y[i],2) + pow(accel_z[i],2)))*RAD_TO_DEG);
    }

    return 0;
}
