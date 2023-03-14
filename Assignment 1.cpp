#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>



std::vector<int> string_to_digits(std::string s){
 
    std::vector<int> out; 
 
    for(int i = 0; i < s.size(); i++){
 
       std::string digit_string;
       digit_string.push_back(s[i]);
 
       int digit_int = std::stoi(digit_string);
 
       out.push_back(digit_int);
 
    }
 
    return out;
 
}



bool possible_sequence(std::string digits, std::string sequence){
    
    int i, j;
    bool possible;
    std::vector<int> round_digits, sequence_digits;

    round_digits = string_to_digits(digits);
    sequence_digits = string_to_digits(sequence);

    for(i=0; i<sequence_digits.size(); i++){
        for(j=0; j<round_digits.size(); j++){
            if(sequence_digits[i]==round_digits[j]){
                possible = true;
                round_digits[j]=11;
                j=round_digits.size();
            }
            else{
                possible = false;
            }
        }
        if(j==round_digits.size() && !possible){
            i=sequence_digits.size();
        }
    }

    return possible;

}


int score(std::string s, const std::vector<int>& values){

    int sum_of_values=0, sum_of_consecutive=0, counter=0;
    std::vector<int> sequence_digits;
    bool consecutive;

    sequence_digits = string_to_digits(s);

    for(int i=0; i<sequence_digits.size(); i++){
        if(i==0){
           if(sequence_digits[i]==sequence_digits[i+1]-1){
                sum_of_consecutive+=values[sequence_digits[i]];
                counter+=1;
                if(sequence_digits[i]!=sequence_digits[i+1]-1){
                    sum_of_values=sum_of_values + counter*(sum_of_consecutive);
                    counter=0;
                    sum_of_consecutive=0;
                }
            }
            else{
                sum_of_values+=values[sequence_digits[i]];
            } 
        }
        else if(i==sequence_digits.size()){
            if(sequence_digits[i]==sequence_digits[i-1]+1){
                sum_of_consecutive+=values[sequence_digits[i]];
                counter+=1;
                if(sequence_digits[i]!=sequence_digits[i+1]-1){
                    sum_of_values=sum_of_values + counter*(sum_of_consecutive);
                    counter=0;
                    sum_of_consecutive=0;
                }
            }
            else{
                sum_of_values+=values[sequence_digits[i]];
            }
        }
        else{
            if(sequence_digits[i]==sequence_digits[i-1]+1 || sequence_digits[i]==sequence_digits[i+1]-1){
                sum_of_consecutive+=values[sequence_digits[i]];
                counter+=1;
                if(sequence_digits[i]!=sequence_digits[i+1]-1){
                    sum_of_values=sum_of_values + counter*(sum_of_consecutive);
                    counter=0;
                    sum_of_consecutive=0;
                }
            }
            else{
                sum_of_values+=values[sequence_digits[i]];
            }
        }
    }

    sum_of_values+=counter*(sum_of_consecutive);

    return sum_of_values;

}



int get_best_sequence(std::string digits, const std::vector<std::string>& allowed, const std::vector<int>& values, std::string& best_sequence){

    int current_highscore=-99999999, current_score, highscore_index;
    std::vector<std::string> allowed_sequences;

    for(int i=0; i<allowed.size(); i++){
        current_score=score(allowed[i], values);
        if(possible_sequence(digits, allowed[i])){
            allowed_sequences.push_back(allowed[i]);
            if(current_score>current_highscore){
                current_highscore=current_score;
                highscore_index=i;
            }
        }
    }

    best_sequence=allowed[highscore_index];

    return current_highscore;

}





int main(){

    std::string allowed_file, values_file, rounds_file, output_file;
    std::ifstream allowed, values, rounds;
    std::ofstream output;
    std::vector<std::string> allowed_vector, rounds_vector, output_vector;
    std::vector<int> values_vector;
    std::string best_sequence;
    int highscore;



    std::cin >> allowed_file >> values_file >> rounds_file >> output_file;



    allowed.open(allowed_file);
    std::string allowed_temp;
    while(allowed >> allowed_temp){
        allowed_vector.push_back(allowed_temp);
    }
    allowed.close();

    values.open(values_file);
    int values_temp;
    while(values >> values_temp){
        values_vector.push_back(values_temp);

    }
    values.close();

    rounds.open(rounds_file);
    std::string rounds_temp;
    while(rounds >> rounds_temp){
        rounds_vector.push_back(rounds_temp);
    }
    rounds.close();



    output.open(output_file);
    for(int i=0; i<rounds_vector.size(); i++){
        highscore = get_best_sequence(rounds_vector[i], allowed_vector, values_vector, best_sequence);
        output << rounds_vector[i] << " " << best_sequence << " " << highscore << std::endl;
    }
    output.close();

}



