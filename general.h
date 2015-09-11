#include <string.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include "linked_list.h"

#ifndef SEBER_GENERAL
#define SEBER_GENERAL

template <typename T>
void printArray(const T * array, const int & size, const std::string & starterText, const std::string & endOfLineText) {

	if (starterText.empty()) {

		std::cout << "Array output: " << std::endl;

	}

	else {

		std::cout << starterText << std::endl;

	}

	for (int i = 0; i < size; i++) {

		std::cout << "	" << i << ": " << array[i] << endOfLineText << std::endl;

	}

}

template <typename T>
int isElementInArray(const T * array, const int & size, const T & element) {

	for (int i = 0; i < size; i++) {

		if (array[i] == element) {

			return i;

		}

	}

	return -1;

}

std::string toLower(std::string string) {

	std::transform(string.begin(), string.end(), string.begin(), ::tolower);

	return string;


}

char * stringToCString(const std::string & input) {

	char * output = new char[input.length()];
	strcpy(output, input.c_str());

	return output;

}

int stringCharCounter(const std::string & data, const char * delimiter) {

	int count = 0;

	for (int i = 0; i < static_cast<int>(data.size()); i++) {

		if (data[i] == *delimiter) {

			count++;

		}

	}

	return count;

}

std::string cStringtoString(char * input) {

	return input;

}

const std::string cStringtoString(const char * input) {

	return input;

}

bool isNumberEven(int value) {

	return value % 2 == 0;

}

bool isCharBlank(const char & value) {

	if (value == ' ' || value == '\n' || value == '\t' || value == '\r') {

		return true;

	}

	return false;

}

std::string trimBlankCharacters(const std::string & input_string) {

	std::string output_string = input_string;
	bool run = true;

	while(run) {

		run = false;

		if (!output_string.empty()) {

			if (isCharBlank(output_string.at(0))) {

				output_string.erase(0, 1);
				run = true;

			}

		}

	}

	run = true;

	while(run) {

		run = false;

		if (!output_string.empty()) {

			if (isCharBlank(output_string.at(output_string.size() - 1))) {

				output_string.erase(output_string.size() - 1, 1);
				run = true;

			}

		}

	}

	return output_string;

}

std::string clearAllBlankCharacters(const std::string & input_string) {

	std::string copy_input_string = input_string;
	std::string output_string;

	for (int i = 0; i < static_cast<int>(copy_input_string.length())	; i++) {

		if (!isCharBlank(copy_input_string.at(i))) {

			output_string.append(copy_input_string.substr(i, 1));

		}

	}

	return output_string;

}

bool does_value_fall_between_inclusive(const int & value, const int & low, const int & high) {

	return (value >= low && value <= high);

}

linked_list<std::string> stringTokenizer(const std::string & data, const char * delimiter) { // Implement "" to make anything inside one data value

	linked_list<std::string> list;
	char * token;

	token = strtok(stringToCString(data), delimiter);

	while (token != NULL) {

		list.push_back(cStringtoString(token));
		token = strtok(NULL, delimiter);

	}

	return list;

}

void printNumTimes(const std::string & string, const int & count) {

	for (int i = 0; i < count; i++) {

		std::cout << string;

	}

}

void clearConsole() {

	for (int i = 0; i < 72; i++) {

		std::cout << std::endl;

	}

}

class tokenizedString {

	linked_list<std::string> preceeding_delimiters;
	linked_list<std::string> data;
	linked_list<std::string> following_delimiters;
	linked_list<int> positions;
	int size;

	public:

	tokenizedString() : preceeding_delimiters(), data(), following_delimiters(), size(0) {}

	~tokenizedString() {

		clear();

	}

	bool insertToken(std::string preceeding_delimiter, std::string token, std::string following_delimiter) {

		preceeding_delimiters.push_back(preceeding_delimiter);
		data.push_back(token);
		following_delimiters.push_back(following_delimiter);
		size++;

		return true;

	}

	void remove(const int & position) {

		preceeding_delimiters.remove(position);
		data.remove(position);
		following_delimiters.remove(position);
		size--;

	}

	std::string getPreceedingDelimiter(const int & position) const {

		return preceeding_delimiters.getData(position);

	}

	std::string getData(const int & position) const {

		return data.getData(position);

	}

	std::string getFollowingDelimiter(const int & position) const {

		return following_delimiters.getData(position);

	}

	int getSize() const {

		return size;

	}

	std::string getDelimitedData(const std::string & preceeding_delimiter, const std::string & following_delimiter, const int & position = 0, const std::string & splitter = "") const {

		int beginning_element_position = preceeding_delimiters.findElement(preceeding_delimiter, position);
		int ending_element_position = following_delimiters.findElement(following_delimiter, beginning_element_position);
		std::string output_string;

		if (beginning_element_position != -1 && ending_element_position != -1) {

			for (int i = beginning_element_position; i <= ending_element_position; i++) {

				output_string.append(getData(i));

				if (i != ending_element_position) {

					output_string.append(splitter);

				}

			}

		}

		return output_string;

	}

