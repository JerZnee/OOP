#include <iostream>
#include <string>

class Modulo {
public:
    // default constructor
    Modulo(int number_, int N_){
        number = number_ % N_;
        N = N_;
    }
    // arithmetical operations
    Modulo& operator=(const Modulo &other) = default;

    Modulo operator+(const Modulo &other) const{
        return Modulo((number + other.number) % N, N);
    }
    Modulo operator-() const{
        return Modulo((N- number), N);
    }
    Modulo operator-(const Modulo &other) const{
        return *this + (-other);
    }
    Modulo operator*(const Modulo &other) const{
        return Modulo((number * other.number) % N, N);
    }
    static Modulo pow( Modulo base, const Modulo exp) {
        int tmp = base.number;
        for (int i = 0; i < exp.number; ++i){
            base.number *= tmp;
        }
        base.number %= base.N;
        return base;
    }
    //  division by modulo using the Euler theorem
    Modulo operator/(Modulo other) const{
        return Modulo(((*this) * pow(other, Modulo(N - 2, N))).number, N);
    }

    // compare operators
    bool operator<(const Modulo &other) const{
        return number < other.number;
    }
    bool operator>(const Modulo &other) const{
        return number > other.number;
    }
    bool operator!=(const Modulo &other) const{
        return number != other.number;
    }
    bool operator==(const Modulo &other) const{
        return !((*this) != other);
    }
    bool operator>=(const Modulo &other) const{
        return ((*this) == other) || ((*this) > other);
    }
    bool operator<=(const Modulo &other) const{
        return ((*this) == other) || ((*this) < other);
    }

    friend std::ostream& operator<< (std::ostream &out, const Modulo &n){
        out << n.number;
        return out;
    }
private:
    int number{0}, N{1};
};

// help function
void help(){
    std::cout << "plus num1 num2 mod" << std::endl;
    std::cout << "minus num1 num2 mod" << std::endl;
    std::cout << "mul num1 num2 mod" << std::endl;
    std::cout << "div num1 num2 mod" << std::endl;
    std::cout << "pow num1 num2 mod" << std::endl;
    std::cout << "exit to quit" << std::endl;
    std::cout << "help to get help" << std::endl;
}

int main() {

    help();
    std::string cmd;

    while (true){
        std::cout << ">>> ";
        std::cin >> cmd;
        // exit commands
        if(cmd == "quit" || cmd == "exit") {
            break;
        }
            // all available commands
        else if(cmd != "plus" && cmd != "minus" && cmd != "mul" && cmd != "div" && cmd != "pow" || cmd == "help"){
            help();
            continue;
        }

        // create three numbers
        int num1, num2, mod;
        std::cin >> num1 >> num2 >> mod;
        // create three numbers by modulo
        Modulo n1(num1, mod), n2(num2, mod), n3(0, mod);

        // given operations
        if(cmd == "plus"){
            n3 = n1 + n2;
        }
        else if(cmd == "minus"){
            n3 = n1 - n2;
        }
        else if(cmd == "mul"){
            n3 = n1 * n2;
        }
        else if(cmd == "div"){
            n3 = n1 / n2;
        } else if(cmd == "pow"){
            n3 = Modulo::pow(n1, n2);
        }
        // prints result
        std::cout << n3 << std::endl;
    }
    return 0;
}
