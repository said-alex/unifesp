#include <stdio.h>
#include <stdlib.h>

#define PRODUCT_DOES_NOT_EXIST_MSG "nao existe"
#define PRODUCT_EXISTS_MSG "ja existe"

typedef struct product {
  int id;
  int amount;
  int sales;
  float gain;
  struct product* next;
} Product;

Product* newProduct(int id, int amount, float gain) {
  Product* product = (Product*)malloc(sizeof(Product));

  product->id = id;
  product->amount = amount;
  product->gain = gain;
  product->sales = 0;
  product->next = NULL;

  return product;
}

Product* insertProduct(Product* product, Product* newProduct) {
  if (!product)
    return newProduct;

  if (product->id == newProduct->id) {
    puts(PRODUCT_EXISTS_MSG);
    return product;
  }

  if (product->gain < newProduct->gain) {
    newProduct->next = product;
    return newProduct;
  }

  product->next = insertProduct(product->next, newProduct);

  return product;
}

Product* deleteProduct(Product* product, int productId) {
  if (!product) {
    puts(PRODUCT_DOES_NOT_EXIST_MSG);
    return product;
  }

  if (product->id == productId) {
    Product* productAux = product->next;
    free(product);
    return productAux;
  }

  product->next = deleteProduct(product->next, productId);

  return product;
}

Product* findProductById(Product* product, int productId) {
  if (!product || product->id == productId)
    return product;

  return findProductById(product->next, productId);
}

void updateProductAmount(Product* product, int productId, int amount) {
  product = findProductById(product, productId);

  if (!product) {
    puts(PRODUCT_DOES_NOT_EXIST_MSG);
    return;
  }

  product->amount += amount;
}

void saleProduct(Product* product, int productId) {
  product = findProductById(product, productId);

  if (!product || !product->amount) {
    puts(PRODUCT_DOES_NOT_EXIST_MSG);
    return;
  }

  product->sales++;
  product->amount--;
}

void showProduct(Product* product) {
  printf("%d %f\n", product->id, (product->gain * product->sales));
}

void listProducts(Product* product) {
  if (!product)
    return;

  showProduct(product);
  listProducts(product->next);
}

int main() {
  int operationCount, operation, id, amount;
  float gain;

  Product* product = NULL;

  scanf("%d", &operationCount);

  while (--operationCount >= 0) {
    scanf(" %d", &operation);

    if (operation == 1) {
      scanf(" %d %d %2f", &id, &amount, &gain);
      product = insertProduct(product, newProduct(id, amount, gain));
    } else if (operation == 2) {
      scanf(" %d %d", &id, &amount);
      updateProductAmount(product, id, amount);
    }
    else if (operation == 3) {
      scanf(" %d", &id);
      saleProduct(product, id);
    }
    else if (operation == 4) {
      scanf(" %d", &id);
      product = deleteProduct(product, id);
    } else {
      return 1;
    }
  }

  listProducts(product);

  return 0;
}
