#pragma once
#include <iostream>
#include <sstream>


const std::string FILE_NOT_OPENED_EXCEPTION = "FileNotOpenedException: for path ";
const std::string FILE_READING_EXCEPTION = "FileReadingException: Error ocured while reading the file. Illegal value in pair number: ";
const std::string NUMBER_OF_ITEMS_IN_FILE_EXCEPTION = "NumberOfItemsDifferentThanNumberOfLinesInFileException: passed number of items is different than the number of actual items in file. Given number of items: ";
const std::string ILLEGAL_PROBABILITY_EXCEPTION = "IllegalProbabilityException: incorrect input for probability parameters: ";
const std::string ILLEGAL_PARAMETERS_EXCEPTION = "IllegalParametersException: incorrect input for parameter: ";
const std::string ILLEGAL_ITEM_NUMBER_EXCEPTION = "IllegalItemNumberException: number of items differs from KnapsackProblem numberOfItems in Individual at index: ";
const std::string UNKNOWN_ERROR = "UnknownError: please contact our hotline at +48 213 769 420";

const std::string POP_SIZE_INFO = " populationSize. It's size must be greater than 0";
const std::string ITEM_SIZE_INFO = " items. It's size must be greater than 0";
const std::string KNAPSACK_SIZE_INFO = " knapsackSize";

struct MessageException : public std::exception {
public:
	const char* what() const noexcept {
		return message.c_str();
	}
protected:
	std::string message;
	std::stringstream ss;
};

struct FileReadingException : public MessageException {
public:
	FileReadingException(const int pairNumber)
	{
		ss << FILE_READING_EXCEPTION << pairNumber;
		message = ss.str();
	};
};

struct FileNotOpenedException : public MessageException {
public:
	FileNotOpenedException(const std::string& filePath)
	{
		message = FILE_NOT_OPENED_EXCEPTION + filePath;
	};

};

struct NumberOfItemsDifferentThanNumberOfLinesInFileException : public MessageException {
public:
	NumberOfItemsDifferentThanNumberOfLinesInFileException(const unsigned int enteredNumberOfItems)
	{
		ss << NUMBER_OF_ITEMS_IN_FILE_EXCEPTION << enteredNumberOfItems;
		message = ss.str();
	};
};
struct IllegalItemNumberException : public MessageException {
	IllegalItemNumberException(const unsigned int individualIndex, const unsigned int expectedSize, const unsigned int actualSize) {
		ss << ILLEGAL_ITEM_NUMBER_EXCEPTION << individualIndex << " expected number: " << expectedSize <<  " actual number: " << actualSize;
		message = ss.str();
	};
};

struct IllegalParameterValueException : public MessageException {
	IllegalParameterValueException() {
		ss << ILLEGAL_PARAMETERS_EXCEPTION;
		message = ss.str();
	};
	IllegalParameterValueException(const double wrongValue)
	{
		ss << ILLEGAL_PARAMETERS_EXCEPTION << wrongValue;
		message = ss.str();
	};
};
struct IllegalItemParametersException : public IllegalParameterValueException {
public:
	IllegalItemParametersException(const double wrongValue)
	{
		ss << wrongValue << " both value and weight have to be greater than 0";
		message = ss.str();
	};
};

struct IllegalProbabilityException : public IllegalParameterValueException {
public:
	IllegalProbabilityException(const double wrongValue)
	{
		ss << ILLEGAL_PROBABILITY_EXCEPTION << wrongValue << ", make sure they are between 0 and 1 inclusive";
		message = ss.str();
	};
};
struct IllegalSizeException : public IllegalParameterValueException {
public:
	IllegalSizeException(const int wrongValue, const std::string& information) 
	{
		ss << wrongValue << information;
		message = ss.str();
	};
};