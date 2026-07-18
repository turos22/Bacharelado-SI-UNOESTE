import cherrypy
import os

from classes.Cadastro import Cadastro

# Defina o diretório base corretamente
localDir = os.path.dirname(os.path.abspath(__file__))

class PaginaTabela():
    cabecalho = open(os.path.join(localDir, 'paginas', 'cabecalho.html'), encoding='utf-8').read()
    rodape = open(os.path.join(localDir, 'paginas', 'rodape.html'), encoding='utf-8').read()

    @cherrypy.expose()
    def index(self):
        return self.montaTabela()

    def montaTabela(self):
        html = self.cabecalho
        html += self.exibeDados()
        html +=  '''<button class="insere" href="abreTelaInsere" >
        <a href="abreTelaInsere" style="text-decoration: none; color: inherit;">
        Inserir novo Registro</a></button>'''
        html += self.rodape
        return html

    def exibeDados(self):
        html = '''
        <table class="styled-table" style="width: 80%; margin-left: auto; margin-right: auto;">
            <thead>
                <tr style="background-color: #3fa035;">
                    <th>ID</th>
                    <th>Nome</th>
                    <th>Email</th>
                    <th>Telefone</th>
                    <th>Alterar</th>
                    <th>Excluir</th>
                </tr>
            </thead>
            <tbody>
        '''
        objDados = Cadastro()
        dados = objDados.obterTodosDados()
        for cad in dados:
            html += f'''
                <tr>
                    <td>{cad['cad_cod']}</td>
                    <td>{cad['cad_nome']}</td>
                    <td>{cad['cad_email']}</td>
                    <td>{cad['cad_tel']}</td>
                     <td>
                        <a class="action-btn" style="background-color: #3fa035;" href="alterarCadastro?idCad={cad['cad_cod']}">Alterar</a>
                    </td>
                    <td>
                        <a class="action-btn" style="background-color: #3fa035;" href="excluirCadastro?idCad={cad['cad_cod']}">Excluir</a>
                    </td>
                   
                </tr>
            '''
        html += '''
            </tbody>
        </table><br><br>
        '''
        return html

    @cherrypy.expose()
    def abreTelaInsere(self, pCad_cod=0, txtnome="", txtemail="", txttel="", txtarea=0, txtexp="", txthr="", txtcidade="",
                   txtestado="", txtusuario="", txtsenha=""):
        html = self.cabecalho
        html += '''<section class="cadastro-voluntario">
        <h2>Seja um Voluntário!</h2>
        <form action="GravarCadastro" method="post" class="form-voluntario">
          
          <input type="hidden" id="txtcad_cod" name="txtcad_cod" value="%s"/>
          
          <label for="txtnome">Nome Completo:</label>
          <input type="text" id="txtnome" name="txtnome" value="%s" required>

          <label for="txtemail">E-mail:</label>
          <input type="email" id="txtemail" name="txtemail" value="%s" required>

          <label for="txttel">Telefone:</label>
          <input type="tel" id="txttel" name="txttel" placeholder="(99) 99999-9999"  value="%s"required>
         '''% (pCad_cod, txtnome, txtemail, txttel)
        vl1 = ''
        vl2 = ''
        vl3 = ''
        if int(txtarea) == 1:
            vl1 = "selected"
        elif int(txtarea) == 2:
            vl2 = "selected"
        elif int(txtarea) == 3:
            vl3 = "selected"
        html += ''' <label for="txtarea">Áreas de Interesse:</label>
          <select id="txtarea" name="txtarea">
            <option value="">-- Selecione --</option>
            <option value="1" %s>Doador</option>
            <option value="2" %s>Ajudante em Projetos</option>
            <option value="3" %s>Profissional Naturalize</option>
          </select>
        '''%(vl1, vl2, vl3)
        html += '''
          <label for="txtexp">Experiência (opcional):</label>
          <textarea id="txtexp" name="txtexp" rows="4" placeholder="Conte-nos se você já participou de algum trabalho voluntário...">%s</textarea>

          <label for="txthr">Disponibilidade (dias e horários):</label>
          <input type="text" id="txthr" name="txthr" value="%s" >

          <label for="txtcidade">Cidade:</label>
          <input type="text" id="txtcidade" name="txtcidade" value="%s">

          <label for="txtestado">Estado:</label>
          <input type="text" id="txtestado" name="txtestado" value="%s">

          <label for="txtusuario">Usuário:</label>
          <input type="text" id="txtusuario" name="txtusuario" value="%s" required>

          <label for="txtsenha">Senha:</label>
          <input type="text" id="txtsenha" name="txtsenha" value="%s" required>


          <button type="submit" class="btn-enviar">Realizar Cadastro</button>
          <br>
          <a  href="/rotaTabela" class="btn-volta-link">Voltar</a>

        </form>
      </section>'''% (txtexp, txthr, txtcidade, txtestado, txtusuario, txtsenha)
        html += self.rodape
        return html

    @cherrypy.expose()
    def GravarCadastro(self, txtcad_cod=0, txtnome="", txtemail="", txttel="", txtarea=0, txtexp="", txthr=None, txtcidade=None,
                   txtestado=None, txtusuario="", txtsenha=""):
        if int(txtcad_cod) == 0: #insercao
            objCad = Cadastro()
            teste = objCad.InserDados(txtnome, txtemail, txttel, txtarea, txtexp, txthr, txtcidade, txtestado, txtusuario, txtsenha)
            if teste > 0:
                return """
                       <!DOCTYPE html>
                            <html lang="pt-br">
                            <head>
                              <meta charset="UTF-8">
                              <title>Ação Concluída</title>
                              <style>
                                body {
                                  margin: 0;
                                  padding: 0;
                                  font-family: Arial;
                                  display: flex;
                                  justify-content: center;
                                  align-items: center;
                                  height: 100vh;
                                }
                            
                                .mensagem {
                                  padding: 30px 50px;
                                  margin-right: 10px;
                                  background-color: #d4edda;
                                  border: 2px solid #28a745;
                                  color: #155724;
                                  font-size: 24px;
                                  font-weight: bold;
                                  border-radius: 10px;
                                }
                                .voltar {
                                    margin-left: 50px;
                                    padding: 8px 12px;
                                    border-radius: 4px;
                                    font-size: 1em;
                                    background-color: #009879;
                                    color: white;
                                    border: none;
                                    cursor: pointer;
                                    transition: all 0.3s ease-in-out;
                                }
                                .voltar:hover {
                                    background-color: #007f63;
                                    transform: scale(1.1);
                            
                                }
                                
                              </style>
                            </head>
                            <body>
                              <div class="mensagem">Inserção concluída com sucesso!</div>
                              <button class="voltar" href="/rotaTabela" >
                            <a href="/rotaTabela" style="text-decoration: none; color: inherit;">
                            Voltar</a></button>
                            </body>
                            </html>

                        """
            else:
                return """
                        <script>
                            alert("Inserção não concluída, favor verificar");
                            window.history.back();
                        </script>
                        """
        else:
            objCad = Cadastro()
            teste = objCad.AlteraDados(txtcad_cod, txtnome, txtemail, txttel, txtarea, txtexp, txthr, txtcidade, txtestado, txtusuario, txtsenha)
            if teste > 0:
                return """
                       <!DOCTYPE html>
                            <html lang="pt-br">
                            <head>
                              <meta charset="UTF-8">
                              <title>Ação Concluída</title>
                              <style>
                                body {
                                  margin: 0;
                                  padding: 0;
                                  font-family: Arial;
                                  display: flex;
                                  justify-content: center;
                                  align-items: center;
                                  height: 100vh;
                                }
                            
                                .mensagem {
                                  padding: 30px 50px;
                                  margin-right: 10px;
                                  background-color: #d4edda;
                                  border: 2px solid #28a745;
                                  color: #155724;
                                  font-size: 24px;
                                  font-weight: bold;
                                  border-radius: 10px;
                                }
                                .voltar {
                                    margin-left: 50px;
                                    padding: 8px 12px;
                                    border-radius: 4px;
                                    font-size: 1em;
                                    background-color: #009879;
                                    color: white;
                                    border: none;
                                    cursor: pointer;
                                    transition: all 0.3s ease-in-out;
                                }
                                .voltar:hover {
                                    background-color: #007f63;
                                    transform: scale(1.1);
                            
                                }
                                
                              </style>
                            </head>
                            <body>
                              <div class="mensagem">Alteração concluída com sucesso!</div>
                              <button class="voltar" href="/rotaTabela" >
                            <a href="/rotaTabela" style="text-decoration: none; color: inherit;">
                            Voltar</a></button>
                            </body>
                            </html>

                        """
            else:
                return """
                        <script>
                            alert("Alteração não concluída, favor verificar");
                            window.history.back();
                        </script>
                        """

    @cherrypy.expose()
    def alterarCadastro(self, idCad):
        objCad = Cadastro()
        dados = objCad.obterDadosUnico(idCad)
        return self.abreTelaInsere(idCad, dados[0]['cad_nome'], dados[0]['cad_email'], dados[0]['cad_tel'], dados[0]['cad_area'], dados[0]['cad_exp'],
         dados[0]['cad_hr'], dados[0]['cad_cidade'], dados[0]['cad_estado'], dados[0]['usu_login'], dados[0]['usu_senha'])


    @cherrypy.expose()
    def excluirCadastro(self, idCad):
        objCad = Cadastro()
        if objCad.ExcluiDados(idCad):
            raise cherrypy.HTTPRedirect('/rotaTabela')
        else:
            return '''<h2> O cadastro nao foi excluido...</h2>
                          <a href="/rotaTabela">voltar</a>'''