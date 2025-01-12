#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

int countDecimalPlaces(long double num) {
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

    
    if(countDecimalPlaces(a) == 0 && countDecimalPlaces(b) == 0 && ((a != 0 && b != 0))){
        width = to_string(static_cast<long long>(a * b)).length();
    }
    else if(a == 0 || b == 0){
        width = max(to_string(static_cast<long long>(a)).length(), to_string(static_cast<long long>(a)).length());
    }
    else{
        width = to_string(static_cast<long long>(a * b)).length()
        + countDecimalPlaces(a) + countDecimalPlaces(b) + 1;
    }
    
    
    return width;
}

void countColumnSums(vector<long long> &res, vector<int> &positions, vector<int> &columnSums) {

    int maxColumn = 0;
    for (size_t i = 0; i < res.size(); i++) {
        int columnPosition = to_string(res[i]).length() + positions[i] - 1;
        maxColumn = max(maxColumn, columnPosition);
    }

    columnSums.assign(maxColumn + 1, 0);

    for (size_t i = 0; i < res.size(); i++) {
        long long value = res[i];
        int pos = positions[i];

        int column = pos;
        while (value > 0) {
            columnSums[column] += value % 10; 
            value /= 10; 
            column++;
        }
    }

    for (size_t i = 0; i < columnSums.size(); i++) {
        if (columnSums[i] >= 10) {
            if (i + 1 >= columnSums.size()) {
                columnSums.push_back(0);
            }
            columnSums[i + 1] += columnSums[i] / 10; 
            columnSums[i] %= 10; 
        }
    }
}

bool isPowerOfTen(long long n) {
    if (n <= 0) return false;  
    while (n % 10 == 0) {
        n /= 10;  
    }
    return n == 1;  
}

void writeColumnMultiplication(long double a, long double b){
    vector<long long> res;
    vector<int> pos;
    
    bool lo(to_string(static_cast<long long>(a)).length() + countDecimalPlaces(a) 
    >= to_string(static_cast<long long>(b)).length() + countDecimalPlaces(b));
    
    int aDecimalPlaces = countDecimalPlaces(a);
    int bDecimalPlaces = countDecimalPlaces(b);
   
    int totalDecimalPlaces = aDecimalPlaces + bDecimalPlaces;
    long long intA = static_cast<long long>(round(a * pow(10, aDecimalPlaces)));
    long long intB = static_cast<long long>(round(b * pow(10, bDecimalPlaces)));

    int width;
    if(isPowerOfTen(intA) || isPowerOfTen(intB)){
        width = findWidth(a, b) - 1;
    }else{width = findWidth(a, b);}

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

    if(a == 0 || b == 0){ 
        cout << right << setw(width) << 0;
        return;
    }

    long long sum = 0;
    int constDec = lo ? aDecimalPlaces : bDecimalPlaces;
    if(res.size() == 1){
        cout << right << setw(width) << fixed << setprecision(totalDecimalPlaces) 
        << res[0] / pow(10, totalDecimalPlaces) << endl;
        return;
    }
    else if(isPowerOfTen(intA) || isPowerOfTen(intB)){
        cout << right << setw(width) << a * b << endl;
        return;
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
                    else if(totalDecimalPlaces - pos[i] <= 0){
                        cout << right << setw(width - pos[i] - 1)  << setprecision(0)
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

        }
        cout << setw(width) << setfill('-') << "" << endl;
        cout << setfill(' ');

        vector<int> columnSums;
        countColumnSums(res, pos, columnSums);

        if(totalDecimalPlaces != 0){
            for(int i = columnSums.size() - 1; i >= 0 ; i--){
                cout << columnSums[i];
                if(i == totalDecimalPlaces){
                    cout << '.';
                }
            }
        }
        else{
             for(int i = columnSums.size() - 1; i >= 0 ; i--){
                    cout << columnSums[i];
            }
        }
    }
   
}


int main() {
    long double a, b;

    cin >> a >> b;
    writeColumnMultiplication(a, b);
    
    

    return 0;
}
