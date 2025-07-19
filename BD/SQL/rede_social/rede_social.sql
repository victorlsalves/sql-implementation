#Implementação do banco de dados para a rede social em SQLite

PRAGMA foreign_keys = ON;

CREATE TABLE Usuario (
  id_usuario INTEGER PRIMARY KEY AUTOINCREMENT,
  nome TEXT NOT NULL,
  email TEXT NOT NULL UNIQUE,
  nascimento DATE NOT NULL,
  website TEXT,
  genero CHAR(1) NOT NULL CHECK (genero IN ('m', 'f')),
  telefone TEXT,
  foto_perfil TEXT
);

CREATE TABLE Seguidor (
  id_seguidor INTEGER NOT NULL,
  id_seguido INTEGER NOT NULL,
  PRIMARY KEY (id_seguidor, id_seguido),
  FOREIGN KEY (id_seguidor) REFERENCES Usuario(id_usuario),
  FOREIGN KEY (id_seguido) REFERENCES Usuario(id_usuario)
);

CREATE TABLE Postagem (
  id_postagem INTEGER PRIMARY KEY AUTOINCREMENT,
  id_usuario INTEGER NOT NULL,
  texto TEXT NOT NULL,
  data_postagem DATETIME NOT NULL,
  FOREIGN KEY (id_usuario) REFERENCES Usuario(id_usuario)
);

CREATE TABLE Album (
  id_album INTEGER PRIMARY KEY AUTOINCREMENT,
  id_usuario INTEGER NOT NULL,
  titulo TEXT NOT NULL,
  FOREIGN KEY (id_usuario) REFERENCES Usuario(id_usuario)
);

CREATE TABLE Foto (
  id_foto INTEGER PRIMARY KEY AUTOINCREMENT,
  uri TEXT NOT NULL
);

CREATE TABLE Foto_Postagem (
  id_postagem INTEGER NOT NULL,
  id_foto INTEGER NOT NULL,
  PRIMARY KEY (id_postagem, id_foto),
  FOREIGN KEY (id_postagem) REFERENCES Postagem(id_postagem),
  FOREIGN KEY (id_foto) REFERENCES Foto(id_foto)
);

CREATE TABLE Foto_Album (
  id_foto INTEGER NOT NULL,
  id_album INTEGER NOT NULL,
  PRIMARY KEY (id_foto, id_album),
  FOREIGN KEY (id_foto) REFERENCES Foto(id_foto),
  FOREIGN KEY (id_album) REFERENCES Album(id_album)
);