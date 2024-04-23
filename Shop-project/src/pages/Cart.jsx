import React from 'react';
import { useContext } from 'react';
import Button from 'react-bootstrap/Button';
// Importam ce avem nevoie.
import { CartContext } from '../store/Cart/context';
import { removeFromCart } from '../store/Cart/actions';

export function Cart() {
  // Extragem state-ul si dispatch-ul asociate cart-ului.
  const { state, dispatch } = useContext(CartContext);

  function handleCartRemove(id) {
    // Apelam actiunea, cu payload-ul aferent.
    const actionResult = removeFromCart(id);
    // Trimitem rezultatul actiunii catre reducer.
    dispatch(actionResult);
  }

  return (
    <div className="mx-2">
      {/* Afisam continutul state-ului cart-ului pe ecran. */}
      {state.products.length === 0 ? (
        <p>Nu ai produse in cos.</p>
      ) : (
        state.products.map((product) => {
          const totalProductPrice = product.price * product.quantity;
          return (
            <div key={product.id} className="m-3">
              <div className="d-flex justify-content-between align-items-center mb-3">
                <img src={product.image} alt="" />
                <strong>{product.name}</strong>
                <p>
                  {product.quantity} X {product.price}$ = {totalProductPrice}$
                </p>
              </div>
              <Button
                variant="danger"
                // La click pe buton, apelam functia ce va declansa modificarea state-ului.
                onClick={() => handleCartRemove(product.id)}
              >
                Remove
              </Button>
            </div>
          );
        })
      )}
    </div>
  );
}
