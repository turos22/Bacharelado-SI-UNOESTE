import sqlite3

import os

localDir = os.path.dirname(os.path.abspath(__file__))
parentDir = os.path.dirname(localDir)
bancoDir = os.path.join(parentDir, "Banco")

class Banco():

    def __init__(self):
        self.__conexao = None
        self.__cursor = None

    def __abrirConexao(self):
        self.__conexao = sqlite3.connect(os.path.join(bancoDir, "Cadastro.db"))
        print("Banco de dados armazenado em:", self.__conexao.execute("PRAGMA database_list;").fetchall())

        # Fechar conexão
        self.__conexao.row_factory = sqlite3.Row  # isso serve para que você possa acessar os dados pelos nomes dos atributos da tabela e não somente pela posição que eles se encontram
        self.__cursor = self.__conexao.cursor()
        self.__cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
        tabelas = self.__cursor.fetchall()

        print("Tabelas no banco de dados:", tabelas)

    def __fecharConexao(self):
        self.__cursor.close()
        self.__conexao.close()

    def executarsql(self, sql):
        linhas = -1
        if len(sql) > 0:
            self.__abrirConexao()
            self.__cursor.execute(sql)
            self.__conexao.commit()
            linhas = self.__cursor.rowcount
            self.__fecharConexao()
        return linhas

    def executaselect(self, sql):
        registros = ''
        if len(sql) > 0:
            self.__abrirConexao()
            self.__cursor.execute(sql)
            registros = self.__cursor.fetchall()
            self.__fecharConexao()
        return registros


