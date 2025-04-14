
## Requisitos

1. **Requisitos Funcionais:**
    - **RF1:** Cadastro de veículos com informações como marca, modelo, ano, cor, e preço.
    - **RF2:** Cadastro de clientes com informações básicas (nome, telefone, e-mail).
    - **RF3:** Realização de vendas, incluindo a emissão de notas fiscais.
    - **RF4:** Controle de estoque de veículos.
    - **RF5:** Gerenciamento de funcionários (vendedores e gerentes).
    - **RF6:** Relatórios de vendas e estoque.

## Funcionalidades Previstas

1. **Cadastro de Veículos:**
    - Inserir, alterar e excluir veículos.
    - Visualizar detalhes de cada veículo.
2. **Cadastro de Clientes:**
    - Inserir, alterar e excluir clientes.
    - Visualizar detalhes de cada cliente.
3. **Vendas:**
    - Realizar vendas, incluindo a seleção do veículo e do cliente.
4. **Controle de Estoque:**
    - Visualizar o estoque atual de veículos.
    - Receber novos veículos e atualizar o estoque.
5. **Gerenciamento de Funcionários:**
    - Inserir, alterar e excluir funcionários.
    - Definir permissões para cada funcionário.
6. **Relatórios:**
    - Gerar relatórios de vendas por período.
    - Gerar relatórios de estoque atual.

## Regras de Negócio

1. **RN1:** Somente gerentes podem adicionar novos veículos ao estoque.
2. **RN2:** Somente vendedores podem realizar vendas.
3. **RN3:** O estoque deve ser atualizado automaticamente após cada venda.
4. **RN4:** O sistema deve verificar se há estoque suficiente antes de realizar uma venda.

## Diagrama de Classes


| Classe | Atributos | Métodos |
| :-- | :-- | :-- |
| **Veiculo** | marca, modelo, ano, cor, preco | get/set Atributos, calcularPreco() |
| **Cliente** | nome, telefone, email | get/set Atributos |
| **Venda** | data, veiculo, cliente, notaFiscal | realizarVenda(), emitirNotaFiscal() |
| **Funcionario** | nome, cargo (vendedor/gerente) | get/set Atributos, realizarVenda() (para vendedores) |
| **Estoque** | listaVeiculos | adicionarVeiculo(), removerVeiculo() |

### Relacionamentos

- **Veiculo** está relacionado a **Venda** (um veículo pode ser vendido várias vezes, mas cada venda é de um veículo específico).
- **Cliente** está relacionado a **Venda** (um cliente pode realizar várias compras, mas cada venda é de um cliente específico).
- **Funcionario** está relacionado a **Venda** (um funcionário pode realizar várias vendas, mas cada venda é realizada por um funcionário específico).



