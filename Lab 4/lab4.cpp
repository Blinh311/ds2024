#include <iostream>
#include <sstream>
#include <map>

// Mapping function
void map_function(const std::string& line, std::map<std::string, int>& intermediate_result) {
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
        intermediate_result[word]++;
    }
}

// Reducing function
void reduce_function(const std::map<std::string, int>& intermediate_result) {
    for (const auto& pair : intermediate_result) {
        std::cout << pair.first << "\t" << pair.second << std::endl;
    }
}


int main() {
    std::map<std::string, int> intermediate_result;

    // Simulating input data (lines of text)
    std::stringstream input_data;
    input_data << "hello world\n";
    input_data << "hello again world\n";
    input_data << "world world hello\n";

    std::string line;
    while (std::getline(input_data, line)) {
        // Map phase
        map_function(line, intermediate_result);
    }

    // Reduce phase
	reduce_function(intermediate_result);

    return 0;
}
