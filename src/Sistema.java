import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.time.LocalDate;

public class Sistema {
    
    private List<Veiculo> estoque;
    private List<Cliente> clientes;
    private List<Venda> vendas;
    private List<Funcionario> funcionarios;

    // Construtor da classe
    public Sistema() {
        this.estoque = new ArrayList<>();
        this.clientes = new ArrayList<>();
        this.vendas = new ArrayList<>();
        this.funcionarios = new ArrayList<>();
    }

     // Adicionar um veículo ao estoque
    public void adicionarVeiculo(Veiculo veiculo, Funcionario funcionario) {
        if (verificarPermissao(funcionario, "adicionarVeiculo")) {
            estoque.add(veiculo);
            System.out.println("Veículo adicionado ao estoque: " + veiculo);
        } else {
            System.out.println("Permissão negada! Apenas gerentes podem adicionar veículos.");
        }
    }

    // Alterar informações de um veículo
    public void alterarVeiculo(String placa, Scanner sc) {
        Veiculo veiculo = buscarVeiculoPorPlaca(placa);
        if (veiculo != null) {
            System.out.println("Alterando veículo: " + veiculo);
            System.out.print("Nova marca: ");
            veiculo.setMarca(sc.nextLine());
            System.out.print("Novo modelo: ");
            veiculo.setModelo(sc.nextLine());
            System.out.print("Novo ano: ");
            veiculo.setAno(sc.nextInt()); sc.nextLine();
            System.out.print("Nova cor: ");
            veiculo.setCor(sc.nextLine());
            System.out.print("Novo preço: ");
            veiculo.setPreco(sc.nextDouble()); sc.nextLine();
            System.out.println("Veículo alterado com sucesso!");
        } else {
            System.out.println("Veículo não encontrado!");
        }
    }

    // Excluir um veículo do estoque
    public void excluirVeiculo(String placa) {
        Veiculo veiculo = buscarVeiculoPorPlaca(placa);
        if (veiculo != null) {
            estoque.remove(veiculo);
            System.out.println("Veículo excluído: " + veiculo);
        } else {
            System.out.println("Veículo não encontrado!");
        }
    }

    // Adicionar um cliente
    public void adicionarCliente(Cliente cliente) {
        clientes.add(cliente);
        System.out.println("Cliente adicionado: " + cliente);
    }

    // Alterar informações de um cliente
    public void alterarCliente(String cpf, Scanner sc) {
        Cliente cliente = buscarClientePorCpf(cpf);
        if (cliente != null) {
            System.out.println("Alterando cliente: " + cliente);
            System.out.print("Novo nome: ");
            cliente.setNome(sc.nextLine());
            System.out.print("Novo telefone: ");
            cliente.setTelefone(sc.nextLine());
            System.out.print("Novo e-mail: ");
            cliente.setEmail(sc.nextLine());
            System.out.println("Cliente alterado com sucesso!");
        } else {
            System.out.println("Cliente não encontrado!");
        }
    }

    // Excluir um cliente
    public void excluirCliente(String cpf) {
        Cliente cliente = buscarClientePorCpf(cpf);
        if (cliente != null) {
            clientes.remove(cliente);
            System.out.println("Cliente excluído: " + cliente);
        } else {
            System.out.println("Cliente não encontrado!");
        }
    }

    // Realizar uma venda
    public void realizarVenda(String placa, String cpfCliente, Funcionario funcionario) {
        Veiculo veiculo = buscarVeiculoPorPlaca(placa);
        Cliente cliente = buscarClientePorCpf(cpfCliente);
        if (veiculo != null && cliente != null) {
            Venda venda = new Venda(LocalDate.now(), veiculo, cliente, funcionario);
            vendas.add(venda);
            estoque.remove(veiculo); // Remove o veículo do estoque após a venda
            System.out.println("Venda realizada com sucesso! " + venda);
        } else {
            System.out.println("Veículo ou cliente não encontrado!");
        }
    }

    // Listar o estoque de veículos
    public void listarEstoque() {
        if (estoque.isEmpty()) {
            System.out.println("Estoque vazio.");
        } else {
            System.out.println("\n--- Estoque de Veículos ---");
            for (Veiculo veiculo : estoque) {
                System.out.println(veiculo);
                System.out.println("\n---------------------------");
            }
        }
    }

    // Listar as vendas realizadas
    public void listarVendas() {
        if (vendas.isEmpty()) {
            System.out.println("Nenhuma venda realizada.");
        } else {
            System.out.println("\n--- Vendas Realizadas ---");
            for (Venda venda : vendas) {
                System.out.println(venda);
            }
        }
    }

    // Gerar o relatório de vendas
    public void gerarRelatorioVendas() {
        if (vendas.isEmpty()) {
            System.out.println("Nenhuma venda realizada.");
        } else {
            System.out.println("\n--- Relatório de Vendas ---");
            for (Venda venda : vendas) {
                System.out.println(venda);
            }
        }
    }

    // Gerar o relatório de estoque
    public void gerarRelatorioEstoque() {
        if (estoque.isEmpty()) {
            System.out.println("Estoque vazio.");
        } else {
            System.out.println("\n--- Relatório de Estoque ---");
            for (Veiculo veiculo : estoque) {
                System.out.println(veiculo);
            }
        }
    }

    // Adicionar um funcionário
    public void adicionarFuncionario(Funcionario funcionario) {
        funcionarios.add(funcionario);
    }

    // Buscar um veículo pelo número da placa
    private Veiculo buscarVeiculoPorPlaca(String placa) {
        for (Veiculo veiculo : estoque) {
            if (veiculo.getPlaca().equals(placa)) {
                return veiculo;
            }
        }
        return null;
    }

    // Buscar um cliente pelo CPF
    private Cliente buscarClientePorCpf(String cpf) {
        for (Cliente cliente : clientes) {
            if (cliente.getCpf().equals(cpf)) {
                return cliente;
            }
        }
        return null;
    }

    // Verificar se o funcionário tem permissão para realizar a operação
    private boolean verificarPermissao(Funcionario funcionario, String acao) {
        if (funcionario instanceof Gerente) {
            return true; // Apenas gerentes podem adicionar veículos
        }
        return false;
    }
}