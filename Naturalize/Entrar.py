import cherrypy
import os

from classes.Cadastro import Cadastro
localDir = os.path.dirname(os.path.abspath(__file__))

class Principal():
    doc = open(os.path.join(localDir, 'paginas', 'Entrar.html'), encoding='utf-8').read()


    @cherrypy.expose()
    def index(self):

        html = self.doc
        return html

    @cherrypy.expose()
    def Logar(self, txtusu, txtsenha):
          Obj = Cadastro()
          dados = Obj.DadosLogin(txtusu, txtsenha)
          if len(dados) > 0:
              raise cherrypy.HTTPRedirect(f"/rotaprincipal?nome={txtusu}")
          else:
              return "<script>alert('Usuário ou senha inválidos!'); window.location = '/';</script>"