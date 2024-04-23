// State-ul initial contine campul prodcts, ce are ca valoare un array gol.
export const initialState = {
  // Initial nu avem produse in cart.
  products: [],
};

// Reducerul primeste ca parametri state-ul, respectiv rezultatul apelului unei actiuni.
export function cartReducer(state, action) {
  console.log(action);
  // Evaluam tipurile actiunii:
  switch (action.type) {
    case 'ADD_TO_CART': {
      let updatedProducts;
      let newState;
      // Verificam daca produsul continut in actiune exista deja in cart.
      const foundProduct = state.products.find((product) => {
        return product.id === action.payload.id;
      });
      // Daca am gasit produsul, ii marim cantitatea cu 1.
      if (foundProduct) {
        // Este nevoie sa modificam cantitatea FARA sa modificam array-ul initial.
        // Astfel, folosim un map.
        updatedProducts = state.products.map((product) => {
          // Daca produsul este cel cautat, returnam un nou produs, care contine campurile produsului anterior, dar cu cantitatea modificata.
          if (foundProduct.id === product.id) {
            return {
              // Continutul produsului din state-ul anterior.
              ...product,
              // Cantitatea produsului din state-ul anterior + 1.
              quantity: product.quantity + 1,
            };
            // Daca produsul nu este cel cautat, nu avem nimic de modificat, deci il returnam.
          } else {
            return product;
          }
        });
        // Daca produsul adauagt in cart nu exista deja in cart, il adaugam la sfarsitul array-ului.
      } else {
        // Avem grija ca noul array de produse sa nu il modifice pe cel vechi!
        updatedProducts = [
          ...state.products,
          {
            ...action.payload,
            // Fiind prima data cand un produs este adaugat in cart, are cantitatea 1.
            quantity: 1,
          },
        ];
      }
      // Cream noul state, ce contine produsele actualizate.
      newState = {
        products: updatedProducts,
      };
      // Returnam noul state.
      return newState;
    }
    case 'REMOVE_FROM_CART': {
      // Pentru a șterge produsele, filtram produsele din state, excuzandu-l pe cel care are id-ul venit din payload.
      const filteredProducts = state.products.filter((product) => {
        return product.id !== action.payload;
      });
      // State-ul nou va contine produsele filtrate.
      const newState = {
        products: filteredProducts,
      };
      return newState;
    }
    // Nu uitam ca in cazul default sa returnam state-ul anterior, nemodificat!
    default:
      return state;
  }
}
