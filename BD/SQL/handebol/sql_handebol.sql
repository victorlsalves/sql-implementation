#Implementação do banco de dados para campeonato de handebol em SQLite

PRAGMA foreign_keys = ON;

CREATE TABLE Estadio (
  id_estadio INTEGER PRIMARY KEY,
  nome TEXT NOT NULL,
  endereco TEXT NOT NULL
);

CREATE TABLE Time (
  id_time INTEGER PRIMARY KEY AUTOINCREMENT,
  nome TEXT NOT NULL UNIQUE,
  id_estadio_sede INTEGER NOT NULL,
  capitao INTEGER NOT NULL,
  FOREIGN KEY (id_estadio_sede) REFERENCES Estadio(id_estadio),
  FOREIGN KEY (capitao) REFERENCES Jogador(id_jogador)
);

CREATE TABLE Jogador (
  id_jogador INTEGER PRIMARY KEY AUTOINCREMENT,
  nome TEXT NOT NULL,
  nascimento DATE NOT NULL,
  genero CHAR(1) NOT NULL CHECK (genero IN ('M', 'F')),
  altura REAL NOT NULL, -- decimal(4,2)
  id_time INTEGER NOT NULL,
  FOREIGN KEY (id_time) REFERENCES Time(id_time)
);

CREATE TABLE Campeonato (
  id_campeonado INTEGER PRIMARY KEY AUTOINCREMENT,
  ano INTEGER NOT NULL UNIQUE
);

CREATE TABLE Partida (
  id_partida INTEGER PRIMARY KEY AUTOINCREMENT,
  id_campeonato INTEGER NOT NULL,
  id_time_mandante INTEGER NOT NULL,
  id_time_visitante INTEGER NOT NULL,
  id_estadio INTEGER NOT NULL,
  data_partida DATE NOT NULL,
  placar_mandante INTEGER,
  placar_visitante INTEGER,
  FOREIGN KEY (id_campeonato) REFERENCES Campeonato(id_campeonado),
  FOREIGN KEY (id_time_mandante) REFERENCES Time(id_time),
  FOREIGN KEY (id_time_visitante) REFERENCES Time(id_time),
  FOREIGN KEY (id_estadio) REFERENCES Estadio(id_estadio)
);