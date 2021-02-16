// Preet Panchal
// 100707094
// CSCI1061U - LAB02
// LAB CRN: 73921 - SEC: 005
// January 30, 2021

// part4.cpp

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string> 

using namespace std; 

//functions now include another parameter for the digit shift values
string encrypt(string message, int Lshift, int Dshift); //declaring encryption function
string decrypt(string message, int rev_Lshift, int rev_Dshift); //declaring decryption function 

//main function includes commandline arguments as parameters
int main(int argc, char* argv[]) {

    //converting all neccessary arguments to respective variables
    string cipher_type = argv[1]; //these three arguments will always exist in both methods
    int Lshift = atoi(argv[2]); 
    int Dshift = atoi(argv[3]); 

    //this program is able to distinguish between both standard commandline testing
    //and also auto-testing using IO REDIRECTION
    //if there are only 4 arguments detected, it will continue to process the cipher
    //using cin and cout otherwise it will process the files using the fstream library functions

    if (argc == 4) { //code remains same as in part 3 for io redirection
        if (cipher_type == "-e") {
            string line; 
            while (getline(cin, line)) {
                string cipherText = encrypt(line, Lshift, Dshift);  
                cout << cipherText << endl; 
            }
        } else {
            string line; 
            while (getline(cin, line)) {
                string plainText = decrypt(line, Lshift, Dshift);  
                cout << plainText << endl; 
            }
        }
    } else { //code remains same for standard files reading and writing 
        string inFile_name = argv[4]; //converting file names to string when performing IO REDIRECTION
        string outFile_name = argv[5]; //this is the only time they are considered arguments 

        ifstream inf(inFile_name); 

        if (inf.is_open()) {
            if (cipher_type == "-e") {
                string line; 
                ofstream outf(outFile_name); 
                while (getline(inf, line)) {
                    string cipherText = encrypt(line, Lshift, Dshift);  
                    outf << cipherText << endl; 
                }
                outf.close(); 
                inf.close(); 
            } else {
                string line; 
                ofstream outf(outFile_name); 
                while (getline(inf, line)) {
                    string plainText = decrypt(line, Lshift, Dshift);  
                    outf << plainText << endl; 
                }
                outf.close(); 
                inf.close(); 
            }
        } 
    }

    return 0; 
}

//encryption function now includes four cases where it checks blanks
//digits, uppercase and lowercase and it completes the cipher respectively
string encrypt(string message, int Lshift, int Dshift) {
    string result = ""; 
    for (int i=0; i<message.length(); ++i) {
        if (isblank(message[i])) {
            result += char(message[i]);
        } 
        else if (isdigit(message[i])) { 
            result += char(int(message[i] + Dshift - '0' + 10) % 10 + '0'); 
        } 
        else if (isupper(message[i])) {
            result += char(int(message[i] + Lshift - 'A' + 26) % 26 + 'A'); 
        } else {
            result += char(int(message[i] + Lshift - 'a' + 26) % 26 + 'a');
        }
    }
    return result;  
}

//same as encryption, except we subtract the shift value to reverse the process
string decrypt(string message, int rev_Lshift, int rev_Dshift) {
    string result = ""; 
    for (int i=0; i<message.length(); i++) {
        if (isblank(message[i])) {
            result += char(message[i]);
        } 
        else if (isdigit(message[i])) {
            result += char(int(message[i] - rev_Dshift - '0' + 10) % 10 + '0'); 
        } 
        else if (isupper(message[i])) {
            result += char(int(message[i] - rev_Lshift - 'A' + 26) % 26 + 'A'); 
        } else {
            result += char(int(message[i] - rev_Lshift - 'a' + 26) % 26 + 'a');
        }
    }
    return result;  
}
