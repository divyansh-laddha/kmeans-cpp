#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

class ProjectException : public exception{
protected:
    string message;
public:
 ProjectException(const string& msg): message(msg){}
    const char* what() const noexcept override{
        return message.c_str();
    }
};

class InvalidKException : public ProjectException{
public:
    InvalidKException(): ProjectException("Invalid value of K."){}
};


class ErrorFileOpening: public ProjectException{
    public:
        ErrorFileOpening() : ProjectException("Unable to Open CSV File."){}
};

class EmptyDataSet : public ProjectException{
    public: 
        EmptyDataSet() : ProjectException("DataSet is Empty."){}
};


class DimensionMismatchException : public ProjectException{
public:
    DimensionMismatchException(): ProjectException("Dimension mismatch."){}
};

#endif