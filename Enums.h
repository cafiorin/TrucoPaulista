#pragma once

enum TipoDePartida { Cliente, DoisJogadores, QuatroJogadores, QuatroJogadores_umremoto};

enum Naipes { Espadas, Copas, Ouro, Paus };

enum StatusJogador { Inicia, EsperandoCartas, RecebeuCartas, SuaVez, NaoEhSuaVez, Truca, AtualizaTento};

enum AcaoRealizada { Jogou, Trucou, Correu, Aceitou }; 

enum NumeroDaRodadaAtual { PrimeiraRodada, SegundaRodada, TerceiraRodada, Melando, MaoDeOnze };

enum PosicaoNaDuplaParaJogar { Primeiro, Pe };

enum ValorDasCartasNaMao {Otimo, Bom, Medio, Fraco, Ruim};

enum ProbabilidadeDeTrucarOuCorrerOuAceitar {Alta, Media, Baixa};