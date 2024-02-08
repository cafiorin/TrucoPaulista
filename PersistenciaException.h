#pragma once

#include <exception>

class PersistenciaException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Não foi possível encontrar o arquivo do jogo.";
    }
};