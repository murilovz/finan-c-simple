Controle Financeiro Pessoal

**Requisitos:**
Linguagem C
Compilador GCC (recomendado)

Um simples, porém robusto, gerenciador financeiro de linha de comando desenvolvido em C. Este projeto foi criado como um exercício prático para aprofundar conhecimentos em manipulação de arquivos (binários e texto), uso de `structs` e criação de interfaces interativas no terminal.

**Sobre o Projeto**

O objetivo era criar um programa capaz de registrar transações financeiras (receitas, despesas e poupança), armazená-las de forma persistente e permitir a consulta e geração de relatórios. A aplicação utiliza um arquivo binário (`.dat`) para o armazenamento eficiente dos dados e gera um relatório de texto (`.txt`) formatado para fácil leitura.

**Funcionalidades**

-   **Adicionar Transações:** Registre receitas, despesas e valores para o "cofrinho".
-   **Persistência de Dados:** As transações são salvas em um arquivo binário (`Agosto.dat`), garantindo que os dados não sejam perdidos ao fechar o programa.
-   **Geração de Relatório:** Crie um arquivo de texto (`Agosto.txt`) estilizado e formatado em tabela a qualquer momento, baseado nos dados atuais.
-   **Consulta de Saldos:** Verifique o total de receitas, despesas, o valor guardado no cofrinho e o saldo disponível.
-   **Listagem de Movimentações:** Visualize todas as transações salvas diretamente no terminal.
-   **Interface Limpa:** O menu é intuitivo e a tela é limpa a cada nova ação para uma melhor experiência de usuário.
-   **Segurança:** A opção de limpar todos os dados pede uma confirmação para evitar a exclusão acidental.

OBS: o nome do arquivo poderá ser alterado para o mês respectivo. Por exemplo, está configurado atualmente para "Agosto", mas pode-se alterar para outro mês, e assim terás relatórios mensais.

DEMONSTRAÇÃO DE MENU PRINCIPAL E RELATÓRIO DE TEXTO:
Menu Principal
```
\=== Menu Financeiro ===

1.  Realizar transacao
2.  Consultar cofrinho
3.  Verificar movimentacoes
4.  Ver saldos atuais
5.  Limpar todos os dados
6.  Gerar Relatorio em arquivo de texto
0.  Sair do programa

Selecione a opcao desejada:

```
Exemplo do Relatório Gerado (`Agosto.txt`)
```

\+------------+-----------+------------------------------------------+---------------+
| Data       | Tipo      | Descrição                                |    Valor (R$) |
\+------------+-----------+------------------------------------------+---------------+
| 06/08/2025 | Receita   | Salário do mês                           |       3500.00 |
| 06/08/2025 | Despesa   | Aluguel                                  |       1200.00 |
| 07/08/2025 | Cofre     | Poupança para viagem                     |        250.00 |
| 07/08/2025 | Despesa   | Compras no supermercado                  |        450.75 |
\+------------+-----------+------------------------------------------+---------------+

````

**Como Usar**

Para compilar e executar este projeto localmente, siga os passos abaixo.

*Pré-requisitos*
Você precisa ter um compilador C instalado no seu sistema (como GCC ou Clang).

*Instalação e Execução*

1.  **Clone o repositório:**
    ```sh
    git clone [https://github.com/](https://github.com/)[SEU-USUARIO]/[NOME-DO-REPOSITORIO].git
    ```

2.  **Navegue até o diretório do projeto:**
    ```sh
    cd [NOME-DO-REPOSITORIO]
    ```

3.  **Compile o código-fonte:**
    ```sh
    gcc financeiro.c -o financeiro
    ```
    *(Substitua `financeiro.c` pelo nome do seu arquivo .c, se for diferente)*

4.  **Execute o programa:**
    -   No Windows:
        ```sh
        financeiro.exe
        ```
    -   No Linux ou macOS:
        ```sh
        ./financeiro
        ```

---
**Estrutura dos Arquivos**

-   `finan-c-simple.c`: O código-fonte principal da aplicação.
-   `Agosto.dat`: Arquivo binário gerado automaticamente para armazenar os dados das transações. É a "fonte da verdade" do programa.
-   `Agosto.txt`: Relatório de texto estilizado, gerado sob demanda através do menu da aplicação.

---

**Licença**

Distribuído sob a licença MIT. Veja o arquivo `LICENSE` para mais informações.

---

***Feito com propósito por Murilo Viaceli Zanuz***
