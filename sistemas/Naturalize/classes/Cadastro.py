from classes.banco import Banco


class Cadastro():
    def __init__(self):
        self.__cad_cod = 0
        self.__cad_nome = ''
        self.__cad_email = ''
        self.__cad_tel = ''
        self.__cad_area = 0
        self.__cad_exp = ''
        self.__cad_hr = ''
        self.__cad_cidade = ''
        self.__cad_estado = ''
        self.__cad_usuario = ''
        self.__cad_senha = ''   
        self.__banco = Banco()

#region REGIAO GETS E SETS
    # (cad_cod)
    def set_cad_cod(self, pId):
        if int(pId) > 0:
            self.__cad_cod = pId

    def get_cad_cod(self):
        return self.__cad_cod

    # (cad_nome)
    def set_cad_nome(self, nome):
        if nome:
            self.__cad_nome = nome

    def get_cad_nome(self):
        return self.__cad_nome

    # (cad_email)
    def set_cad_email(self, email):
        if email:
            self.__cad_email = email

    def get_cad_email(self):
        return self.__cad_email

    # (cad_tel)
    def set_cad_tel(self, tel):
        if tel:
            self.__cad_tel = tel

    def get_cad_tel(self):
        return self.__cad_tel

    # (cad_area)
    def set_cad_area(self, area):
        if len(area) > 0:
            if int(area) >0:
                self.__cad_area = area

    def get_cad_area(self):
        return self.__cad_area

    # (cad_exp)
    def set_cad_exp(self, exp):
        if exp:
            self.__cad_exp = exp

    def get_cad_exp(self):
        return self.__cad_exp

    # (cad_hr)
    def set_cad_hr(self, hr):
        if hr:
            self.__cad_hr = hr

    def get_cad_hr(self):
        return self.__cad_hr

    # (cad_cidade)
    def set_cad_cidade(self, cidade):
        if cidade:
            self.__cad_cidade = cidade

    def get_cad_cidade(self):
        return self.__cad_cidade

    # (cad_estado)
    def set_cad_estado(self, estado):
        if estado:
            self.__cad_estado = estado

    def get_cad_estado(self):
        return self.__cad_estado
    
    def set_cad_usuario(self, usuario):
        if usuario:
            self.__cad_usuario = usuario

    def get_cad_usuario(self):
        return self.__cad_usuario
    
    def set_cad_senha(self, senha):
        if senha:
            self.__cad_senha = senha

    def get_cad_senha(self):
        return self.__cad_senha
    #endregion

    #region select de tudo
    def obterTodosDados(self):
        sql = ''' select * from cadastro order by cad_nome'''
        return self.__banco.executaselect(sql)
    #endregion

    #region select de unico registro
    def obterDadosUnico(self, pCad_cod):
        sql = '''select 
              cad_cod, cad_nome, cad_email, cad_tel, cad_area, cad_exp, cad_hr, cad_cidade, cad_estado,
              coalesce(usu_login, '') as usu_login,
              coalesce(usu_senha, '') as usu_senha
              from cadastro where cad_cod = #cad_cod'''
        sql = sql.replace('#cad_cod', str(pCad_cod))
        return self.__banco.executaselect(sql)
    #endregion

    #region alteracao
    def AlteraDados(self, pCad_cod, pCad_nome, pCad_email, pCad_tel, pCad_area, pCad_exp, pCad_hr, pCad_cidade,
                    pCad_estado, pCad_usuario, pCad_senha):

        self.set_cad_cod(pCad_cod)
        self.set_cad_nome(pCad_nome)
        self.set_cad_email(pCad_email)
        self.set_cad_tel(pCad_tel)
        self.set_cad_area(pCad_area)
        self.set_cad_exp(pCad_exp)
        self.set_cad_hr(pCad_hr)
        self.set_cad_cidade(pCad_cidade)
        self.set_cad_estado(pCad_estado)
        self.set_cad_usuario(pCad_usuario)
        self.set_cad_senha(pCad_senha)

        sql = f'''
            UPDATE cadastro SET
                cad_nome = '{self.__cad_nome}',
                cad_email = '{self.__cad_email}',
                cad_tel = '{self.__cad_tel}',
                cad_area = {self.__cad_area},
                cad_exp = '{self.__cad_exp}',
                cad_hr = '{self.__cad_hr}',
                cad_cidade = '{self.__cad_cidade}',
                cad_estado = '{self.__cad_estado}',
                usu_login = '{self.__cad_usuario}',
                usu_senha = '{self.__cad_senha}'
            WHERE cad_cod = {self.__cad_cod}
        '''
        return self.__banco.executarsql(sql)
    #endregion

    #region insercao
    def InserDados(self, pCad_nome, pCad_email, pCad_tel, pCad_area, pCad_exp, pCad_hr, pCad_cidade, pCad_estado, pCad_usuario, pCad_senha):
        self.set_cad_nome(pCad_nome)
        self.set_cad_email(pCad_email)
        self.set_cad_tel(pCad_tel)
        self.set_cad_area(pCad_area)
        self.set_cad_exp(pCad_exp)
        self.set_cad_hr(pCad_hr)
        self.set_cad_cidade(pCad_cidade)
        self.set_cad_estado(pCad_estado)
        self.set_cad_usuario(pCad_usuario)
        self.set_cad_senha(pCad_senha)

        sql = f'''
            INSERT INTO cadastro (
                cad_nome, cad_email, cad_tel, cad_area, cad_exp, cad_hr, cad_cidade, cad_estado, usu_login, usu_sen
            ) VALUES (
                '{self.__cad_nome}', '{self.__cad_email}', '{self.__cad_tel}', {self.__cad_area},
                '{self.__cad_exp}', '{self.__cad_hr}', '{self.__cad_cidade}', '{self.__cad_estado}', '{self.__cad_usuario}', '{self.__cad_senha}'
            )
        '''
        return self.__banco.executarsql(sql)
    #endregion

    #region exclusao
    def ExcluiDados(self, pCad_cod):
        sql = '''delete from cadastro where cad_cod = #cad_cod'''
        sql = sql.replace('#cad_cod', str(pCad_cod))
        return self.__banco.executarsql(sql)
    #endregion

    def DadosLogin(self, pUsuario, pSenha):
        sql = ''' select * from cadastro where usu_login = '#usuario' and usu_senha = '#senha' '''
        sql = sql.replace('#usuario', pUsuario)
        sql = sql.replace('#senha', pSenha)
        return self.__banco.executaselect(sql)




