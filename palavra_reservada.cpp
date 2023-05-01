#include<iostream>
#include <stdexcept>

class PalavraReservada{

    private:
    std::string categoria, tipo, cadeia;

    public:
    PalavraReservada(std::string cadeia, std::string categoria, std::string tipo);

};

    PalavraReservada::PalavraReservada(std::string cadeia, std::string categoria, std::string tipo){
        PalavraReservada::cadeia = cadeia;
        PalavraReservada::categoria = categoria;
        PalavraReservada::tipo = tipo;
        
    }