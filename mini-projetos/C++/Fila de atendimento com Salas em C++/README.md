# Sistema de Simulação de Atendimento Hospitalar

Este projeto consiste em um sistema de simulação de atendimento emergencial hospitalar baseado em níveis de prioridade. Desenvolvido em linguagem C/C++ como um projeto prático para a disciplina de **Estruturas de Dados (ED)**, o software utiliza conceitos avançados de alocação dinâmica, gerenciamento de filas encadeadas através de estruturas descritoras e uma lista duplamente encadeada para o controle dinâmico de salas médicas operacionais.

O sistema dispõe de uma Interface de Usuário Baseada em Texto (TUI) interativa e reativa em tempo real, renderizada com o auxílio da biblioteca `conio2.h`.

---

## 🚀 Funcionalidades Principais

*   **Gerenciamento Multifilas por Prioridade:** Separação automática de pacientes em três níveis críticos:
    *   🔴 **Alta Prioridade (Vermelho):** Atendimento imediato e mandatório sobre as demais filas.
    *   🟡 **Média Prioridade (Amarelo):** Atendimento intermediário.
    *   🟢 **Baixa Prioridade (Verde):** Atendimento eletivo/comum.
*   **Controle Dinâmico de Salas de Atendimento:** O programa gerencia de 1 a 6 consultórios de forma concorrente. Salas operam através de uma Lista Duplamente Encadeada (LDDE), permitindo inserção ou remoção física de consultórios em tempo de execução.
*   **Simulação de Fluxo Contínuo:** Pacientes entram no sistema de forma programática lendo dados persistidos em disco, enquanto um temporizador interno simula a passagem das unidades de tempo (UT). A taxa de chegada de novos pacientes é determinada de forma estocástica e pseudo-aleatória.
*   **Métricas de Desempenho Hospitalar:** Apresentação em tempo real de estatísticas cruciais para a administração hospitalar, tais como:
    *   Quantidade de pacientes atendidos por categoria.
    *   Tempo médio de espera em fila para cada nível de gravidade.
    *   Contador acumulado de atendimentos finalizados por sala ativa e histórico de salas removidas.

---

## 🛠️ Arquitetura de Dados

O núcleo do sistema baseia-se na composição e interação de estruturas dinâmicas bem definidas:

### 1. Paciente (`struct Paciente`)
Representa o nó de uma lista simplesmente encadeada. Contém dados de triagem, identificadores e marcadores temporais essenciais para o cálculo do tempo de espera.
```c
struct Paciente {
    char Class[20];     // Classificação por extenso (Vermelho, Amarelo, Verde)
    char Nome[20];      // Nome do paciente
    char Queixa[20];    // Sintomatologia principal / Queixa médica
    char Data[10];      // Data de entrada
    int Tempo;          // Tempo necessário para o atendimento (em UT)
    int prio;           // Código numérico interno de prioridade (1=Alta, 2=Média, 3=Baixa)
    int tempo_fila;     // Timestamp de entrada na fila (UT atual)
    Paciente *prox;     // Ponteiro para o próximo paciente na fila
};
```

### 2. Descritores de Fila (`struct Descritor` e `struct DescritorMaster`)
Utiliza o conceito de nós descritores para otimizar o acesso às extremidades das filas e permitir uma arquitetura de "lista de listas".
```c
struct Descritor {
    int Qtd;                   // Quantidade atual de pacientes nesta fila
    int tipo;                  // Identificador do tipo da fila (1=Verde, 2=Amarelo, 3=Vermelho)
    Paciente *inicio;          // Ponteiro para o primeiro paciente (head)
    Paciente *fim;             // Ponteiro para o último paciente (tail)
    Descritor *prox_desc;      // Ponteiro para o descritor da próxima categoria de fila
};

struct DescritorMaster {
    int Qtd;                   // Número total de categorias de filas gerenciadas (fixado em 3)
    Descritor *inicio;         // Ponteiro para o primeiro descritor de fila
};
```

