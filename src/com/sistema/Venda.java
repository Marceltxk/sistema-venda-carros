package com.sistema;

import java.time.LocalDate;

public class Venda {
    private LocalDate data;
    private Veiculo veiculo;
    private Cliente cliente;
    private Funcionario funcionario;

    public Venda(LocalDate data, Veiculo veiculo, Cliente cliente, Funcionario funcionario) {
        this.data = data;
        this.veiculo = veiculo;
        this.cliente = cliente; 
        this.funcionario = funcionario;
    }

    public LocalDate getData() { return this.data; }
    public Veiculo getVeiculo() { return this.veiculo; }
    public Cliente getCliente() { return this.cliente; }
    // public String getNotaFiscal() { return this.notaFiscal; }

    // public String emitirNotaFiscal() {

    // }

}