	linked_list<std::string> getAllDelimitedData(const std::string & preceeding_delimiter, const std::string & following_delimiter, const std::string & splitter = "") const {

		linked_list<std::string> output;
		std::string outputString;
		bool add_tokens = false;

		for (int i = 0; i < getSize(); i++) {

			if (getPreceedingDelimiter(i) == preceeding_delimiter && !add_tokens) {

				add_tokens = true;

			}

			if (add_tokens) {

				outputString.append(getData(i));
				outputString.append(splitter);

			}

			if (getFollowingDelimiter(i) == following_delimiter && add_tokens) {

				output.push_back(outputString);
				outputString.clear();
				add_tokens = false;

			}

		}

		return output;

	}

	const linked_list<std::string> getPreceedingList() const {

		linked_list<std::string> new_preceeding_delimiters = preceeding_delimiters;

		return new_preceeding_delimiters;

	}

	linked_list<std::string> getDataList() const {

		linked_list<std::string> new_data = data;

		return new_data;

	}

	linked_list<std::string> getFollowingList() const {

		linked_list<std::string> new_following_delimiters = following_delimiters;

		return new_following_delimiters;

	}

	std::string str() const {

		std::string output_string;// = input_string;
		//tokenizedString parsedData = stringTokenizer(input_string, searchTerms);

		if (getSize() >= 1) {

			if (!getPreceedingDelimiter(0).empty()) {

				output_string.append(getPreceedingDelimiter(0));

			}

		}

		for (int i = 0; i < getSize(); i++) {

			output_string.append(getData(i));
			output_string.append(getFollowingDelimiter(i));

		}

		return output_string;

	}

	void print(std::ostream & stream) const {

		stream << "[";

		for (int i = 0; i < size; i++) {

			stream << "{" << i << ": ";
			stream << "\"" << preceeding_delimiters.getData(i) << "\" | ";
			stream << "\"" << data.getData(i) << "\" | ";
			stream << "\"" << following_delimiters.getData(i) << "\"";
			stream << "}";

			if (i != (size - 1)) {

				stream << "," << std::endl;

			}

		}

		stream << "]";

	}

	void clear() {

		int currentSize = getSize();

		for (int i = 0; i < currentSize; i++) {

			remove(0);

		}
	}

	bool operator== (const tokenizedString & rhs) const {

		if (getSize() != rhs.getSize()) {

			return false;

		}

		for (int i = 0; i < getSize(); i++) {

			if (getPreceedingDelimiter(i) != rhs.getPreceedingDelimiter(i) || getData(i) != rhs.getData(i) || getFollowingDelimiter(i) != rhs.getFollowingDelimiter(i)) {

				return false;

			}

		}

		return true;

	}

	bool operator!= (const tokenizedString & rhs) const {

		return !(*this == rhs);

	}

	tokenizedString & operator= (const tokenizedString & rhs) {

		if (this != &rhs) {

			clear();

			for (int i = 0; i < rhs.getSize(); i++) {

				insertToken(rhs.getPreceedingDelimiter(i), rhs.getData(i), rhs.getFollowingDelimiter(i));

			}

			return *this;

		}

	}

};

bool is_numeric(const std::string & input_string) {

	return input_string.find_first_not_of("0123456789") == std::string::npos;

}

bool is_alpha(const std::string & input_string) {

	return input_string.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") == std::string::npos;

}

bool is_alphanumeric(const std::string & input_string) {

	return input_string.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") == std::string::npos;

}

bool is_varName(const std::string & input_string) {

	return input_string.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-") == std::string::npos;

}

