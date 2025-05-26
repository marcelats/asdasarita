package asda;
import java.io.Serializable;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Vector;

/**  
 * Representa o usu rio que foi armazenado no banco de dados, com todos seus
 * atributos e configura  es de modelagem
 * @author Andr  Felipe Rodrigues
 * @version 1.0
 */ 

public class UsuarioCadastro implements Serializable{
	

	private int id;

	private String nome;

	private String password;

	private String tipoUsuario;

	private String tipoModelo;

	private String abordagem;

	private String linguagem;

	private int warmup;

	private int lote;

	private String plataforma;
	
	public UsuarioCadastro()
	{

	}
	
	public UsuarioCadastro(ResultSet rs)
	{
		loadResultSet(rs);
	}

	public String getAbordagem() {
		return abordagem;
	}

	public void setAbordagem(String abordagem) {
		this.abordagem = abordagem;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getLinguagem() {
		return linguagem;
	}

	public void setLinguagem(String linguagem) {
		this.linguagem = linguagem;
	}

	public int getLote() {
		return lote;
	}

	public void setLote(int lote) {
		this.lote = lote;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getPlataforma() {
		return plataforma;
	}

	public void setPlataforma(String plataforma) {
		this.plataforma = plataforma;
	}

	public String getTipoModelo() {
		return tipoModelo;
	}

	public void setTipoModelo(String tipoModelo) {
		this.tipoModelo = tipoModelo;
	}

	public String getTipoUsuario() {
		return tipoUsuario;
	}

	public void setTipoUsuario(String tipoUsuario) {
		this.tipoUsuario = tipoUsuario;
	}

	public int getWarmup() {
		return warmup;
	}

	public void setWarmup(int warmup) {
		this.warmup = warmup;
	}

	public void loadResultSet(ResultSet rs)
	{
		try
		{
			this.id = Integer.parseInt(rs.getString(1));
			this.nome = rs.getString(2);
			this.password = rs.getString(3);
			this.tipoUsuario = rs.getString(4);
			this.tipoModelo = rs.getString(5);
			this.abordagem = rs.getString(6);
			this.linguagem = rs.getString(7);
			this.warmup = Integer.parseInt(rs.getString(8));
			this.lote = Integer.parseInt(rs.getString(9));
			this.plataforma = rs.getString(10);
		}
		catch(SQLException sqlex)
		{
			sqlex.printStackTrace();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public static void main(String args[])
	{
		String a = "teste A", b = "teste B", c = "teste C";
		Vector v = new Vector(0);
		v.add(a);
		v.add(b);
		v.add(c);
		System.out.println((String)v.get(0) + " " + (String)v.get(1));
		v.remove(0);
		System.out.println((String)v.get(0) + " " + (String)v.get(1));
	}
	
	public String toString()
	{
		String ret;
		ret = "ID: " + getId()
			+ "Nome do usu rio: " + getNome()
			+ "Tipo de Modelo: " + getTipoModelo();
		return ret;
	}

}
