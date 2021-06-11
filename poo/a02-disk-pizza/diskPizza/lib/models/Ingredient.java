package diskpizza.lib.models;

public class Ingredient {
  private String name;
  private float price;

  public Ingredient(String name, float price) {
    setName(name);
    setPrice(price);
  }

  public void setName(String name) {
    this.name = name;
  }

  public void setPrice(float price) {
    this.price = price;
  }

  public String getName() {
    return name;
  }

  public float getPrice() {
    return price;
  }
}