tokenizedString stringTokenizer(std::string data, const linked_list<std::string> & delimiters) {

	linked_list<bool> delimiter_good(delimiters.getSize(), false);
	linked_list<bool> delimiter_disregarded(delimiters.getSize(), false);
	tokenizedString output = tokenizedString();
	std::string outputString;
	std::string value;
	std::string preceeding_delimiter;
	std::string following_delimiter;

	while(data.length()) {

		for (int i = 0; i < delimiters.getSize(); i++) {

			if (!delimiter_disregarded.getData(i)) {

				size_t next_needle = data.find(delimiters.getData(i));

				if (next_needle == std::string::npos) {

					delimiter_disregarded.setData(i, true);
					continue;

				}

				if (!next_needle) {

					delimiter_good.setData(i, true);

				}

			}

		}

		linked_list<int> good_positions = delimiter_good.findAllElements(true);

		if (good_positions.getSize() > 1) {

			size_t largest_string = 0;
			int bestPosition = -1;

			for (int i = 0; i < good_positions.getSize(); i++) {

				if (delimiters.getData(good_positions.getData(i)).size() > largest_string) {

					largest_string = delimiters.getData(good_positions.getData(i)).size();
					bestPosition = good_positions.getData(i);

				}

			}

			preceeding_delimiter = following_delimiter;
			following_delimiter = delimiters.getData(bestPosition);
			output.insertToken(preceeding_delimiter, outputString, following_delimiter);
			data = data.substr(delimiters.getData(bestPosition).size());

		}

		if (good_positions.getSize() == 1) {

			preceeding_delimiter = following_delimiter;
			following_delimiter = delimiters.getData(good_positions.getData(0));
			output.insertToken(preceeding_delimiter, outputString, following_delimiter);
			data = data.substr(delimiters.getData(good_positions.getData(0)).size());

		}

		if (delimiter_disregarded.findNumAllElements(true) == delimiters.getSize()) {

			preceeding_delimiter = following_delimiter;
			following_delimiter.clear();
			outputString.append(data);
			output.insertToken(preceeding_delimiter, outputString, following_delimiter);
			outputString.clear();
			break;

		}

		if (good_positions.empty()) {

			if (data.length()) {

				value = data.at(0);
				data = data.substr(1);
				outputString.append(value);

			}

		} else {

			outputString.clear();

			for (int j = 0; j < good_positions.getSize(); j++) {

				delimiter_good.setData(good_positions.getData(j), false);

			}

		}

	}

	if (!outputString.empty()) {

		preceeding_delimiter = following_delimiter;
		following_delimiter.clear();
		output.insertToken(preceeding_delimiter, outputString, following_delimiter);

	}

	if (output.getSize() >= 1) {

		if (output.getPreceedingDelimiter(0) == "" && output.getData(0) == "") {

			output.remove(0);

		}

	}

	return output;

}

std::string findAllAndReplace(const std::string & input_string, const linked_list<std::string> & searchTerms, const std::string & replacementTerm) {

	std::string output_string;// = input_string;
	tokenizedString parsedData = stringTokenizer(input_string, searchTerms);

	if (parsedData.getSize() >= 1) {

		if (!parsedData.getPreceedingDelimiter(0).empty()) {

			output_string.append(replacementTerm);

		}

	}

	for (int i = 0; i < parsedData.getSize(); i++) {

		output_string.append(parsedData.getData(i));

		if (!parsedData.getFollowingDelimiter(i).empty()) {

			output_string.append(replacementTerm);

		}

	}

	return output_string;

}

std::string removeExcessCharacters(const std::string & input_string, const linked_list<std::string> & searchTerms) {

	tokenizedString parsedData = stringTokenizer(input_string, searchTerms);
	tokenizedString outputData;

	for (int i = 0; i < parsedData.getSize(); i++) {

		if (!parsedData.getData(i).empty() || parsedData.getPreceedingDelimiter(i) != parsedData.getFollowingDelimiter(i)) {

			outputData.insertToken(parsedData.getPreceedingDelimiter(i), parsedData.getData(i), parsedData.getFollowingDelimiter(i));

		}

	}

	return outputData.str();

}

linked_list<std::string> commandLineTokenizer(const std::string & input_data) {

	linked_list<std::string> excessCharacters = {" "};
	linked_list<std::string> replacementTerms = {"'"};
	linked_list<std::string> delimiters = {" ", "\""};
	std::string data = removeExcessCharacters(input_data, excessCharacters);
	data = findAllAndReplace(data, replacementTerms, "\"");
	tokenizedString parsed_list = stringTokenizer(data, delimiters);
	linked_list<std::string> output_list;

	parsed_list.print(std::cout);
	std::cout << std::endl;

	for (int i = 0; i < parsed_list.getSize(); i++) {

		std::cout << "In i = " << i << std::endl;

		if (parsed_list.getPreceedingDelimiter(i) != "\"") {

			output_list.push_back(parsed_list.getData(i));

		}

		else {

			// output_list.push_back(parsed_list.getDelimitedData("\"", "\"", i, " "));
			// i = parsed_list.getFollowingList().findElement("\"", i) + 1;
			parsed_list.getFollowingList();
			std::cout << "New i = " << i << std::endl;

			if (i == -1) {

				break;

			}

		}

		std::cout << "Out i = " << i << std::endl;

	}

	std::cout << "End!" << std::endl;

	return output_list;

}

int stringToInt(const std::string & data) {

	return atoi(data.c_str());

}

double stringToDouble(const std::string & data) {

	return atof(data.c_str());

}

void clearInputStream() {

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

void printMenu(const std::string * menu, const int & size) {

	for (int i = 0; i < size; i++) {

		std::cout << i + 1 << " - " << menu[i] << std::endl;

	}

}

#endif