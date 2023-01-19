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


struct FileReadingException : public std::exception {
public:
	FileReadingException(const int pairNumber)
	{
		ss << FILE_READING_EXCEPTION << pairNumber;
		message = ss.str();
	};

	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
	std::stringstream ss;
};

struct FileNotOpenedException : public std::exception {
public:
	FileNotOpenedException(const std::string& filePath)
		: message {FILE_NOT_OPENED_EXCEPTION + filePath}
	{};
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
};

struct NumberOfItemsDifferentThanNumberOfLinesInFileException : public std::exception {
public:
	NumberOfItemsDifferentThanNumberOfLinesInFileException(const unsigned int enteredNumberOfItems)
	{
		ss << NUMBER_OF_ITEMS_IN_FILE_EXCEPTION << enteredNumberOfItems;
		message = ss.str();
	};
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
	std::stringstream ss;
};
struct IllegalItemNumberException : public std::exception {
	IllegalItemNumberException(const unsigned int individualIndex, const unsigned int expectedSize, const unsigned int actualSize) {
		ss << ILLEGAL_ITEM_NUMBER_EXCEPTION << individualIndex << " expected number: " << expectedSize <<  " actual number: " << actualSize;
		message = ss.str();
	};
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
	std::stringstream ss;
};

struct IllegalParameterValueException : public std::exception {
	IllegalParameterValueException() {
		ss << ILLEGAL_PARAMETERS_EXCEPTION;
		message = ss.str();
	};
	IllegalParameterValueException(const double wrongValue)
	{
		ss << ILLEGAL_PARAMETERS_EXCEPTION << wrongValue;
		message = ss.str();
	};
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
	std::stringstream ss;
};
struct IllegalItemParametersException : public IllegalParameterValueException {
public:
	IllegalItemParametersException(const double wrongValue)
	{
		ss << ILLEGAL_PARAMETERS_EXCEPTION << wrongValue << " both value and weight have to be greater than 0";
		message = ss.str();
	};
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
	std::stringstream ss;
};

struct IllegalKnapsackSizeException : public IllegalParameterValueException {
public:
	IllegalKnapsackSizeException(const double wrongValue)
	{
		ss << ILLEGAL_PARAMETERS_EXCEPTION <<  wrongValue << " knapsackSize";
		message = ss.str();
	};
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
	std::stringstream ss;
};

struct IllegalVectorSizeException : public IllegalParameterValueException {
public:
	IllegalVectorSizeException() : message{ ILLEGAL_PARAMETERS_EXCEPTION + "items. It's size must be greater than 0" }
	{};
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
};
struct IllegalProbabilityException : public IllegalParameterValueException {
public:
	IllegalProbabilityException(const double wrongValue)
	{
		ss << ILLEGAL_PROBABILITY_EXCEPTION << wrongValue << ", make sure they are between 0 and 1 inclusive";
		message = ss.str();
	};
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
	std::stringstream ss;
};
struct IllegalPopulationSizeException : public IllegalParameterValueException {
public:
	IllegalPopulationSizeException(const int wrongValue) : message{ ILLEGAL_PARAMETERS_EXCEPTION + "populationSize. It's size must be greater than 0" }
	{};
	const char* what() const noexcept {
		return message.c_str();
	}
private:
	std::string message;
};