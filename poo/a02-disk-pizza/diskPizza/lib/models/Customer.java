package diskpizza.lib.models;

public class Customer {
  private String name;
  private String phone;
  private String cpf;
  private String address;

  public Customer(String name, String phone, String cpf, String address) {
    setName(name);
    setPhone(phone);
    setCpf(cpf);
    setAddress(address);
  }

  public void setName(String name) {
    this.name = name;
  }

  public void setPhone(String phone) {
    this.phone = phone;
  }

  public void setCpf(String cpf) {
    this.cpf = cpf;
  }

  public void setAddress(String address) {
    this.address = address;
  }

  public String getName() {
    return name;
  }

  public String getPhone() {
    return phone;
  }

  public String getCpf() {
    return cpf;
  }

  public String getAddress() {
    return address;
  }
}
