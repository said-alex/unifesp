import diskPizza.lib.collections.Ingredients;

public class Pizza {
  private int id;
  private Ingredients ingredients;

  public Pizza(int id, Ingredients ingredients) {
    setId(id);
    setIngredients(ingredients);
  }

  public void setId(int id) {
    this.id = id;
  }

  public void setIngredients(Ingredients ingredients) {
    this.ingredients = ingredients;
  }

  public int getId() {
    return id;
  }

  public Ingredients getIngredients() {
    return ingredients;
  }
}
