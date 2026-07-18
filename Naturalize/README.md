# Naturalize - Sistema Web de Gestão de Voluntários

![Python](https://img.shields.io/badge/python-3.x-blue?style=flat-square&logo=python)
![CherryPy](https://img.shields.io/badge/cherrypy-web%20framework-green?style=flat-square)
![SQLite](https://img.shields.io/badge/sqlite-database-blue?style=flat-square&logo=sqlite)

## 📖 Sobre o Projeto

O **Naturalize** é uma plataforma web desenvolvida como projeto acadêmico com o objetivo de promover ações de conscientização ambiental e gestão de voluntários para projetos sustentáveis. A iniciativa permite que pessoas interessadas possam se cadastrar como voluntários em três áreas:

- **Doador** - Contribuir com recursos financeiros
- **Ajudante em Projetos** - Participar ativamente das ações
- **Profissional Naturalize** - Trabalhar profissionalmente nos projetos

### 🎯 Projetos em Destaque

- **BioFiltro Escolar** - Tratamento natural de águas cinzas
- **Plástico Verde** - Produção de bioplástico com casca de banana
- **Eco Luz** - Energia solar com materiais recicláveis

## 🛠️ Tecnologias Utilizadas

- **Python 3.x** - Linguagem de programação principal
- **CherryPy** - Framework web minimalista e leve
- **SQLite** - Banco de dados embarcado
- **HTML5/CSS3** - Template e estilização

## 📂 Estrutura do Projeto

```
├── Traba.py                    # Arquivo principal (entry point)
├── Entrar.py                   # Rotas de autenticação
├── pageTeste.py                # Rotas de CRUD
├── classes/
│   ├── Cadastro.py             # Modelo de cadastro e regras de negócio
│   └── banco.py                # Classe de conexão com SQLite
├── paginas/
│   ├── pagina1.html            # Página inicial
│   ├── Entrar.html             # Tela de login
│   ├── cabecalho.html          # Header compartilhado
│   ├── rodape.html             # Footer compartilhado
│   ├── cadastro.html           # Formulário de voluntário
│   └── [projetos].html         # Páginas dos projetos
├── css/
│   ├── estilo.css              # Estilos principais
│   └── entrar.css              # Estilos da tela de login
├── fotos/                      # Imagens e assets
└── Banco/
    └── Cadastro.db             # Banco de dados SQLite
```

## ⚙️ Como Executar

### Pré-requisitos
- Python 3.x instalado
- pip

### Instalação

1. Clone o repositório:
```bash
git clone https://github.com/seu-usuario/naturalize.git
cd naturalize
```

2. Instale as dependências:
```bash
pip install cherrypy
```

3. Execute a aplicação:
```bash
python Traba.py
```

4. Acesse no navegador:
```
http://localhost:8081
```

### 📝 Credenciais de Teste

Para acessar a área de voluntários:
- **Usuário: teste** (criado durante o cadastro)
- **Senha: 123** (definida no cadastro)

## 🌐 Rotas Disponíveis

| Rota | Método | Descrição |
|------|--------|-----------|
| `/` | GET | Página inicial |
| `/Logar` | GET | Autenticação do usuário |
| `/rotaTabela` | GET | Lista de voluntários (CRUD) |
| `/rotaTabela/abreTelaInsere` | GET | Formulário de cadastro |
| `/rotaTabela/GravarCadastro` | POST | Salvar/editar voluntário |
| `/rotaTabela/alterarCadastro` | GET | Carregar dados para edição |
| `/rotaTabela/excluirCadastro` | GET | Remover voluntário |

## 👥 Desenvolvedores

Projeto desenvolvido durante o 2º semestre da faculdade (2024/2025):

- **Arthur Orosco** - [Portfólio](paginas/portfolio_arthur.html)
- **Mateus Maciel** - [Portfólio](../Portifolio%20Mateus/HTML2.html)
- **Renan Carvalho** - [Portfólio](../Portifolio%20Renan/index.html)

## 📋 Observações Importantes

⚠️ **Este é um projeto acadêmico** e possui algumas limitações de segurança:
- Senhas armazenadas em texto plano (não usar em produção)
- Banco de dados SQLite local

## 📄 Licença

Este projeto é distribuído sob a licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

⚠️ **Nota:** Este é um projeto acadêmico e possui limitações de segurança (senhas em texto plano, SQL Injection). Não recomendado para uso em produção sem modificações.

---
✨ Desenvolvido com Python e CherryPy
