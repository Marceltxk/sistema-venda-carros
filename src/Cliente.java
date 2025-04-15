public class Cliente {
    private String nome, telefone, email;
    
    public Cliente(String nome, String telefone, String email) {
        this.nome = nome;
        this.telefone = telefone;
        this.email = email;
    }

    public String getNome() { return nome; }
    public String getTelefone() { return telefone; }
    public String getEmail() { return email; };

    public void setNome(String nome)  { this.nome = nome; }
    public void setTelefone(String tel) { this.telefone = tel; }
    public void setEmail(String email) { this.email = email; }
}