import java.time.LocalDate;

public class Venda {
    private LocalDate data;
    private Veiculo veiculo;
    private Cliente cliente;
    private String notaFiscal;

    public Venda(LocalDate data, Veiculo veiculo, Cliente cliente, String notaFiscal) {
        this.data = data;
        this.veiculo = veiculo;
        this.cliente = cliente; 
        this.notaFiscal = notaFiscal;
    }

    public LocalDate getData() { return this.data; }
    public Veiculo getVeiculo() { return this.veiculo; }
    public Cliente getCliente() { return this.cliente; }
    public String getNotaFiscal() { return this.notaFiscal; }

    public void realizarVenda() {

    }

    public String emitirNotaFiscal() {

    }

}