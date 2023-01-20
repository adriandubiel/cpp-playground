
// https://www.geeksforgeeks.org/friend-class-function-cpp/

class BF; // forward definition needed
// another class in which function is declared
class anotherClass {
public:
    void print_bf(BF& obj);
};

class BF{
    friend class AF;    
    int b;
    public:

    friend void anotherClass::print_bf(BF& bf);
};

class AF{
  int a;
    public:

    AF(BF& bf) : bf(bf) {
        bf.b = 3;
    }

    friend void af_print(AF& af);

    BF& bf;
};

void af_print(AF& af){
  af.a = 4;
}

void anotherClass::print_bf(BF& bf){
  bf.b = 4;
}

int main()
{

    return 0;
}
