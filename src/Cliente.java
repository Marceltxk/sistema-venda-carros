public class Cliente {
    private String cpf, nome, telefone, email;
    
    public Cliente(String cpf, String nome, String telefone, String email) {
        this.cpf = cpf;
        this.nome = nome;
        this.telefone = telefone;
        this.email = email;
    }

    public String getCpf() { return cpf; }
    public String getNome() { return nome; }
    public String getTelefone() { return telefone; }
    public String getEmail() { return email; };

    public void setCpf(String cpf) {this.cpf = cpf; }
    public void setNome(String nome)  { this.nome = nome; }
    public void setTelefone(String tel) { this.telefone = tel; }
    public void setEmail(String email) { this.email = email; }
}