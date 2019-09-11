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
const float MG_TO_G = 0.001;
const float MS_TO_S = 0.001;

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
    stream.setf(ios::fixed, ios::floatfield);
    stream.precision(3);
    stream << timestamp << " s:\t";
    stream << roll << "  ,  ";
    stream << pitch << "\n";
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
            vector<float> data = read_line(line);

            timestamp.push_back(data[0]*MS_TO_S);
            accel_x.push_back(data[1]*MG_TO_G);
            accel_y.push_back(data[2]*MG_TO_G);
            accel_z.push_back(data[3]*MG_TO_G);
        }
        log.close();
    }

    fstream result;
    result.open("result.log", ios::out);
    result << "Results - Estimator for roll and pitch angles\n\n";
    result << "Data format:\n";
    result << "Timestamp [s]:\tRoll [deg]   ,   Pitch [deg]\n\n";
    while(result.is_open()){
        for(int i=0 ; i<timestamp.size() ; i++){
            float roll_angle = compute_roll(accel_x[i], accel_y[i], accel_z[i]);
            float pitch_angle = compute_pitch(accel_x[i], accel_y[i], accel_z[i]);
            write_line(result, timestamp[i], roll_angle, pitch_angle);
        }
        result.close();
    }

    return 0;
}
