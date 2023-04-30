#include<iostream>
#include <stdexcept>

class PalavraReservada{

    private:
    std::string categoria, tipo, cadeia;

    public:
    PalavraReservada(std::string cadeia);

};

    PalavraReservada::PalavraReservada(std::string cadeia){
        PalavraReservada::cadeia = cadeia;
        
    }