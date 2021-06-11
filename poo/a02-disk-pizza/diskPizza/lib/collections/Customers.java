package diskpizza.lib.collections;

import diskpizza.lib.models.Customer;

import java.util.ArrayList;
import java.util.List;

public class Customers {
  private List<Customer> customers = new ArrayList<Customer>();

  public Customer create(String name, String phone, String cpf, String address) {
    Customer customer = new Customer(name, phone, cpf, address);

    customers.add(customer);

    return customer;
  }

  public Customer findByPhone(String phone) {
    for (Customer customer : customers) {
      if (customer.getPhone() == phone) return customer;
    }

    return null;
  }
}
