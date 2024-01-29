#pragma once

enum Naipes { Espadas, Copas, Ouro, Paus };

enum StatusJogador { Inicia, EsperandoCartas, RecebeuCartas, SuaVez, NaoEhSuaVez, Truca };

enum AcaoRealizada { Jogou, Trucou, Correu, Aceitou }; 

enum NumeroDaRodadaAtual { PrimeiraRodada, SegundaRodada, TerceiraRodada, Melando, MaoDeOnze };

enum PosicaoNaDuplaParaJogar { Primeiro, Pe };

enum ValorDasCartasNaMao {Otimo, Bom, Medio, Fraco, Ruim};

enum ProbabilidadeDeTrucarOuCorrerOuAceitar {Alta, Media, Baixa};