#include <ArduinoSTL.h>

#include <StaticThreadController.h>
#include <Thread.h>
#include <ThreadController.h>

#include <Array.h>

#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <EasyStringStream.h>

#include <bitset>
#include <cctype>
#include <algorithm>
//#include <fstream>
#include <functional>
#include <iosfwd>
#include <list>
#include <map>
#include <memory>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
//#include <thread>
//#include <tuple>

using namespace std;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display

int contrast_level = 90; //this value might need to be changed depending on your LCD

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
  }

float applyOp(float a, float b, char op) {
    switch(op) {
      case '+': return a + b;
      case '-': return a - b;
      case '*': return a * b;
      case '/': return a / b; 
    }
  }

  float evaluate(string tokens) {
    int i;
    stack <float> values;
    stack <char> ops;

    for(i = 0; i < tokens.length(); i++){

      if(isdigit(tokens[i])) {
        float val = 0;

      while(i < tokens.length() && isdigit(tokens[i])) {
        val = (val*10) + (tokens[i]-'0');
        i++;
      }

      values.push(val);
      i--;
    }

      else {
        while(!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {

          float val2 = values.top();
          values.pop();

          float val1 = values.top();
          values.pop();

          char op = ops.top();
          ops.pop();

          values.push(applyOp(val1, val2, op));

        }
        ops.push(tokens[i]);
      }
  }

  while(!ops.empty()) {
    float val2 = values.top();
    values.pop();

    float val1 = values.top();
    values.pop();

    char op = ops.top();
    ops.pop();

    values.push(applyOp(val1, val2, op));
  }

  return values.top();
  }

  string make_string(int a) {
    if (a == 1) { return "1"; }
    else if (a == 2) {return "2";}
    else if (a == 3) {return "3";}
    else if (a == 4) {return "4";}
    else if (a == 5) {return "5";}
    else if (a == 6) {return "6";}
    else if (a == 7) {return "7";}
    else if (a == 8) {return "8";}
    else if (a == 9) {return "9";}
  }


  int three() {

    bool found = false;

    string num1, num2, num3, num4, num5;

    vector<string> ans;
    int j = 0;

    while(found == false) {
      srand(time(0));
      randomSeed(analogRead(0));

      num1 = make_string(random(1,10));
      num2 = make_string(random(1,10));
      num3 = make_string(random(1,10));
      num4 = make_string(random(1,10));
      num5 = make_string(random(1,10));

      int myints[] = {1, 2, 3, 4};

      sort(myints, myints + 3);

      lcd.setCursor(0, 0);

      do {
        string ops[4];
        string equationtest;
        for (int i = 0; i < 3; i++) {
          if (myints[i] == 1) { ops[i] = '+';}
          else if (myints[i] == 2) {ops[i] = '-';}
          else if (myints[i] == 3) {ops[i] = '*';}
          else {ops[i] = '/';}
        }

        string type1side1 = num1;
        string type1side2 = num2 + ops[0] + num3 + ops[1] + num4 + ops[2] + num5;
        string type2side1 = num1 + ops[0] + num2;
        string type2side2 = num3 + ops[1] + num4 + ops[2] + num5;
        string type3side1 = num1 + ops[0] + num2 + ops[1] + num3;
        string type3side2 = num4 + ops[2] + num5;
        string type4side1 = num1 + ops[0] + num2 + ops[1] + num3 + ops[2] + num4;
        string type4side2 = num5;

        if (evaluate(type1side1) == evaluate(type1side2)) {
          //cout << type1side1 << "=" << type1side2 << endl;
          ans.push_back(type1side1 + "=" + type1side2);
          found = true;
        }
        if (evaluate(type2side1) == evaluate(type2side2)) {
          //cout << type2side1 << "=" << type2side2 << endl;
          ans.push_back(type2side1 + "=" + type2side2);
          found = true;
        }
        if (evaluate(type3side1) == evaluate(type3side2)) {
          //cout << type3side1 << "=" << type3side2 << endl;
          ans.push_back(type3side1 + "=" + type3side2);
          found = true;
        }
        if (evaluate(type4side1) == evaluate(type4side2)) {
          //cout << type4side1 << "=" << type4side2 << endl;
          ans.push_back(type4side1 + "=" + type4side2);
          found = true;
        }
      }
        while (next_permutation(myints, myints + 4));
      }
    
    string printtest = num1 + "_" + num2 + "_" + num3 + "_" + num4 + "_" + num5;

    lcd.print(printtest.c_str());

    }

void setup() {


  //these two lines are used to set the contrast level for the LCD
  pinMode(6, OUTPUT);
  analogWrite(6, contrast_level);
  lcd.begin(10, 1);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display

  three();
  
  }


void loop() {

         //print hello, world! starting at that position

}
