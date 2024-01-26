#pragma once

enum Naipes { Espadas, Copas, Ouro, Paus };

enum StatusJogador { Inicia, EsperandoCartas, RecebeuCartas, SuaVez, JogouCarta, Truca , Aceita }; //Deve ter mais

enum AcaoRealizada { Jogou, Trucou, Correu, Aceitou }; //Deve ter mais

enum NumeroDaRodadaAtual { PrimeiraRodada, SegundaRodada, TerceiraRodada, Melando, MaoDeOnze };

enum PosicaoNaDuplaParaJogar { Primeiro, Pe };

enum ValorDasCartasNaMao {Otimo, Bom, Medio, Fraco, Ruim};

enum ProbabilidadeDeTrucarOuCorrerOuAceitar {Alta, Media, Baixa};