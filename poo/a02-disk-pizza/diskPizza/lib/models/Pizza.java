package diskpizza.lib.models;

import diskpizza.lib.collections.Ingredients;

public class Pizza {
  private int id;
  private String name;
  private Ingredients ingredients;

  public Pizza(int id, String name, Ingredients ingredients) {
    setId(id);
    setName(name);
    setIngredients(ingredients);
  }

  public void setId(int id) {
    this.id = id;
  }

  public void setName(String name) {
    this.name = name;
  }

  public void setIngredients(Ingredients ingredients) {
    this.ingredients = ingredients;
  }

  public int getId() {
    return id;
  }

  public String getName() {
    return name;
  }

  public Ingredients getIngredients() {
    return ingredients;
  }
}
