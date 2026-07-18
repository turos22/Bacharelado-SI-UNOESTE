# 📝 Editor de Textos em C

Este é um projeto de um Editor de Textos interativo desenvolvido em C++. O objetivo do sistema é permitir a criação, edição, leitura e manipulação de arquivos de texto puro de forma simplificada através do terminal ou console.

---

## 📂 Estrutura do Projeto

O diretório principal (`Traba1/`) contém os seguintes arquivos modulares:

*   **`Editor De Textos.cpp`**: O arquivo de implementação principal contendo as lógicas de controle, captura de comandos do usuário e fluxo de execução do editor.
*   **`Editor de Textos.h`**: O cabeçalho (*header file*) que define as estruturas de dados, assinaturas de funções e classes que sustentam o editor.
*   **`Editor De Textos.exe`**: O executável pré-compilado pronto para rodar no ambiente Windows.
*   **`editor_de_texto.txt`**: O arquivo de texto padrão utilizado pelo programa para ler ou salvar o conteúdo manipulado pelo editor.

---

## ⚙️ Funcionalidades Principais

*   **Criação e Leitura:** Abertura e exibição de arquivos de texto no terminal.
*   **Inserção de Conteúdo:** Adição de novas linhas de texto dinamicamente.
*   **Salvamento Automático/Manual:** Persistência de dados diretamente no arquivo `editor_de_texto.txt`.
*   **Modularidade:** Estrutura organizada dividindo definições (`.h`) de implementações (`.cpp`).

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
Certifique-se de ter um compilador para C++ instalado em seu sistema (como o `GCC/G++`).

### Passos para Compilação via Terminal

1. Abra o terminal na pasta raiz do projeto (`Traba1/`).
2. Digite o comando abaixo para compilar o código fonte:

```bash
g++ "Editor De Textos.cpp" -o "EditorDeTextos"
