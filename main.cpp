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

int sign(float value){
    if(value > 0) {return 1;}
    else if(value == 0) {return 0;}
    else {return -1;}
}

float compute_roll(float accel_x, float accel_y, float accel_z){
    float num = accel_y;
    float den = sign(accel_z)*sqrt(pow(accel_z, 2) + MI*pow(accel_x, 2));

    return atan2(num, den)*RAD_TO_DEG;
}

float compute_pitch(float accel_x, float accel_y, float accel_z){
    float num = -accel_x;
    float den = sqrt(pow(accel_y, 2) + pow(accel_z, 2));

    return atan2(num, den)*RAD_TO_DEG;
}

string float_to_string(float value){
    stringstream ss;
    ss << value;
    return ss.str();
}

vector<float> read_line(string line){
    stringstream line_ss(line);
    vector<float> data;

    for (int i=0 ; i<=3; i++){
        string value;
        getline(line_ss, value, DELIMITER);
        data.push_back(stof(value));
    }
    return data;
}

void write_line(fstream &stream, float timestamp, float roll, float pitch){
    string line = float_to_string(timestamp) + ", ";
    line.append(float_to_string(roll) + ", ");
    line.append(float_to_string(pitch) + "\n");

    stream << line;
    return;
}

int main(){
    vector<float> timestamp;
    vector<float> accel_x, accel_y, accel_z;

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

    fstream result;
    result.open("result.log", ios::out);
    if(result.is_open()){
        for(int i=0 ; i<rows ; i++){
            write_line(result, time_stamp[i], roll_angle[i], pitch_angle[i]);
        }
        result.close();
    }

    return 0;
}
