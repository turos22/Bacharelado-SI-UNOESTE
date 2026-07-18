# 🏥 Simulador de Fila Hospitalar com Prioridade (Animação em Terminal)

Este projeto é um simulador interativo de atendimento hospitalar desenvolvido em C++. Ele implementa uma **Fila de Prioridade Dinâmica** e utiliza bibliotecas nativas do Windows (`conio2.h` e `windows.h`) para renderizar uma interface gráfica customizada em modo texto dentro do console, incluindo animações de movimentação de pacientes em tempo real.

---

## 📂 Estrutura do Projeto

*   **`tadFILAHosp.h`**: TAD (Tipo Abstrato de Dados) contendo as estruturas (`tpElemento`, `tpFilaP`) e as operações lógicas da fila de prioridade (`PUSH`, `POP`, ordenação interna por nível de urgência).
*   **`main.cpp`** (ou arquivo principal): Contém a lógica de controle do tempo de simulação, leitura do banco de dados fictício (`Pacientes.txt`), cálculo das médias de tempo de espera e as rotinas gráficas de animação.
*   **`Pacientes.txt`**: Arquivo de texto que funciona como entrada de dados contendo a lista de pacientes simulados no formato: `Nome;ID;Prioridade`.

---

## ⚙️ Funcionalidades Principais

*   **Fila de Prioridade Baseada em Urgência:** Ao dar `PUSH` na fila, o sistema reordena internamente os registros para garantir que pacientes com maior prioridade passem na frente, simulando uma triagem de hospital real.
*   **Animação Baseada em ASCII (*Stickman*):** O sistema conta com uma função dinâmica que desenha portas abrindo/fechando e um personagem andando passo a passo pelo terminal ao mudar do estado de espera para o estado de atendimento.
*   **Geração Aleatória de Tempo de Consulta:** O tempo que cada médico leva para atender varia dinamicamente utilizando funções pseudo-aleatórias (`rand()`).
*   **Relatório Estatístico Final:** Ao encerrar a simulação, o console exibe o total de pacientes atendidos e a métrica exata do tempo médio que as pessoas passaram aguardando na fila.

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
*   **Ambiente Windows:** Este código foi feito especificamente para rodar no prompt do Windows devido às bibliotecas `windows.h` (controle de clocks/`Sleep`) e `conio2.h`/`conio.h` (posicionamento de cursor `gotoxy` e cores de texto).
*   Um compilador configurado para C++ (como o `GCC/G++` via MinGW ou em IDEs clássicas de faculdade como Dev-C++ ou Code::Blocks com a biblioteca `conio2` inclusa).

### Passos via Terminal

1. Garanta que o arquivo `Pacientes.txt` com a listagem esteja na **mesma pasta** dos arquivos de código.
2. Compile o código executando o comando:
   ```bash
   g++ main.cpp -o FilaHospitalar -lconio
