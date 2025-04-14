import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Sistema sistema = new Sistema();

        Funcionario gerente = new Gerente("Carlos", "111");
        Funcionario vendedor = new Vendedor("Ana", "222");
        sistema.adicionarFuncionario(gerente);
        sistema.adicionarFuncionario(vendedor);

        while (true) {
            
            System.out.println("\n--- MENU ---");
            System.out.println("1. Adicionar Veículo");
            System.out.println("2. Alterar Veículo");
            System.out.println("3. Excluir Veículo");
            System.out.println("4. Adicionar Cliente");
            System.out.println("5. Alterar Cliente");
            System.out.println("6. Excluir Cliente");
            System.out.println("7. Realizar Venda");
            System.out.println("8. Listar Estoque");
            System.out.println("9. Listar Vendas");
            System.out.println("10. Relatório de Vendas");
            System.out.println("11. Relatório de Estoque");
            System.out.println("0. Sair");
            int opcao = sc.nextInt(); sc.nextLine();

            switch (opcao) {
                case 1:
                    System.out.print("Placa: ");
                    String placa = sc.nextLine();
                    System.out.print("Marca: ");
                    String marca = sc.nextLine();
                    System.out.print("Modelo: ");
                    String modelo = sc.nextLine();
                    System.out.print("Ano: ");
                    int ano = sc.nextInt(); sc.nextLine();
                    System.out.print("Cor: ");
                    String cor = sc.nextLine();
                    System.out.print("Preço: ");
                    double preco = sc.nextDouble(); sc.nextLine();
                    sistema.adicionarVeiculo(new Veiculo(marca, modelo, ano, cor, preco, placa), gerente);
                    break;
                case 2:
                    System.out.print("Placa do veículo a alterar: ");
                    sistema.alterarVeiculo(sc.nextLine(), sc);
                    break;
                case 3:
                    System.out.print("Placa do veículo a excluir: ");
                    sistema.excluirVeiculo(sc.nextLine());
                    break;
                case 4:
                    System.out.print("CPF: ");
                    String cpf = sc.nextLine();
                    System.out.print("Nome: ");
                    String nome = sc.nextLine();
                    System.out.print("Telefone: ");
                    String telefone = sc.nextLine();
                    System.out.print("Email: ");
                    String email = sc.nextLine();
                    sistema.adicionarCliente(new Cliente(cpf, nome, telefone, email));
                    break;
                case 5:
                    System.out.print("CPF do cliente a alterar: ");
                    sistema.alterarCliente(sc.nextLine(), sc);
                    break;
                case 6:
                    System.out.print("CPF do cliente a excluir: ");
                    sistema.excluirCliente(sc.nextLine());
                    break;
                case 7:
                    System.out.print("Placa do veículo: ");
                    String placaVenda = sc.nextLine();
                    System.out.print("CPF do cliente: ");
                    String cpfCliente = sc.nextLine();
                    sistema.realizarVenda(placaVenda, cpfCliente, vendedor);
                    break;
                case 8:
                    sistema.listarEstoque();
                    break;
                case 9:
                    sistema.listarVendas();
                    break;
                case 10:
                    sistema.gerarRelatorioVendas();
                    break;
                case 11:
                    sistema.gerarRelatorioEstoque();
                    break;
                case 0:
                    System.out.println("Saindo...");
                    return;
                default:
                    System.out.println("Opção inválida!");
            }
        }
    }
}
