#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stack>
using namespace std;

struct mystate{
    string ros;
    string next;
    int id;
    int state;
};
vector <mystate *> myarr;
vector <string> rules;
vector <int> reduce;

int reducing(int state, vector<int>reduce){
    int index = 0;
    while(index < reduce.size()){
        if (state == reduce[index]){
            return 1;
        }
        index++;
    }
    return 0;
}

int main(){
    int ns, nh, checkerror;
    checkerror = 0;
    int numt, numnt, numr;
    cin >> numt;
    string str;
    getline(cin,str);
    int index0  = 0;
    while(index0 < numt){
        string str;
        getline(cin,str);
        index0++;
    }
    cin >> numnt;
    string str1;
    getline(cin,str1);
    int index1 = 0;
    while(index1 < numnt){
        string str;
        getline(cin,str);
        index1++;
    }
    string str2;
    getline(cin,str2);
    cin >> numr;
    string str3;
    getline(cin,str3);
    int index2 = 0;
    while(index2 < numr){
        string s;
        getline(cin, s);
        rules.push_back(s);
        index2++;
    }
    cin >> ns;
    string str4;
    getline(cin,str4);
    cin >> nh;
    string str5;
    getline(cin,str5);
    int mypos = 0;
    while(mypos < nh){
        string str;
        mystate *s = new mystate();
        getline(cin, str);
        istringstream iss(str);
        iss >> s->id;
        iss >> s->next;
        iss >> s->ros;
        if(s->ros == "reduce"){
            reduce.push_back(s->id);
        }
        iss >> s->state;
        myarr.push_back(s);
        mypos++;
    }
    string input;
    int eof = 0;
    int count = 1;
    int numto = 0;
    stack <string> symstack;
    stack <int> statestack;
    int find = 0;
    symstack.push("BOF");
    statestack.push(0);
    int num;
    int final = -1;
    int index = 0;
    while(index < myarr.size()){
        if (0 == myarr[index]->id && "BOF" == myarr[index]->next
            && myarr[index]->ros == "shift"){
            num = index;
            find = 1;
            final = myarr[num]->state;
            break;
        }
        index++;
    }
    statestack.push(final);
    cin >> input;
    while (cin >> input) {
        count++;
        if (eof == 1){
            checkerror = 1;
            cerr << "ERROR at " << count << endl;
            for (int i = 0; i < myarr.size(); i++){
                delete myarr[i];
            }
            myarr.clear();
            rules.clear();
            reduce.clear();
            return 0;
        }
        if (input == "EOF"){
            eof = 1;
        }
        while (reducing(statestack.top(), reduce)){
            int numm;
            int index = 0;
            while(index < myarr.size()){
                if ( statestack.top() == myarr[index]->id && input == myarr[index]->next &&
                    myarr[index]->ros == "reduce"){
                    numm = myarr[index]->state;
                    numto = 1;
                    break;
                }
                index++;
            }
            if (numto == 0) break;
            string rule = rules[numm];
            cout << rule << endl;
            symstack.pop();
            int result = 0;
            istringstream iss(rule);
            int c = 0;
            string temp;
            while (iss >> temp){
                c++;
            }
            result = c - 1;
            int index2 = 0;
            while(index2 < result){
                statestack.pop();
                index2++;
            }
            istringstream isss(rule);
            string A;
            isss >> A;
            symstack.push(A);
            int num;
            int final = -1;
            int index3 = 0;
            while(index3 < myarr.size()){
                if (statestack.top() == myarr[index3]->id && A == myarr[index3]->next
                    && myarr[index3]->ros == "shift"){
                    num = index3;
                    find = 1;
                    final = myarr[num]->state;
                    break;
                }
                index3++;
            }
            statestack.push(final);
        }
        symstack.push(input);
        int num;
        int final = -1;
        int index = 0;
        while(index < myarr.size()){
            if (statestack.top() == myarr[index]->id && input == myarr[index]->next
                && myarr[index]->ros == "shift"){
                num = index;
                find = 1;
                final = myarr[num]->state;
                break;
            }
            index++;
        }
        if (final == -1){
            cerr << "ERROR at " << count << endl;
            checkerror = 1;
            int pos5 = 0;
            while(pos5 < myarr.size()){
                delete myarr[pos5];
                pos5++;
            }
            myarr.clear();
            rules.clear();
            reduce.clear();
            return 0;
        }
        else{
            int num;
            int final = -1;
            int index = 0;
            while(index < myarr.size()){
                if (statestack.top() == myarr[index]->id && input == myarr[index]->next
                    && myarr[index]->ros == "shift"){
                    num = index;
                    find = 1;
                    final = myarr[num]->state;
                    break;
                }
                index++;
            }
            statestack.push(final);
        }
    }
    if (checkerror == 0){
        cout << rules[0] << endl;
    }
    int num3 = 0;
    while(num3 < myarr.size()){
        delete myarr[num3];
        num3++;
    }
    myarr.clear();
    rules.clear();
    reduce.clear();
    return 0;
}