### 3. Médicos / Salas de Atendimento (`struct Medico`)
Implementado como uma **Lista Duplamente Encadeada (LDDE)**, representando os consultórios ativos no hospital. Permite que o fluxo de atendimento percorra e distribua os pacientes de forma ágil.
```c
struct Medico {
    int Tempo_Estimado;        // Tempo decorrido do atendimento atual
    int Status;                // Estado de disponibilidade (0 = Desativado/Indisponível, 1 = Ativo)
    int num_sala;              // Número identificador único do consultório
    int verde_atend;           // Contador histórico de pacientes da fila Verde atendidos nesta sala
    int amarelo_atend;         // Contador histórico de pacientes da fila Amarela atendidos nesta sala
    int vermelho_atend;        // Contador histórico de pacientes da fila Vermelha atendidos nesta sala
    Paciente *atual;           // Ponteiro para o paciente atualmente em consulta
    Medico *ant;               // Ponteiro para a sala anterior (LDDE)
    Medico *prox;              // Ponteiro para a próxima sala (LDDE)
};
```

---

## 📄 Formato do Arquivo de Entrada (`Pacientes.txt`)

O programa requer um arquivo de texto nomeado rigidamente como `Pacientes.txt` localizado no mesmo diretório de execução. O arquivo deve seguir uma formatação delimitada por ponto e vírgula (`;`), contendo os registros estruturados dos pacientes a serem triados.

**Exemplo de Conteúdo (`Pacientes.txt`):**
```text
Vermelho;4;Arthur Pendragon;Dor Toracica Intensa;17/07/2026
Amarelo;3;Ginevra Weasley;Febre Alta Persistente;17/07/2026
Verde;2;Lancelot du Lac;Escoriação Leve;17/07/2026
Vermelho;5;Morgana le Fay;Crise Convulsiva;17/07/2026
Verde;3;Merlin Ambrosius;Cefaleia de Rotina;17/07/2026
```
*Nota: A ordem das colunas mapeia de forma exata a assinatura de leitura: `Classificacao;TempoAtendimento;Nome;Queixa;Data`.*

---

## 🎮 Controles de Simulação

Durante a execução da simulação, a tela principal atualiza de forma incremental o status de cada fila e consultório. É possível interagir dinamicamente com o ecossistema utilizando os seguintes comandos no teclado:

| Tecla | Ação | Descrição |
| :---: | :--- | :--- |
| **`N`** | **Adicionar Nova Sala** | Cria uma nova sala médica ao final da lista dinâmica (respeitando o limite máximo absoluto de 6 salas). |
| **`R`** | **Remover Sala** | Sorteia uma sala para marcar seu `Status` como indisponível (`0`). Caso ela possua um paciente em consulta, ela aguardará a conclusão do atendimento antes de realizar a exclusão física e contagem final de dados. |
| **`ESC`** | **Encerrar Programa** | Interrompe o laço principal de simulação e exibe o painel consolidado com o log de salas excluídas e produtividade. |

---

## 🛠️ Compilação e Execução

Por fazer uso extensivo da API de manipulação de terminal do Windows (`windows.h`) e de funções legadas de posicionamento de cursor (`conio2.h`), recomenda-se a compilação em ambientes baseados em Windows (como o IDE **Dev-C++** ou **Code::Blocks** configurados com suporte à biblioteca conio2).

### Passos para Compilação via Terminal (MinGW / GCC):
1. Certifique-se de que possui os arquivos de implementação do projeto (`main.cpp`, `trabalhoED.h` e os arquivos de terceiros da `conio2`).
2. Execute o comando de compilação vinculando os objetos necessários:
   ```bash
   g++ main.cpp -o SimuladorHospital.exe -lconio
   ```
3. Garanta que o arquivo `Pacientes.txt` esteja na mesma pasta do arquivo executável gerado.
4. Execute `SimuladorHospital.exe`.

---

## 📈 Lógica de Escalonamento de Atendimento
1. **Chegada:** O sistema sorteia um tempo aleatório de 1 a 5 unidades de tempo para a chegada do próximo paciente listado no arquivo.
2. **Priorização:** Ao entrar no fluxo, o paciente é inserido no descritor de fila correspondente à gravidade.
3. **Alocação:** Sempre que uma sala médica livre (`Status = 1` e `atual = NULL`) é identificada, o algoritmo busca o próximo paciente disponível, priorizando rigorosamente a Fila Vermelha. Se vazia, passa para a Amarela, e por fim para a Verde.
4. **Desativação Segura:** Se o usuário solicitar a remoção de salas, o sistema aplica um algoritmo de exclusão física segura: se a sala estiver ocupada, o médico conclui o atendimento corrente, computa as métricas pessoais e apenas depois o nó é liberado da memória (`delete pos`).
