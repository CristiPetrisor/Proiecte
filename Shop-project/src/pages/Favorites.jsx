import React, { useContext } from 'react';
import { FavoritesContext } from '../store/Favorites/context';
import { removeFromFavorites } from '../store/Favorites/actions';
import { Button } from 'react-bootstrap';

export function Favorites() {
  const { state, dispatch } = useContext(FavoritesContext);

  function handleFavoritesRemove(productId) {
    const actionResult = removeFromFavorites(productId);
    dispatch(actionResult);
  }

  return (
    <div className="mx-2">
      {state.products.length === 0 ? (
        <p>Nu sunt produse favorite.</p>
      ) : (
        state.products.map((product) => (
          <div key={product.id} className="m-3">
            <div className="d-flex align-items justify-content-between mx-4">
              <img src={product.image} alt="" />
              <strong>{product.name}</strong>
              <Button
                variant="danger"
                onClick={() => {
                  handleFavoritesRemove(product.id);
                }}
              >
                Remove
              </Button>
            </div>
          </div>
        ))
      )}
    </div>
  );
}
