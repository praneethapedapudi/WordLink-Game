#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
//#include<windows.h>
#include<cctype>

using namespace std;

const int WORD_LEN=5;
const int NO_OF_GUESS=6;
const int MATCH=2;
const int NO_MATCH=0;
const int PARTLY_MATCH=1;

void toUpperCase(string &input){
    transform(input.begin(), input.end(), input.begin(), [](unsigned char c)
            {return toupper(c);});
}

string getRandomWord(){
    //TODO fetch random word from API (ex: WordsAPI)
    return "ready";
}

bool isValid(string word){
    //TODO check correctness of the word from API
    return word.length()==WORD_LEN && word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")==string::npos;
}

void markMatch(vector<vector<int>> &match, int currGuessIndex, string target, string guess){

    for(int i=0; i<guess.length(); i++){
        match[currGuessIndex][i]=NO_MATCH;
    }

    for(int i=0; i<guess.length(); i++){
        for(int j=0; j<target.length(); j++){
            if(guess[i]==target[j]){
                if(i==j){
                    match[currGuessIndex][i]=MATCH;
                    break;
                } else{
                    match[currGuessIndex][i]=PARTLY_MATCH;
                }
            }
        }
    }
}

bool isAllMatch(string target, string guess){
    for(unsigned int i=0; i<target.length(); i++){
        if(target[i]!=guess[i]){
            return false;
        }            
    }
    return true;
}

void printWordle(vector<vector<int>> match, vector<string> guess, int currGuessIndex){
    //clear console
    system("cls");
    cout<<"======================================================================================================"<<endl;
    cout<<"||   :::       :::  ::::::::  :::::::::  :::::::::  :::        ::::::::::: ::::    ::: :::    :::    ||"<<endl;
    cout<<"||   :+:       :+: :+:    :+: :+:    :+: :+:    :+: :+:            :+:     :+:+:   :+: :+:   :+:     ||"<<endl;
    cout<<"||   +:+       +:+ +:+    +:+ +:+    +:+ +:+    +:+ +:+            +:+     :+:+:+  +:+ +:+  +:+      ||"<<endl;
    cout<<"||   +#+  +:+  +#+ +#+    +:+ +#++:++#:  +#+    +:+ +#+            +#+     +#+ +:+ +#+ +#++:++       ||"<<endl;
    cout<<"||   +#+ +#+#+ +#+ +#+    +#+ +#+    +#+ +#+    +#+ +#+            +#+     +#+  +#+#+# +#+  +#+      ||"<<endl;
    cout<<"||    #+#+# #+#+#  #+#    #+# #+#    #+# #+#    #+# #+#            #+#     #+#   #+#+# #+#   #+#     ||"<<endl;
    cout<<"||     ###   ###    ########  ###    ### #########  ########## ########### ###    #### ###    ###    ||"<<endl;
    cout<<"======================================================================================================"<<endl;
    cout<<"Rules:"<<endl;
    cout<<"1. Guess the word in less than "+::to_string(NO_OF_GUESS)+" guesses."<<endl;
    cout<<"2. Green colour indicates correct letter in correct position"<<endl;
    cout<<"3. Yellow colour indicates correct letter in incorrect position"<<endl;
    cout<<"Good Luck:)"<<endl;


    for(int i=0; i<=currGuessIndex&&i<guess.size(); i++){
        string separator = "-";
        string padding="|";
        string text="|";

        for(int j=0; j<guess[i].length(); j++){
            separator+="------";
            padding+="     |";
            char value=toupper(guess[i][j]);
            text+="  ";
            if(match[i][j]==PARTLY_MATCH){
                //print coloured text
                text+="\033[33m";
            }
            else if(match[i][j]==MATCH){
                text+="\033[32m";
            }

            text+=value;
            if(match[i][j]==PARTLY_MATCH||match[i][j]==MATCH){
                //close colour
                text+="\033[0m";                
            }
            text+="  |";
        }

        if(i==0){
            cout<<separator<<endl;
        }
        cout<<padding<<endl;
        cout<<text<<endl;
        cout<<padding<<endl;
        cout<<separator<<endl;
    }
}

int main(){
    vector<string> guess(NO_OF_GUESS);
    vector<vector<int>> match(NO_OF_GUESS, vector<int>(WORD_LEN));
    string target=getRandomWord();
    toUpperCase(target);

    string input;
    unsigned int currGuessCnt=0;
    //to print game title
    printWordle(match, guess, -1);

    while(currGuessCnt<NO_OF_GUESS){
        do{
           cout<<"Please enter your guess(word length must be "+::to_string(WORD_LEN)+") or type Q/q to quit the game: ";
           getline(cin, input); 
           toUpperCase(input);
        }
        while(input!="Q"&&!isValid(input));

        if(input=="Q"){
            cout<<"Quit game"<<endl;
            break;
        }

        guess[currGuessCnt]=input;
        markMatch(match, currGuessCnt, target, input);
        printWordle(match, guess, currGuessCnt);
        if(isAllMatch(target, input)){
            cout<<"Congrats, you WON!"<<endl;
            break;
        }
        // cout<<currGuessCnt<<endl;
        currGuessCnt++;
    }
    return 0;
}
