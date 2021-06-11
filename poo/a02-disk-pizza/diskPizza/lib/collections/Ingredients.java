package diskpizza.lib.collections;

import diskpizza.lib.models.Ingredient;

import java.util.ArrayList;
import java.util.List;

public class Ingredients {
  private List<Ingredient> ingredients = new ArrayList<Ingredient>();

  public Ingredient create(String name, String phone, String cpf, String address) {
    Ingredient ingredient = new Ingredient(name, phone, cpf, address);

    ingredients.add(ingredient);

    return ingredient;
  }

  public Ingredient findById(int id) {
    for (Ingredient ingredient : ingredients) {
      if (ingredient.getId() == id) return ingredient;
    }

    return null;
  }

  public Ingredient findByName(String name) {
    for (Ingredient ingredient : ingredients) {
      if (ingredient.getName() == name) return ingredient;
    }

    return null;
  }
}
