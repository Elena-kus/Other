#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

bool is_num(char s) { 
    if ((s <= '9') && ( s >= '0' ))   
    return true;
    else return false;
}

string derivative(string polynomial) {
    
     map <int, int, greater<int>> pow_coef;
    stringstream value(polynomial);
    int x;
    int y;
    int z = 1;
    char c;

while ( value.peek() != EOF) {
    if (value.peek() != '+' && value.peek() != '-') {    
        if (is_num(value.peek())) {       
            value >> x;    
            if(value.peek() == EOF) {       
                pow_coef[0] = z*x;
                break;}
            if(value.peek() == '*') {
                value.ignore(2);
                if(value.peek() == EOF) {         
                    pow_coef[1] += z*x;
                break;}
                if(value.peek() == '^'){
                    value.ignore(1);
                    value >> y;
                    pow_coef[y] += z*x;               
                } else pow_coef[1] += z*x;
            } else pow_coef[0] += z*x;        
        } else {
            x = z;
            value.ignore(1);
            if(value.peek() == EOF) {
                pow_coef[1] += x;
                break;}
            if(value.peek() == '^') {            
                value.ignore(1);
                value >> y;
                pow_coef[y] += x;
            } else pow_coef[1] += x;
        }
    } else {
        value >> c;
        if ( c == '-')
            z = -1;
        else 
        z = 1;
   }
}
    
string result;

for (auto p : pow_coef) {
    if(p.first == 1) {
        if(p.second > 0)
        result = result + '+' + to_string(p.second);
        else
        result += to_string(p.second);
    }
    if(p.first == 2) {
        if(p.second > 0)
        result = result + '+' + to_string(p.second*p.first) + "*x";
        else
        result = result + to_string(p.second*p.first)  + "*x"; 
    }
    if( p.first > 2) {
        if(p.second > 0)
        result = result + '+' + to_string(p.second*p.first) + "*x^" 
        + to_string(p.first - 1);
        else
        result = result + to_string(p.second*p.first) + "*x^" 
        + to_string(p.first - 1);
    }
}

    if (result[0] == '+')
    result.erase(0,1);
    
    return result;
}
