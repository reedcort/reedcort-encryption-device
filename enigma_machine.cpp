/*
 *
 *
 *
 * Compile as follows: g++ -o enigma_machine enigma_machine.cpp -O3 -Wall -std=c++11 -lm
 *
 * Author: Cortney Reed
 * Date created: May 6,2020
 *
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <map>
#include "header.h"
#include <cmath>
#include <cstring>


using namespace std;

string key_10;
string key_3;
char msg[256];
string option;
string en_msg;
string de_msg;
int num;
int flag(0);

int main (){
  
  cout << "Welcome to the crypto machine similar to the Enigma"<<endl;

  while(flag == 0){
    cout <<"\t1. Encrypt msg.\n"
     <<"\t2. Decryot msg.\n"
     <<"Select an option: ";
    getline(cin,option);
    stringstream(option) >> num;
    switch(num){
    case 1:{
      //User enters 10-character string key
      cout << "Enter 10-character string key: ";
      getline(cin,option);
      if (option.length() != 10 ){
          cout << "Key must be 10 characters\n";
        flag=1;
          break;
      }
      key_10 = option;

      //User enters 3-character string key
      cout << "Enter 3-character string key (left to right): ";
      getline(cin,option);
      if (option.length() != 3 ){
          cout << "Key must be 3 characters\n";
        flag=1;
          break;
      }
      key_3 = option;
    //The 3-char key parsed into thre variables
      string key_3_1(1, key_3[0]);
      string key_3_2(1, key_3[1]);
      string key_3_3(1, key_3[2]);

    //Input message to encrypt
      cout << "Enter a message to encrypt (no special characters): ";
      cin.getline(msg,256);
      cout << "\n";
      if (strlen(msg) <= 0 ){
          cout << "Password cannot be empty\n";
          break;
      }
      else{
        unordered_map<int,string> m;
        unordered_map<int,string> spaces;
        
        //characters in string ar put in hash table
        for (int i=0,k =0; k < (signed)strlen(msg); i++,k++){
          if (msg[k] == ' '){
            spaces[k]=msg[k];
            i--;
            continue;
          }
          m[i]=msg[k];
        }

        string nw_msg;
        string num1;
        int num2;

  
        //characters in string are transposed
        if(key_10.length()>m.size()){
            string tmp;
           for (int i =0; i < (signed)m.size(); i++){
            string beta(1,key_10[i]);
            tmp.append(beta);
           }
           key_10 = tmp;
        }
        else if(m.size() % key_10.length()== 0 or m.size() > key_10.length()){
          float iter = ceil((double)m.size() / 10.0);
          // cout <<(double)m.size()<<"\n";
          // cout <<iter<<"\n";
          for (int i =1; i<iter;i++){
            key_10.append(key_10);
            
          }
        }


        for (int i =0; i < (signed)m.size(); i++){
          num1 = key_10[i];
          num2 = stoi(num1);
          nw_msg.append(m.find(num2)->second);
        }
        
        for (int i =0; i <36; i++){
          if (left_rotor[i] == key_3_1){
            left_pos = i;
          }
          if (middle_rotor[i] == key_3_2){
            middle_pos = i;
          }
          if (right_rotor[i] == key_3_3){
            right_pos = i;
          }
        }
        
        init_rotorI(left_pos);
        init_rotorII(middle_pos);
        init_rotorIII(right_pos);
        string temp;
        int value;
        
    //Each character is encrypted
        for (int i = 0; i < (signed)nw_msg.length();i++){
          string alpha(1,nw_msg[i]);
          value =  key.find(alpha)->second;
          temp = nw_right_rotor.find(value)->second;
          value = key.find(temp)->second;
          temp.clear();
          temp = nw_middle_rotor.find(value)->second;
          value = key.find(temp)->second;
          temp.clear();
          temp = nw_left_rotor.find(value)->second;
          en_msg.append(temp);
          temp.clear();
          
          rotorIII();

          if ((i+1) % 7 == 0){
            rotorII();
          }
          if ((i+1) % 5 == 0){
            rotorI();
          }

        }
        //Adds spaces back if necessary
        for (int i = 0; i < (signed)en_msg.length()+1; i++)
        {
          if ( spaces.find(i) == spaces.end() ) {
            continue;
          }
          else{
            en_msg.insert(i, spaces.find(i)->second);
          }
        }
        
        cout <<"Encrypted message: "<< en_msg;
        cout<<"\n";
        flag=1;
        break;
      }
        
    }

            
//Option two: Decrypt message
    case 2:{
    //User enters 10-character string key
      cout << "Enter 10-character string key: ";
      getline(cin,option);
      if (option.length() != 10 ){
          cout << "Key must be 10 characters\n";
        flag=1;
          break;
      }
      key_10 = option;

      //User enters 3-character string key
      cout << "Enter 3-character string key (left to right): ";
      getline(cin,option);
      if (option.length() != 3 ){
          cout << "Key must be 3 characters\n";
        flag=1;
          break;
      }
      key_3 = option;
    //The 3-char key parsed into thre variables
      string key_3_1(1, key_3[0]);
      string key_3_2(1, key_3[1]);
      string key_3_3(1, key_3[2]);
        
    //input encrypted message
      cout << "Enter a message to decrypt: ";
      cin.getline(msg,256);
      cout << "\n";
      if (strlen(msg) == 0 ){
          cout << "Password cannot be empty\n";
          break;
      }
      else{
        unordered_map<int,string> m;
        unordered_map<int,string> spaces;
        //characters in string are put in hash table
        for (int i=0,k =0; k < (signed)strlen(msg); i++,k++){
          if (msg[k] == ' '){
            spaces[k]=msg[k];
            i--;
            continue;
          }
          m[i]=msg[k];
        }

        string nw_msg;
        string num1;
          
        if(key_10.length()>m.size()){
            string tmp;
           for (int i =0; i <(signed) m.size(); i++){
            string beta(1,key_10[i]);
            tmp.append(beta);
           }
           key_10 = tmp;
        }
        else if(m.size() % key_10.length()== 0 or m.size() > key_10.length()){
          float iter = ceil((double)m.size() / 10.0);
            
          for (int i =1; i<iter;i++){
            key_10.append(key_10);
          }
        }
  
        for (int i =0; i < (signed)m.size(); i++){
          nw_msg.append(m.find(i)->second);

        }
       
        for (int i =0; i <36; i++){
          if (left_rotor[i] == key_3_1){
            left_pos = i;
          }
          if (middle_rotor[i] == key_3_2){
            middle_pos = i;
          }
          if (right_rotor[i] == key_3_3){
            right_pos = i;
          }
        }
        init_rotorI(left_pos);
        init_rotorII(middle_pos);
        init_rotorIII(right_pos);
        string temp2;
        int value;
        for (int i = 0; i < (signed)nw_msg.length();i++){
          string alpha(1,nw_msg[i]);
          value = rev_nw_left_rotor.find(alpha)->second;
          temp2 = rev_key.find(value)->second;
          value = rev_nw_middle_rotor.find(temp2)->second;
          temp2.clear();
          temp2 = rev_key.find(value)->second;
          value = rev_nw_right_rotor.find(temp2)->second;
          temp2.clear();
          temp2 = rev_key.find(value)->second;
          de_msg.append(temp2);
          temp2.clear();
          
          rotorIII();

          if ((i+1) % 7 == 0){
            rotorII();
          }
          if ((i+1) % 5 == 0){
            rotorI();
          }
        
        }
       
        string message;
        int num2;
        string q;

    //characters in string rearranged according to 10-char key
        int sze= (signed)m.size();
        m.clear();
        for (int i =0; i < sze; i++){
          q = key_10[i];
          num2 = stoi(q);
          if(i>9){
            int indx = floor(i/10);
            m[num2+(indx*10)] = de_msg[i];
            continue;
          }
          m[num2] = de_msg[i];
          
        }

        for (int i =0; i < (signed)de_msg.length(); i++){
          message.append(m.find(i)->second);
        }

        for (int i = 0; i < (signed)message.length()+1; i++)
        {
          if ( spaces.find(i) == spaces.end() ) {
            continue;
          }
          else{
            message.insert(i,spaces.find(i)->second);
          }
        }
      cout <<"Decrypted message: "<< message;
      cout<<"\n";
      flag=1;
      break;
        
      }
  }
    
  }
        
  }
      
}


