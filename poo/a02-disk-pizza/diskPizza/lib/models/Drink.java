package diskpizza.lib.models;

public class Drink {
  private int id;
  private String name;

  public Drink(int id, String name) {
    setId(id);
    setname(name);
  }

  public void setId(int id) {
    this.id = id;
  }

  public void setname(String name) {
    this.name = name;
  }

  public int getId() {
    return id;
  }

  public String getname() {
    return name;
  }
}
