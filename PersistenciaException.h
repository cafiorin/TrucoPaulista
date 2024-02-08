#pragma once

#include <exception>

class PersistenciaException : public std::exception {
public:
    const char* what() const noexcept override {
        return "N�o foi poss�vel encontrar o arquivo do jogo.";
    }
};