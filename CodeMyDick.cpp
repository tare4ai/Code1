#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

int countDecimalPlaces(double num) {
    string str = to_string(num);
    str.erase(str.find_last_not_of('0') + 1, string::npos);
    size_t pos = str.find('.');
    if (pos != string::npos) {
        return str.length() - pos - 1;
    }
    return 0; 
}

void countColumnMultiplication(vector<long long> &res, vector<int> &pos, long long intNum, long long intNum2)
{
    long long multiplier = intNum;
        int position = 0;
        while (multiplier > 0) {
        
            long long digit = multiplier % 10;
            if(digit > 0){
                res.push_back(intNum2 * digit);
            }
            else{
                res.push_back(0);
            }
            multiplier /= 10;
            pos.push_back(position);
            position++;

        }
}

int findWidth(double a, double b){
    string str1 = to_string(a);
    string str2 = to_string(b);
    int width;
    
    str1.erase(str1.find_last_not_of('0') + 1, string::npos);
    str2.erase(str2.find_last_not_of('0') + 1, string::npos);
    str1.erase(str1.find_last_not_of('.') + 1, string::npos);
    str2.erase(str2.find_last_not_of('.') + 1, string::npos);

    
    if(countDecimalPlaces(a) == 0 && countDecimalPlaces(b) == 0){
        width = to_string(static_cast<long long>(a * b)).length();
    }
    else{
        width = to_string(static_cast<long long>(a * b)).length()
        + countDecimalPlaces(a) + countDecimalPlaces(b) + 1;
    }
    
    
    return width;
}

void writeColumnMultiplication(double a, double b){
    vector<long long> res;
    vector<int> pos;
    bool lo(to_string(static_cast<long long>(a)).length() + countDecimalPlaces(a) >= to_string(static_cast<long long>(b)).length() + countDecimalPlaces(b));
    int width = findWidth(a, b);
    int aDecimalPlaces = countDecimalPlaces(a);
    int bDecimalPlaces = countDecimalPlaces(b);

    int totalDecimalPlaces = aDecimalPlaces + bDecimalPlaces;
    long long intA = static_cast<long long>(round(a * pow(10, aDecimalPlaces)));
    long long intB = static_cast<long long>(round(b * pow(10, bDecimalPlaces)));

    if(lo){
        cout << right << setw(width) << fixed << setprecision(countDecimalPlaces(a)) << a << endl;
        cout << right << setw(width) << fixed << setprecision(countDecimalPlaces(b)) << b << endl;
        cout << setw(width) << setfill('-') << "" << endl;
        cout << setfill(' ');
        countColumnMultiplication(res, pos,intB, intA);
    }
    else{
        cout << setw(width) << right << fixed << setprecision(countDecimalPlaces(b)) << b << endl;
        cout << setw(width) << right << fixed << setprecision(countDecimalPlaces(a)) << a << endl;
        cout << setw(width) << setfill('-') << "" << endl;
        cout << setfill(' ');
        countColumnMultiplication(res, pos, intA, intB);
    }

    long long sum = 0;
    int constDec = lo ? aDecimalPlaces : bDecimalPlaces;
    if(res.size() == 1){
        cout << right << setw(width) << fixed << setprecision(totalDecimalPlaces) 
        << res[0] / pow(10, totalDecimalPlaces) << endl;
    }
    else{
        for(int i = 0; i < res.size(); i++){
            if(res[i] > 0){
                if(totalDecimalPlaces != 0){
                    if(totalDecimalPlaces - pos[i] > 0){
                        cout << right << setw(width - pos[i]) << fixed 
                        << setprecision(totalDecimalPlaces - pos[i]) 
                        << res[i] / pow(10, totalDecimalPlaces - pos[i]) << endl;
                    }
                    else if(totalDecimalPlaces - pos[i] == 0){
                        cout << right << setw(width - pos[i] - 1) << setprecision(0)
                        << res[i] / pow(10, totalDecimalPlaces - pos[i]) << '.' << endl;
                    }
                    else{
                        cout << right << setw(width - pos[i]) << res[i] << endl;
                    }
                }
                else{
                    cout << right << setw(width - pos[i]) << res[i] << endl;
                }
            }
            sum += res[i] * pow(10, i);

        }
        cout << setw(width) << setfill('-') << "" << endl;
        cout << setfill(' ');
        cout << right << setw(width) << fixed << setprecision(totalDecimalPlaces) 
        << static_cast<double> (sum) / pow(10, totalDecimalPlaces);
    }
   
}


int main() {
    double a, b;
    cin >> a >> b;
    writeColumnMultiplication(a, b);
    
    

    return 0;
}
