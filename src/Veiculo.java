public class Veiculo {
    private String marca, modelo, cor, placa;
    private int ano;
    private double preco;

    public Veiculo(String marca, String modelo, int ano, String cor, double preco, String placa) {
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
        this.cor = cor;
        this.preco = preco;
        this.placa = placa;
    }

    public String toString() {
        return marca + " " + modelo + " (" + ano + ")\n" + 
               "Cor: " + cor + "\n" + 
               "Preço: R$" + preco + "\n" + 
               "Placa: " + placa;
    }    

    public String getPlaca() { return placa; }
    public String getMarca() { return marca; }
    public String getModelo() { return modelo; }
    public String getCor() { return cor; }
    public int getAno() { return ano; }
    public double getPreco() { return preco; }

    public void setMarca(String marca) { this.marca = marca; }
    public void setModelo(String modelo) { this.modelo = modelo; }
    public void setAno(int ano) { this.ano = ano; }
    public void setCor(String cor) { this.cor = cor; }
    public void setPreco(double preco) { this.preco = preco; }
}

