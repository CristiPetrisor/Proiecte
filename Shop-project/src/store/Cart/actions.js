// Actiunea de adaugare in cart primeste ca paramaetru produsul adaugat.
export function addToCart(product) {
  return {
    type: "ADD_TO_CART",
    payload: product
  };
}

// Actiunea de stergere din cart primeste ca parametru id-ul produsului.
export function removeFromCart(productId) {
  return {
    type: "REMOVE_FROM_CART",
    payload: productId
  };
}
