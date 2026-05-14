📚 Estruturas de Dados e Gestão de Memória
Este repositório contém uma síntese teórica sobre os fundamentos de alocação de memória e estruturas de dados lineares. 
O conteúdo aborda desde a manipulação de ponteiros até a diferença entre listas e vetores, servindo como material de referência para estudos de Ciência da Computação.

📖 Questionário Teórico
1. Alocação de Memória
Alocação Estática: O espaço é reservado pelo compilador em tempo de compilação. O tamanho é fixo e reside no segmento de dados ou na pilha (stack).

Alocação Dinâmica: Ocorre em tempo de execução. O tamanho pode ser ajustado conforme a necessidade, utilizando a área da memória chamada Heap.

2. Comparativo: Estática vs. Dinâmica
3. Característica,Alocação Estática,Alocação Dinâmica
Tempo,Compilação,Execução
Tamanho,Fixo,Variável (Realloc/New)
Memória,Pilha (Stack),Heap
Gerenciamento,Automático,Manual (Free/Delete)

3. Conceitos Fundamentais
Ponteiro: Variável que armazena o endereço de memória de outro objeto. É a base para a alocação dinâmica.

Estruturas Homogêneas: Elementos do mesmo tipo (ex: int vetor[10]).

Estruturas Heterogêneas: Elementos de tipos distintos (ex: struct ou classes).

4. Listas vs. Vetores
A principal vantagem das Listas Encadeadas é a economia de memória em casos de subutilização. Enquanto o vetor reserva um espaço máximo fixo (podendo gerar desperdício), a lista aloca memória apenas para os nós que realmente existem.

🏗️ Representação de Listas
Lista Simplesmente Encadeada
Cada nó possui o dado e um ponteiro para o próximo elemento. O fim da lista é marcado por NULL.

[ HEAD ] -> [ Dado | Próximo ] -> [ Dado | Próximo ] -> NULL

Lista Duplamente Encadeada
Cada nó possui o dado e dois ponteiros: um para o próximo e outro para o anterior, permitindo percorrer a lista em ambos os sentidos.

NULL <- [ Anterior | Dado | Próximo ] <-> [ Anterior | Dado | Próximo ] -> NULL
