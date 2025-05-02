package com.sistema;

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
            System.out.println("\n--- MENU PRINCIPAL ---");
            System.out.println("1. Veículos");
            System.out.println("2. Clientes");
            System.out.println("3. Realizar Venda");
            System.out.println("4. Relatórios");
            System.out.println("0. Sair");
            int opcaoPrincipal = lerInteiro(sc, "Escolha uma opção: ", 0, 4, "Opção inválida!");

            switch (opcaoPrincipal) {
                case 1: // Veículos
                    System.out.println("\n--- MENU VEÍCULOS ---");
                    System.out.println("1. Adicionar Veículo");
                    System.out.println("2. Alterar Veículo");
                    System.out.println("3. Excluir Veículo");
                    System.out.println("4. Listar Estoque");
                    int opVeiculo = lerInteiro(sc, "Escolha uma opção: ", 1, 4, "Opção inválida!");
                    switch (opVeiculo) {
                        case 1:
                            String placa = lerTexto(sc, "Placa (7 caracteres, 4 letras e 3 números): ",
                                "^(?=(?:.*[A-Za-z]){4})(?=(?:.*\\d){3})[A-Za-z\\d]{7}$",
                                "Placa inválida! Deve conter exatamente 4 letras e 3 números.");

                            String marca = lerTexto(sc, "Marca: ",
                                "^[A-Za-zÀ-ÿ ]+$",
                                "Marca inválida! Digite apenas letras.");

                            String modelo = lerTexto(sc, "Modelo: ",
                                "^[A-Za-zÀ-ÿ0-9 ]+$",
                                "Modelo inválido! Digite apenas letras e números.");

                            int ano = lerInteiro(sc, "Ano: ",
                                1900, 2100,
                                "Ano inválido! Digite um número entre 1900 e 2100.");

                            String cor = lerTexto(sc, "Cor: ",
                                "^[A-Za-zÀ-ÿ ]+$",
                                "Cor inválida! Digite apenas letras.");

                            double preco = lerDouble(sc, "Preço: ",
                                0.0, Double.MAX_VALUE,
                                "Preço inválido! Digite um valor numérico positivo.");

                            sistema.adicionarVeiculo(new Veiculo(marca, modelo, ano, cor, preco, placa), gerente);
                            break;
                        case 2:
                            sistema.alterarVeiculo(lerTexto(sc, "Placa do veículo a alterar: ",
                                "^[A-Za-z\\d]{7}$", "Placa inválida!"), sc);
                            break;
                        case 3:
                            sistema.excluirVeiculo(lerTexto(sc, "Placa do veículo a excluir: ",
                                "^[A-Za-z\\d]{7}$", "Placa inválida!"));
                            break;
                        case 4:
                            sistema.listarEstoque();
                            break;
                        default:
                            System.out.println("Opção inválida! Retornando ao menu principal.");
                    }
                    break;

                case 2: // Clientes
                    System.out.println("\n--- MENU CLIENTES ---");
                    System.out.println("1. Adicionar Cliente");
                    System.out.println("2. Alterar Cliente");
                    System.out.println("3. Excluir Cliente");
                    int opCliente = lerInteiro(sc, "Escolha uma opção: ", 1, 3, "Opção inválida!");
                    switch (opCliente) {
                        case 1:
                            String cpf = lerTexto(sc, "CPF: ", "\\d{11}", "CPF inválido! Digite 11 dígitos.");
                            String nome = lerTexto(sc, "Nome: ", "^[A-Za-zÀ-ÿ ]+$", "Nome inválido!");
                            String telefone = lerTexto(sc, "Telefone: ", "\\d{10,11}", "Telefone inválido!");
                            String email = lerTexto(sc, "Email: ", "^.+@.+\\..+$", "Email inválido!");
                            sistema.adicionarCliente(new Cliente(cpf, nome, telefone, email));
                            break;
                        case 2:
                            sistema.alterarCliente(lerTexto(sc, "CPF do cliente a alterar: ", "\\d{11}", "CPF inválido!"), sc);
                            break;
                        case 3:
                            sistema.excluirCliente(lerTexto(sc, "CPF do cliente a excluir: ", "\\d{11}", "CPF inválido!"));
                            break;
                        default:
                            System.out.println("Opção inválida! Retornando ao menu principal.");
                    }
                    break;

                case 3: // Vendas
                    String placaVenda = lerTexto(sc, "Placa do veículo: ",
                        "^[A-Za-z\\d]{7}$", "Placa inválida!");
                    String cpfCliente = lerTexto(sc, "CPF do cliente: ",
                        "\\d{11}", "CPF inválido!");
                    sistema.realizarVenda(placaVenda.toUpperCase(), cpfCliente, vendedor);
                    break;

                case 4: // Relatórios
                    System.out.println("\n--- MENU RELATÓRIOS ---");
                    System.out.println("1. Relatório de Vendas");
                    System.out.println("2. Relatório de Estoque");
                    int opRelatorio = lerInteiro(sc, "Escolha uma opção: ", 1, 2, "Opção inválida!");
                    switch (opRelatorio) {
                        case 1:
                            sistema.gerarRelatorioVendas();
                            break;
                        case 2:
                            sistema.gerarRelatorioEstoque();
                            break;
                        default:
                            System.out.println("Opção inválida! Retornando ao menu principal.");
                    }
                    break;

                case 0:
                    System.out.println("Saindo...");
                    return;
            }
        }
    }

    public static String lerTexto(Scanner sc, String mensagem, String regex, String erro) {
        String input;
        while (true) {
            System.out.print(mensagem);
            input = sc.nextLine().trim();
            if (input.matches(regex)) {
                return input.toUpperCase();
            } else {
                System.out.println(erro);
            }
        }
    }

    public static int lerInteiro(Scanner sc, String mensagem, int min, int max, String erro) {
        while (true) {
            try {
                System.out.print(mensagem);
                int valor = Integer.parseInt(sc.nextLine());
                if (valor >= min && valor <= max) return valor;
                System.out.println(erro);
            } catch (NumberFormatException e) {
                System.out.println(erro);
            }
        }
    }

    public static double lerDouble(Scanner sc, String mensagem, double min, double max, String erro) {
        while (true) {
            try {
                System.out.print(mensagem);
                double valor = Double.parseDouble(sc.nextLine());
                if (valor >= min && valor <= max) return valor;
                System.out.println(erro);
            } catch (NumberFormatException e) {
                System.out.println(erro);
            }
        }
    }
}
