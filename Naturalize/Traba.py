import cherrypy
import os
import sys

from Entrar import Principal
from pageTeste import PaginaTabela


# Defina o diretório base corretamente
localDir = os.path.dirname(os.path.abspath(__file__))


class Principal_abertura():
    doc = open(os.path.join(localDir, 'paginas', 'pagina1.html'), encoding='utf-8').read()


    @cherrypy.expose()
    def index(self, nome="Visitante"):

        bem_vindo = f"<script>alert('Bem-vindo, {nome}!');</script>"
        html = bem_vindo + self.doc
        return html

server_config = {
    'server.socket_host': '127.0.0.1',
    'server.socket_port': 8081  
}
cherrypy.config.update(server_config)

local_config = {
    "/": {
        'tools.staticdir.on': True,
        'tools.staticdir.dir': localDir
    },
    "/css": {
        'tools.staticdir.on': True,
        'tools.staticdir.dir': os.path.join(localDir, 'css')
    },
    "/fotos": {
        'tools.staticdir.on': True,
        'tools.staticdir.dir': os.path.join(localDir, 'fotos')
    },
    "/paginas": {
        'tools.staticdir.on': True,
        'tools.staticdir.dir': os.path.join(localDir, 'paginas')
    },
    '/Scripts': {
        'tools.staticdir.on': True,
        'tools.staticdir.dir':  os.path.join(localDir, 'Scripts')
    }
}

root = Principal()
root.rotaprincipal = Principal_abertura()
root.rotaTabela = PaginaTabela()
cherrypy.quickstart(root, config=local_config)



