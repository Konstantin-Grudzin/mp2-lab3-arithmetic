#ifndef ARIFM
#define ARIFM

#include"stack.h"

struct Lexem {
    double numb;
    char op;
    bool isOp = 0;
    int pos;
};

// isOp = true  -> op
// isOp = false  -> nmb


class Arifm {
    std::string string;
    std::vector<Lexem> postfix;
    double summary;
    std::pair<int, std::string> Error;
    void Convert(std::string s);
    double Calculate();
public:
    Arifm(std::string s);
    std::pair<double, int> Execution();

};
#endif 
